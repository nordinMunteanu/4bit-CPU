#define NOMINMAX
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

const int default_color = 7;
const int error_color = 4;
const int comment_color = 6;
const int success_color = 10;

int main(int argc, char *argv[]){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, comment_color);
	std::cout<<"\tRunning precompilation subroutine...\n";
	std::ifstream fin(argv[1]);
	std::ofstream fout("compilable.2p4");

	if(!fin.is_open()){
		SetConsoleTextAttribute(hConsole, error_color);
		std::cout<<"\tError: file not found\n";
		SetConsoleTextAttribute(hConsole, default_color);
		return 0;
	}

	std::string line;
	
	int i = 0;

	while(getline(fin, line)){
		std::transform(line.begin(), line.end(), line.begin(), ::toupper);
		if(line.size()!=0 && line[0] != ';')
			fout<<'<'<<line<<'>';
	}

	SetConsoleTextAttribute(hConsole, success_color);
	std::cout<<"\tDone!\n";
	SetConsoleTextAttribute(hConsole, default_color);

	return 0;
}