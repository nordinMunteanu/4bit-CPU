#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <cstring>
#include <sys/select.h>
#include <stdexcept>

#include "serialport.hpp"


int main() {
    std::ifstream fin("compf_out.2p4hex");
    int losses = 0;

    if(!fin.is_open()){
        std::cout<< "\033[31mFile compf does not exist: ";
        std::cout<< "\033[4mF000\n";
        return 1;
    }
    if(fin.peek() == std::ifstream::traits_type::eof()){
        std::cout<< "\033[31mFile compf is empty: ";
        std::cout<< "\033[4mF001\n";
        return 1;
    }
    std::cout<<"\n";

    try {
        SerialPort arduino("/dev/ttyUSB0", B9600);

        try {
            std::string setupMessage = arduino.readLine(3);
            std::cout << "\033[36mProgrammer status: " << setupMessage;
        } catch (const std::exception& e) {
            std::cerr << "\033[31mNo setup message received: " << e.what();
            return 1;
        }

        arduino.flushInput();

        std::cout << "\033[32mConnected to Programmer, beginning transmission\n\n";

        std::string input;
        while (fin>>input) {
            if(input[0] == '-'){
                if(input[1] == '0'){
                    std::cout<<"\033[32m\nReached end of compf with code 0\n";
                } else{
                    std::cout<<"\033[36m\nReached end of compf with code: "<<input[1]<<"\n";
                }
                std::cout<<"\033[36mlosses: "<<losses<<"\033[0m\n\n";
                return 0;
            }

            arduino.writeString(input);

            try {
                std::string response = arduino.readLine();
                std::cout << "\033[0mProgrammer output: " << response << "\n";
                
                response.push_back('>');
                std::reverse(response.begin(), response.end());
                response.push_back('<');
                std::reverse(response.begin(), response.end());

                if(response == input){
                    std::cout<<"\033[0mOutput coherrent\n";
                } else{
                    std::cout<<"\033[31mOutput incoherrent\n";
                    losses++;
                }

            } catch (const std::exception& e) {
                std::cerr << "\033[31mTransmission error: " << e.what() << "\n\n";
                return 1;
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "\033[31mError: " << e.what() << "\n\n";
        return 1;
    }

    fin.close();

    return 0;
}