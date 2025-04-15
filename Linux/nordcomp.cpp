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

std::map<int, std::string> vrev = {
    {0, "c"},
    {1, "help"},
    {2, "k-fab"},
    {3, "k-hex"},
    {4, "k-comp"},
    {5, "k-precomp"},
    {6, "k-upl"}
};


int main(int argc, char* argv[]){
    int comv[7] = {0};

    if(argc < 1){
        std::cout<<"Not enough arguments. Use --help for a list of commands";
    }
    else{
        for(int i = 1; i < argc; ++i){
            std::string com(argv[i]);

            if(com[0] == '-'){
                if(com[1] == '-') {
                    com.erase(com.begin());
                    com.erase(com.begin());
                    if(v[com] == 0){
                        std::cout<<"Unknown argument\n";
                        return 2;
                    }
                    comv[v[com]]++;
                }
                else{
                    com.erase(com.begin());
                    for(int j = 0; j < com.size(); ++j){
                        std::string tmp(1, com[j]);
                        if(v[tmp] == 0 && tmp != "c"){
                            std::cout<<"Unknown argument\n";
                            return 2;
                        }
                        comv[v[tmp]]++;
                    }
                }
            }
            else{
                 std::cout<<"Invalid argument format\n";
                 return 1;
            }
        }
    }

    std::string instr("./runner.sh ");

    for(int i = 0; i < 7; ++i){
        if(comv[i] > 1){
            std::cout<<"Invalid argument repetition\n";
            return 3;
        }

        if(comv[i] != 0){
            instr+=vrev[i];
            instr+=" ";
            comv[i]--;
        }else{
            instr+="0 ";
        }
    }

    std::cout<<instr<<'\n';

    return 0;
}
