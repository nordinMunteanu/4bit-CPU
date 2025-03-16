#define NOMINMAX
#include <windows.h>
#include <iostream>

int main(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    SetConsoleTextAttribute(hConsole, 10);
    std::cout<<"Done!\n";
    SetConsoleTextAttribute(hConsole, 7);
    
    return 0;
}