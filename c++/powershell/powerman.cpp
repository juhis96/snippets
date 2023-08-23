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
    std::string command1 = "Write-Output 'Hello, World!'";
    std::string command2 = "Get-Date";
    std::string command3 = "Get-Process";

    std::string output1 = executePowerShellCommand(command1);
    std::cout << "Output 1: " << output1 << std::endl;

    std::string output2 = executePowerShellCommand(command2);
    std::cout << "Output 2: " << output2 << std::endl;

    std::string output3 = executePowerShellCommand(command3);
    std::cout << "Output 3: " << output3 << std::endl;

    return 0;
}