#include <Arduino.h>
#include <stdlib.h>
const byte numChars = 32;
char data[numChars];

void setup()
{
	Serial.begin(9600);
	Serial.println("<Programmer is ready>");
}

void loop()
{
    recvWithStartEndMarkers();
    showNewData();
    switch data[0]{
    
    int op = -1, flag = -1, aval = -1, bval = -1, yval;
    
    flag = readFlag();
    
    if(data[0] == '@'){
        op = setInstructions(yval);
        if(op == 0){
            Serial.println(flag);
        }
        if(op == 2 || op == 4 || op == 5 || op == 6){
            recvWithStartEndMarkers();
            aval= setVal();
            recvWithStartEndMarkers();
            bval= setVal();
            
        }
    }
}

void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;

    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                data[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                data[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}
void showNewData() {
    if (newData == true) {
        Serial.print("Received: ");
        Serial.println(data);

        int val;
        int flag;

        returnVal(val, flag);

        Serial.print("To send: ");
        Serial.print(val);
        Serial.print(' ');
        Serial.println(flag);

        newData = false;
    }
}


int readFlag(){
}

int setInstruction(int &flag){
    char instructions[18][3] = {
    {'E', 'Q', 'L'},
    {'A', 'D', 'D'},
    {'S', 'U', 'B'},
    {'I', 'N', 'C'},
    {'D', 'E', 'C'},
    {'S', 'H', 'L'},
    {'S', 'H', 'R'},
    {'N', 'O', 'T'},
    {'A', 'N', 'D'},
    {'O', 'R', 'R'},
    {'X', 'O', 'R'},
    {'S', 'E', 'T'},
    {'S', 'R', 'T'},
    {'J', 'M', 'P'},
    {'G', 'O', 'T'},
    {'R', 'E', 'T'},
    {'L', 'B', 'L'},
    {'G', 'R', 'T'}
    };
    int instr_codes[18] = {
        0x00,
        0x01,
        0x01,
        0x02,
        0x02,
        0x03,
        0x04,
        0x05,
        0x06,
        0x07,
        0x08,
        0x09,
        0x0A,
        0x0B,
        0x0C,
        0x0D,
        0x0E,
        0X0F
    };
    int val;
    bool isEql = [](char a[], char b[]) {
        for(int i = 1; i < 4; i++){
            if(a[i] != b[i]){
                return false;
            }
        }
        return true;
    }
    
    flag = 0;
    
    for(int i = 0; i < 16; ++i){
        if(isEql(data, instructions[i])){
            val = instr_codes[i];
            if(val == 2 || val == 4){
                flag = 1;
            }
            return 0;
        }
        
        flag = val = -1;
        return -1;
    }
}
int setVal(){
    data[0] = '+';
    int val = atoi(data);
    return val;
}
