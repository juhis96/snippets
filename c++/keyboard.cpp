#include <windows.h>
#include <unistd.h>

int main()
{
    int delay = 5;
    bool quit = false;

    while(!quit){
        INPUT inputs[2] = {};
        ZeroMemory(inputs, sizeof(inputs));   
        inputs[0].type = INPUT_KEYBOARD;
        inputs[0].ki.wVk = VK_F5;

        inputs[1].type = INPUT_KEYBOARD;
        inputs[1].ki.wVk = VK_F5;
        inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

        SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));

        sleep(delay);
        quit = GetAsyncKeyState(VK_F6);
    }
}