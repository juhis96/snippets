#include <windows.h>
#include <iostream>
#include <random>

using namespace std;

int main(){
    cout <<
    "                                           " << endl << 
    " _ _ _         _   _____         _____     " << endl << 
    "| | | |___ ___| |_|  _  |___ _ _|     |___ " << endl << 
    "| | | | . |  _| '_|   __|_ -| | |  |  | . |" << endl << 
    "|_____|___|_| |_,_|__|  |___|_  |_____|  _|" << endl << 
    "                            |___|     |_|  " << endl << 
    "Workplace Psychological Operation v0.1" << endl;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(50, 1000);

    while(true){
        int randomValue = dist(gen);
        cout << randomValue << endl;
        Beep(randomValue, randomValue);
        Sleep(randomValue);
    }
}