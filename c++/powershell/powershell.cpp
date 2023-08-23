#include <iostream>
#include <windows.h>

int main()
{
    // Create the command to execute
    std::wstring command = L"powershell.exe -Command \"Write-Host 'Hello, PowerShell!'\"";

    // Create the necessary structures for process creation
    STARTUPINFOW si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Start the PowerShell process
    if (CreateProcessW(
        NULL,                                          // No module name (use command line)
        const_cast<LPWSTR>(command.c_str()),            // Command line
        NULL,                                          // Process handle not inheritable
        NULL,                                          // Thread handle not inheritable
        FALSE,                                         // Set handle inheritance to FALSE
        0,                                             // No creation flags
        NULL,                                          // Use parent's environment block
        NULL,                                          // Use parent's starting directory
        &si,                                           // Pointer to STARTUPINFO structure
        &pi)                                           // Pointer to PROCESS_INFORMATION structure
        )
    {
        // Wait for the PowerShell process to finish
        WaitForSingleObject(pi.hProcess, INFINITE);

        // Get the exit code of the PowerShell process
        DWORD exitCode = 0;
        GetExitCodeProcess(pi.hProcess, &exitCode);

        // Close process and thread handles
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);

        // Print the exit code
        std::cout << "PowerShell exit code: " << exitCode << std::endl;
    }
    else
    {
        std::cerr << "Failed to execute PowerShell command." << std::endl;
        return 1;
    }

    return 0;
}