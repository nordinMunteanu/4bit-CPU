#if defined _WIN32 || defined _WIN64
#define NOMINMAX
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>

const int default_color = 7,
          error_color = 4,
          comment_color = 6,
          success_color = 10;

bool is_empty(std::ifstream& pFile)
{
    return pFile.peek() == std::ifstream::traits_type::eof();
}

int main(int argc, char *argv[])
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, comment_color);
    std::cout<<"Running pre-compilation subroutine\n";
    std::ifstream fin(argv[1]);

    fin>>std::ws;

    std::ofstream fout("compf.2p4hex");

    if(!fin.is_open()){
        SetConsoleTextAttribute(hConsole, error_color);
        std::cout<<"Error: file not found: F1000";
        SetConsoleTextAttribute(hConsole, default_color);
        return 1;
    }
    if(is_empty(fin)){
        SetConsoleTextAttribute(hConsole, error_color);
        std::cout<<"Error: file is empty: F0000";
        SetConsoleTextAttribute(hConsole, default_color);
        fout<<"-1";
        return 1;
    }

    std::string line;
    int i = 0;
    int countInputs = 0;

    while(getline(fin, line)){
		std::transform(line.begin(), line.end(), line.begin(), ::toupper);
		if(line.size()!=0 && line[0] != ';'){
            std::vector<std::string>tokens;
            std::stringstream check1(line);

            std::string intermediate;

            while(getline(check1, intermediate, ' ')){
                tokens.push_back(intermediate);
            }


            for(auto i : tokens){

                if(i[0] == 'R' && i[1] >='0' && i[1] <= '9'){
                    countInputs--;
                    i.erase(i.begin()+0);
                }

                if(i[0] >='A' && i[0] <= 'Z'){
                    if(countInputs <= 0){
                        countInputs = 2;
                    }
                    else{
                        while(countInputs){
                            countInputs --;
                            fout<<"<0>";
                        }
                    }

                    fout<<"<"<<i<<'>';
                }

                if(i[0] >= '0' && i[0] <= '9'){
                    fout<<"<"<<i<<'>';
                    countInputs--;
                }

            }
        }
    }

    fout<<"\n-0";

    SetConsoleTextAttribute(hConsole, success_color);
    std::cout<<"Pre-compilation successful!";
    SetConsoleTextAttribute(hConsole, default_color);

    return 0;
}
#else

#include <iostream>

int main(){
    std::cout<<"Error: wrong operating system detected: W0000\n";
    return 1;
}
#endif
