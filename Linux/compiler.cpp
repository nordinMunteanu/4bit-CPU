#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

std::vector<std::string> instr_names = {
    "FLG", "ADD", "SUB", "INC", "DEC",
    "SHL", "NOT", "AND", "ORR", "XOR",
    "SET", "SRT", "JMP", "GOF", "GOT",
    "RET", "LBL", "BPZ"
};

std::vector<int> instr_codes = {
    0, 1, 1, 1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14
};

std::string trim(const std::string& str) {
    auto start = str.begin();
    while (start != str.end() && std::isspace(*start)) {
        start++;
    }
    auto end = str.end();
    do {
        end--;
    } while (std::distance(start, end) > 0 && std::isspace(*end));
    return std::string(start, end + 1);
}

bool isEndMarker(const std::string& str) {
    return trim(str) == "-0";
}

int binaryToInt(const std::string& binStr) {
    try {
        size_t pos;
        std::string processed = binStr;
        if (binStr.size() > 2 && binStr[1] == 'B') {
            processed = binStr.substr(2);
        }
        int num = std::stoi(processed, &pos, 2);
        if (pos != processed.length()) {
            throw std::invalid_argument("\033[36mInvalid binary detected: C022\n");
        }
        return num;
    } catch (...) {
        throw std::invalid_argument("\033[36mInvalid binary detected: C020\n");
    }
}

int hexToInt(const std::string& hexStr) {
    try {
        size_t pos;
        std::string processed = hexStr;
        if (hexStr.size() > 2 && hexStr[1] == 'X') {
            processed = hexStr.substr(2);
        }
        int num = std::stoi(processed, &pos, 16);
        if (pos != processed.length()) {
            throw std::invalid_argument("\033[36mInvalid binary detected: C012\n");
        }
        return num;
    } catch (...) {
        throw std::invalid_argument("\033[36mInvalid hex detected: C010\n");
    }
}

int strToNum(const std::string& numStr) {
    if (numStr.empty()) {
        throw std::invalid_argument("\033[31mEmpty number detected: C102\n");
    }

    try {
        if (numStr.size() > 1 && numStr[0] == '0') {
            if (numStr[1] == 'b' || numStr[1] == 'B') {
                return binaryToInt(numStr);
            } else if (numStr[1] == 'x' || numStr[1] == 'X') {
                return hexToInt(numStr);
            }
        }
        return std::stoi(numStr);
    } catch (...) {
        throw std::invalid_argument("\033[36mInvalid number format detected: C103\n");
    }
}

std::string int_to_hex(int v){
    std::string rez;
    if(v == 0) return "0";
    while(v != 0){
        int t = v%16;
        v/=16;
        rez+=(t>=10)? ('A' + t - 10):('0'+t);
    }
    reverse(rez.begin(), rez.end());
    return rez;
}

void processInstruction(const std::string& instr, std::ofstream& fout) {
    bool found = false;
    int code = -1;

    for (size_t i = 0; i < instr_names.size(); ++i) {
        if (instr == instr_names[i]) {
            code = instr_codes[i];
            found = true;
            break;
        }
    }

    if (!found) {
        throw std::invalid_argument("\033[31mInstruction not recognised: C001 (" + instr + ")\n");
    }

    fout << "<" << int_to_hex(code);
    if(instr == "SUB" || instr == "DEC"){
        fout << "+>\n";
    } else fout<< "-\n";
}

void processNumber(const std::string& numStr, std::ofstream& fout) {
    try {
        int num = strToNum(numStr);
        std::cout<<num<<'\n';
        if (num < 0) {
            throw std::out_of_range("\033[31mOverflow detected: C101\n");
        }
        fout << "<" << int_to_hex(num) << ">\n";
    } catch (const std::exception& e) {
        throw;
    }
}

int main() {
    std::ifstream fin("compf.2p4fab");
    if (!fin.is_open()) {
        std::cerr << "\033[31mFailed to open input file: F100\n";
        return 1;
    }

    std::ofstream fout("compf.2p4hex");
    if (!fout.is_open()) {
        std::cerr << "\033[31mFailed to open output file F100\n";
        return 1;
    }

    std::cout << "\033[36mBeginning compilation\n";

    std::string line;
    bool compilationSuccess = true;

    while (getline(fin, line)) {
        line = trim(line);

        if (line.empty()) {
            continue;
        }

        if (isEndMarker(line)) {
            break;
        }

        try {
            if (line[0] >= 'A' && line[0] <= 'Z') {
                processInstruction(line, fout);
            } else {
                processNumber(line, fout);
            }
        } catch (const std::exception& e) {
            std::cerr << e.what();
            compilationSuccess = false;
            // Continue processing but mark as failed
        }
    }


    if (compilationSuccess) {
        std::cout << "\033[32mCompilation successful!\n";
        fout<<"-0";
        return 0;
    } else {
        std::cerr << "\033[31mCompilation completed with errors\n";
        fout<<"-1";
        return 1;
    }

    fin.close();
    fout.close();

    std::cout<<"\033[0m\n";

    return 0;
}
