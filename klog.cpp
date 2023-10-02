#include <iostream>
#include <fstream>


int main(){
    // open or create a text file in append mode
    std::ofstream keylog("log.txt", std::ios::app);

    // if the file didn't open, shut the program down
    if (!keylog.is_open()){
        return 1;
    }



    keylog << "hello world";


    std::cout << "hello world";



    keylog.close();

    return 0;
}