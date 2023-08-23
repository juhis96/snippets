#include <iostream>
#include <windows.h>

int main()
{
    // Create a named pipe for communication
    HANDLE pipe = CreateNamedPipeW(
        L"\\\\.\\pipe\\MyLocalPipe",             // Pipe name (wide string)
        PIPE_ACCESS_DUPLEX,                 // Read/write access
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT, // Pipe mode
        PIPE_UNLIMITED_INSTANCES,           // Max instances
        0,                                  // Output buffer size
        0,                                  // Input buffer size
        0,                                  // Default timeout (0 means blocking)
        NULL                                // Security attributes
    );

    if (pipe == INVALID_HANDLE_VALUE)
    {
        std::cerr << "Failed to create named pipe." << std::endl;
        return 1;
    }

    std::cout << "Waiting for PowerShell to connect..." << std::endl;

    // Wait for a client (PowerShell) to connect to the pipe
    if (ConnectNamedPipe(pipe, NULL) != FALSE)
    {
        std::cout << "PowerShell connected. You can start sending commands." << std::endl;

        // Read commands from the user and send them to PowerShell
        std::string command;
        while (true)
        {
            std::cout << "> ";
            std::getline(std::cin, command);

            // Send the command to PowerShell through the pipe
            DWORD bytesWritten;
            WriteFile(pipe, command.c_str(), static_cast<DWORD>(command.size()), &bytesWritten, NULL);

            // Read the response from PowerShell
            char buffer[4096];
            DWORD bytesRead;
            ReadFile(pipe, buffer, sizeof(buffer), &bytesRead, NULL);

            // Null-terminate the response and print it
            buffer[bytesRead] = '\0';
            std::cout << "PowerShell response: " << buffer << std::endl;
        }
    }

    // Cleanup
    CloseHandle(pipe);

    return 0;
}