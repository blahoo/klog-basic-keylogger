#include <iostream>
#include <fstream>
#include <windows.h>


int main(){

    // Get the console window handle
    HWND consoleWindow = GetConsoleWindow(); 

    // Check if console window handle retrieved
    if (consoleWindow != NULL) {

        // Hide the console window
        ShowWindow(consoleWindow, SW_HIDE);

        // open or create a text file in append mode
        std::ofstream keylog("log.txt", std::ios::app);

        // if the file didn't open, shut the program down
        if (!keylog.is_open()){
            return 1;
        }

    




            

        // Add a delay to avoid high CPU usage (you can adjust this)
        Sleep(100);
        



        keylog << "hello world";


        std::cout << "hello world";



        keylog.close();
    }else{ return 1; }

    return 0;
}