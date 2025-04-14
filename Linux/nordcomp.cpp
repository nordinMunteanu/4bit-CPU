#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <cstring>
#include <map>

std::map<std::string, int> v = {
    {"c", 0},
    {"help", 1},
    {"k-fab", 2},
    {"k-hex", 3},
    {"k-comp", 4},
    {"k-precomp", 5},
    {"k-upl", 6}
};

int main(int argc, char* argv[]){
    int comv[7] = {0};

    if(argc < 1){
        std::cout<<"Not enough arguments. Use --help for a list of commands";
    }
    else{
        for(int i = 1; i <= argc; ++i){
            std::string com(argv[i]);
            if(com[0] == '-'){
                if(com[1] == '-'){
                    com.erase(com.begin()+1);
                    comv[v[com]]++;
                }
                else {
                    com.erase(com.begin());
                    while(!com.empty()){
                        std::string com2(1, com[0]);
                        comv[v[com2]]++;
                        com.erase(com.begin());
                    }
                }
            }
            else std::cout<<"Wrong argument format\n";
        }
    }

    for(int i = 0; i < 7; ++i){
        std::cout<<comv[i]<<' ';
    }
    std::cout<<'\n';

    return 0;
}
