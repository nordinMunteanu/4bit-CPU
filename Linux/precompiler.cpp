#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>


int main(int argc, char* argv[]){
    std::cout<<"\033[36mRunning precompilation subroutine\n";

    std::ifstream fin(argv[1]);
    std::ofstream fout("compf.2p4fab");

    fin>>std::ws;

    auto check_extension = [&](){
        std::string extension(".2p4");
        std::string str(argv[1]);
        std::size_t found = str.find(extension);
        if(found == std::string::npos) return 0;
        else return 1;
    };
    
    if(!check_extension()){
        std::cout<<"\033[31mWrong file type: ";
        std::cout<<"\033[4mF020\n";
        return 1;
    }

    if(!fin.is_open()){
        std::cout<< "\033[31mCompilable does not exist: ";
        std::cout<< "\033[4mF010\n";
        return 1;
    }
    if(fin.peek() == std::ifstream::traits_type::eof()){
        std::cout<< "\033[31mCompilable is empty: ";
        std::cout<< "\033[4mF011\n";
        return 1;
    }

    std::string line;
    int i = 0;
    int countInputs = 0;

    while(getline(fin, line)){
		std::transform(line.begin(), line.end(), line.begin(), ::toupper);
		if(line.size()!=0 && line[0] != ';'&&line[0] != '\n' && line[0] != ' '){
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
                    while(countInputs){
                        countInputs --;
                        fout<<"0\n";
                    }
                    countInputs = 2;
                    fout<<i<<"\n";
                }

                if(i[0] >= '0' && i[0] <= '9'){
                    fout<<i<<'\n';
                    countInputs--;
                }

            }
        }
    }

    fout<<"-0";
    std::cout<<"\033[32mPrecompilation subroutine successful!\n";

    fin.close();
    fout.close();
    std::cout<<"\033[0m\n";
    return 0;
}