#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <cstring>

int main(int argc, char* argv[]){
    if(std::strcmp(argv[1], "-c") == 0){
        auto joined_args = [&]() -> std::string{
            std::string result;
            for(int i = 0; i < argc; ++i){
                if(i!=0) result += " ";
                result += argv[i];
            }
            return result;
        }();
        std::printf("the arguments are:%s", joined_args.c_str());
    } else if(argv[1] == "help"){

    } else std::cout<<"Invalid argument\n";

    return 0;
}