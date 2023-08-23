#include <iostream>
#include <windows.h>

int main()
{
    // Create two anonymous pipes for communication
    HANDLE hCmdInputRead, hCmdInputWrite;
    HANDLE hCmdOutputRead, hCmdOutputWrite;
    SECURITY_ATTRIBUTES sa = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };
    CreatePipe(&hCmdOutputRead, &hCmdOutputWrite, &sa, 0);
    CreatePipe(&hCmdInputRead, &hCmdInputWrite, &sa, 0);

    // Set the properties of the Command Prompt process
    STARTUPINFOW si = { sizeof(STARTUPINFOW) };  // Use wide character structure
    PROCESS_INFORMATION pi;
    si.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
    si.hStdOutput = hCmdOutputWrite;
    si.hStdInput = hCmdInputRead;
    si.hStdError = hCmdOutputWrite;  // Optional: Redirect standard error to the same pipe
    si.wShowWindow = SW_HIDE;

    // Create the Command Prompt process
    if (CreateProcessW(
        L"C:\\Windows\\System32\\cmd.exe",  // Path to CMD executable (wide string)
        NULL,                               // Command line (NULL for no arguments)
        NULL,                               // Process handle not inheritable
        NULL,                               // Thread handle not inheritable
        TRUE,                               // Inherit handles
        0,                                  // Creation flags
        NULL,                               // Use parent's environment block
        NULL,                               // Use parent's starting directory
        &si,                                // Pointer to STARTUPINFOW structure
        &pi                                 // Pointer to PROCESS_INFORMATION structure
    ))
    {
        // Close unnecessary handles
        CloseHandle(pi.hThread);
        CloseHandle(hCmdOutputWrite);
        CloseHandle(hCmdInputRead);

        // Read and print the Command Prompt output
        char buffer[4096];
        DWORD bytesRead;
        while (ReadFile(hCmdOutputRead, buffer, sizeof(buffer), &bytesRead, NULL) && bytesRead > 0)
        {
            std::cout.write(buffer, bytesRead);
        }

        // Send commands to Command Prompt
        std::string command;
        while (true)
        {
            std::cout << "> ";
            std::getline(std::cin, command);

            command += "\r\n";  // Add carriage return and newline characters

            // Write the command to Command Prompt
            DWORD bytesWritten;
            WriteFile(hCmdInputWrite, command.c_str(), static_cast<DWORD>(command.size()), &bytesWritten, NULL);

            // Read and print the Command Prompt output
            while (ReadFile(hCmdOutputRead, buffer, sizeof(buffer), &bytesRead, NULL) && bytesRead > 0)
            {
                std::cout.write(buffer, bytesRead);
            }
        }

        // Cleanup
        CloseHandle(pi.hProcess);
        CloseHandle(hCmdOutputRead);
        CloseHandle(hCmdInputWrite);
    }
    else
    {
        std::cerr << "Failed to create Command Prompt process." << std::endl;
        return 1;
    }

    return 0;
}