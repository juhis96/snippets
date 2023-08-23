#include <iostream>
#include <array>
#include <string>

std::string executePowerShellCommand(const std::string& command) {
    std::array<char, 128> buffer;
    std::string result;

    // Open the PowerShell process
    FILE* pipe = _popen("powershell.exe", "w");
    if (!pipe) {
        throw std::runtime_error("Failed to open PowerShell process.");
    }

    // Send the command to the PowerShell process
    fprintf(pipe, "%s\n", command.c_str());
    fflush(pipe);

    // Read the output line by line
    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        result += buffer.data();
    }

    // Close the PowerShell process
    _pclose(pipe);

    // Remove trailing newline characters
    while (!result.empty() && (result.back() == '\n' || result.back() == '\r')) {
        result.pop_back();
    }

    return result;
}

int main() {
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
        output = executePowerShellCommand(command);

        // Print the output
        std::cout << "Output: " << output << std::endl;

    }

    return 0;
}