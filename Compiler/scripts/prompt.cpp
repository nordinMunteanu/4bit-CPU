#define NOMINMAX
#include <windows.h>
#include <iostream>

int main(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    SetConsoleTextAttribute(hConsole, 6);
    std::cout<<"Enter the name of the file to be compiled: ";
    SetConsoleTextAttribute(hConsole, 7);
    
    return 0;
}