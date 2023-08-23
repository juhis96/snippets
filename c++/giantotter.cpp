#include <windows.h>
#include <winuser.h>
#include <iostream>
#include <array>
#include <string>

using namespace std;

string executePowerShellCommand(const std::string& command) {
    array<char, 128> buffer;
    string result;
    
    // Open a pipe to read the output of the PowerShell command
    FILE* pipe = _popen(command.c_str(), "r");
    if (!pipe) {
        throw std::runtime_error("Failed to open pipe.");
    }

    // Read the output line by line
    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        result += buffer.data();
    }

    // Close the pipe
    _pclose(pipe);

    // Remove trailing newline characters
    while (!result.empty() && (result.back() == '\n' || result.back() == '\r')) {
        result.pop_back();
    }

    return result;
}

int main(){
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;
    cfi.dwFontSize.Y = 24;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    std::wcscpy(cfi.FaceName, L"Consolas");
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

    cout << '\a';
    Beep(523,500);
    cout << '\7';
    
    system("mode 650");
    //system("mode con COLS=700");
    ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
    SendMessage(GetConsoleWindow(), WM_SYSKEYDOWN,VK_RETURN, 0x20000000);
    ShowScrollBar(GetConsoleWindow(), SB_VERT, FALSE);

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO scrBufferInfo;
    GetConsoleScreenBufferInfo(hOut, &scrBufferInfo);

    short winWidth = scrBufferInfo.srWindow.Right - scrBufferInfo.srWindow.Left + 1;
    short winHeight = scrBufferInfo.srWindow.Bottom - scrBufferInfo.srWindow.Top + 1;
    short scrBufferWidth = scrBufferInfo.dwSize.X;
    short scrBufferHeight = scrBufferInfo.dwSize.Y;

    COORD newSize;
    newSize.X = scrBufferWidth;
    newSize.Y = winHeight;

    //SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    int Status = SetConsoleScreenBufferSize(hOut, newSize);
    if (Status == 0)
    {
    cout << "SetConsoleScreenBufferSize() failed! Reason : " << GetLastError() << endl;
    exit(Status);
    }

    GetConsoleScreenBufferInfo(hOut, &scrBufferInfo);
    cout << "Screen Buffer Size : " << scrBufferInfo.dwSize.X << " x " << scrBufferInfo.dwSize.Y << endl;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 12);

    cout << "" << endl <<
    "                                          ▓▓▓▓▓▓▓▓▓▓                        " << endl <<
    "  ▓▓▓▓  ▓▓▓▓▓▓▓▓▓▓▓▓  ▓▓▓▓              ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓                    " << endl <<
    "  ▓▓▓▓▓▓▒▒▓▓▓▓▓▓▓▓▒▒▓▓▓▓▓▓          ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓                  " << endl <<
    "    ▓▓▒▒▓▓▓▓▓▓▓▓▓▓▓▓▒▒▓▓          ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓              " << endl <<
    "      ████▓▓▓▓▓▓▓▓████▓▓▓▓▓▓    ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓            " << endl <<
    "    ▓▓▒▒██▓▓▓▓▓▓▓▓██▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓          " << endl <<
    "  ▓▓░░▒▒▒▒▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓        " << endl <<
    "▓▓░░░░▓▓▒▒░░████░░▒▒▓▓░░▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓        " << endl <<
    "▓▓░░▓▓░░    ████    ░░▓▓▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓        " << endl <<
    "▓▓░░▓▓░░            ░░▓▓░░▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓      " << endl <<
    "▓▓░░░░▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓░░░░▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓      " << endl <<
    "  ▓▓░░░░░░░░░░░░░░░░░░░░░░▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓      " << endl <<
    "  ▓▓░░░░░░░░░░░░░░░░░░░░░░▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓    " << endl <<
    "  ▓▓░░░░              ░░░░▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓  " << endl <<
    "    ▓▓░░░░          ░░░░▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓  " << endl <<
    "      ▓▓░░░░        ░░░░▒▒▒▒▓▓▒▒▒▒▒▒▓▓▓▓▓▓▒▒▒▒▓▓▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓" << endl <<
    "        ▓▓░░░░      ░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓" << endl <<
    "        ▓▓░░░░      ░░░░▒▒▒▒▒▒░░░░░░▒▒▒▒▒▒░░░░▓▓▓▓▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓" << endl <<
    "        ▓▓░░░░░░░░░░░░▓▓▒▒▒▒▒▒▓▓▓▓▓▓░░░░░░▓▓▓▓    ▓▓▓▓▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓  " << endl <<
    "  ▓▓▓▓▓▓▓▓▓▓▓▓░░░░░░▓▓▓▓▓▓▓▓▓▓      ▓▓▓▓▓▓            ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓  " << endl <<
    "▓▓▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▓▓▓▓                        ▓▓▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓  " << endl <<
    "  ▓▓▓▓▓▓▓▓        ▓▓▓▓▓▓▓▓                            ▓▓▓▓▓▓▓▓  ▓▓▓▓▓▓▓▓▓▓  " << endl <<
    "                                                              ▓▓▓▓▓▓▓▓▓▓    " << endl <<
    "                                                        ▓▓▓▓▓▓▓▓▓▓▓▓▓▓      " << endl <<
    "                                                      ▓▓▓▓▓▓▓▓▓▓▓▓          " << endl << "";

    /*
    cout << "" << endl <<
    "                                          ▓▓▓▓▓▓▓▓▓▓                        " << endl <<
    "  ▓▓▓▓  ▓▓▓▓▓▓▓▓▓▓▓▓  ▓▓▓▓              ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓                    " << endl <<
    "  ▓▓▓▓▓▓▒▒▓▓▓▓▓▓▓▓▒▒▓▓▓▓▓▓          ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓                  " << endl <<
    "    ▓▓▒▒▓▓▓▓▓▓▓▓▓▓▓▓▒▒▓▓          ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓              " << endl <<
    "      ▒▒██▓▓▓▓▓▓▓▓██▒▒▓▓▓▓▓▓    ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓            " << endl <<
    "    ▓▓████▓▓▓▓▓▓▓▓████▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓          " << endl <<
    "  ▓▓░░▒▒▓▒▓▓▓▓▓▓▓▓▒▓▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓        " << endl <<
    "▓▓░░░░▒▒▓▒░░████░░▒▓▒▒░░▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓        " << endl <<
    "▓▓░░▒▒░░    ████    ░░▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓        " << endl <<
    "▓▓░░▒▒░░            ░░▒▒░░▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓      " << endl <<
    "▓▓░░░░▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓░░░░▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓      " << endl <<
    "  ▓▓░▓▓░░░░░░░░░░░░░░░▓▓░░▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓      " << endl <<
    "  ▓▓░▓░░░░░░░░░░░░░░░░░▓░░▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓    " << endl <<
    "  ▓▓░░░░              ░░░░▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓  " << endl <<
    "    ▓▓░░░░          ░░░░▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓  " << endl <<
    "      ▓▓░░░░        ░░░░▒▒▒▒▓▓▒▒▒▒▒▒▓▓▓▓▓▓▒▒▒▒▓▓▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓" << endl <<
    "        ▓▓░░░░      ░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓" << endl <<
    "        ▓▓░░░░      ░░░░▒▒▒▒▒▒░░░░░░▒▒▒▒▒▒░░░░▓▓▓▓▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓" << endl <<
    "        ▓▓░░░░░░░░░░░░▓▓▒▒▒▒▒▒▓▓▓▓▓▓░░░░░░▓▓▓▓    ▓▓▓▓▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓  " << endl <<
    "  ▓▓▓▓▓▓▓▓▓▓▓▓░░░░░░▓▓▓▓▓▓▓▓▓▓      ▓▓▓▓▓▓            ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓  " << endl <<
    "▓▓▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▓▓▓▓                        ▓▓▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓  " << endl <<
    "  ▓▓▓▓▓▓▓▓        ▓▓▓▓▓▓▓▓                            ▓▓▓▓▓▓▓▓  ▓▓▓▓▓▓▓▓▓▓  " << endl <<
    "                                                              ▓▓▓▓▓▓▓▓▓▓    " << endl <<
    "                                                        ▓▓▓▓▓▓▓▓▓▓▓▓▓▓      " << endl <<
    "                                                      ▓▓▓▓▓▓▓▓▓▓▓▓          " << endl << "";
    */

    cout << " "  << endl <<
    "  ▄████  ██▓ ▄▄▄       ███▄    █ ▄▄▄█████▓    ▒█████  ▄▄▄█████▓▄▄▄█████▓▓█████  ██▀███  " << endl <<
    " ██▒ ▀█▒▓██▒▒████▄     ██ ▀█   █ ▓  ██▒ ▓▒   ▒██▒  ██▒▓  ██▒ ▓▒▓  ██▒ ▓▒▓█   ▀ ▓██ ▒ ██▒" << endl <<
    "▒██░▄▄▄░▒██▒▒██  ▀█▄  ▓██  ▀█ ██▒▒ ▓██░ ▒░   ▒██░  ██▒▒ ▓██░ ▒░▒ ▓██░ ▒░▒███   ▓██ ░▄█ ▒" << endl <<
    "░▓█  ██▓░██░░██▄▄▄▄██ ▓██▒  ▐▌██▒░ ▓██▓ ░    ▒██   ██░░ ▓██▓ ░ ░ ▓██▓ ░ ▒▓█  ▄ ▒██▀▀█▄  " << endl <<
    "░▒▓███▀▒░██░ ▓█   ▓██▒▒██░   ▓██░  ▒██▒ ░    ░ ████▓▒░  ▒██▒ ░   ▒██▒ ░ ░▒████▒░██▓ ▒██▒" << endl <<
    " ░▒   ▒ ░▓   ▒▒   ▓▒█░░ ▒░   ▒ ▒   ▒ ░░      ░ ▒░▒░▒░   ▒ ░░     ▒ ░░   ░░ ▒░ ░░ ▒▓ ░▒▓░" << endl <<
    "  ░   ░  ▒ ░  ▒   ▒▒ ░░ ░░   ░ ▒░    ░         ░ ▒ ▒░     ░        ░     ░ ░  ░  ░▒ ░ ▒░" << endl <<
    "░ ░   ░  ▒ ░  ░   ▒      ░   ░ ░   ░         ░ ░ ░ ▒    ░        ░         ░     ░░   ░ " << endl <<
    "      ░  ░        ░  ░         ░                 ░ ░                       ░  ░   ░     " << endl << "";

    string command = "powershell.exe -Command \"[Environment]::GetFolderPath('MyDocuments')\"";
    string output = executePowerShellCommand(command);
    cout << "Your document folder: " << output << endl;
    
    cout << "You got ottered big time!" << endl << "Pteronura brasiliensis";
    do {
    cout << '\n' << "Press a key to continue...";
    } while (cin.get() != '\n');

    return 0;
}