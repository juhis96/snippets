#include <iostream>
#include <array>
#include <string>

// Global variable to store the PowerShell process
FILE* powershellProcess = nullptr;

void initializePowerShell() {
    // Open the PowerShell process
    powershellProcess = _popen("powershell.exe", "w");
    if (!powershellProcess) {
        throw std::runtime_error("Failed to open PowerShell process.");
    }
}

void closePowerShell() {
    // Close the PowerShell process
    if (powershellProcess) {
        _pclose(powershellProcess);
        powershellProcess = nullptr;
    }
}

std::string executePowerShellCommand(const std::string& command) {
    std::array<char, 128> buffer;
    std::string result;

    // Check if the PowerShell process is open
    if (!powershellProcess) {
        throw std::runtime_error("PowerShell process is not initialized.");
    }

    // Send the command to the PowerShell process
    fprintf(powershellProcess, "%s\n", command.c_str());
    fflush(powershellProcess);

    // Read the output line by line
    while (fgets(buffer.data(), buffer.size(), powershellProcess) != nullptr) {
        result += buffer.data();
    }

    // Remove trailing newline characters
    while (!result.empty() && (result.back() == '\n' || result.back() == '\r')) {
        result.pop_back();
    }

    return result;
}

int main() {
    initializePowerShell();

    std::string command;
    std::string output;

    while (true) {
        // Prompt for command input
        std::cout << "Enter a PowerShell command (or 'exit' to quit): ";
        std::getline(std::cin, command);

        // Check if the user wants to exit
        if (command == "exit") {
            break;
        }

        // Execute the PowerShell command
        try {
            output = executePowerShellCommand(command);
            std::cout << "Output: " << output << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    closePowerShell();

    return 0;
}