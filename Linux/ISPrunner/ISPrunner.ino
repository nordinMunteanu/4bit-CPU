#include <Arduino.h>

const i0 = 1, i1= 2, i2 = 3, i3 = 4, data = 10, clock = 11, latch = 12, reset = 9, enable = 8;

const byte numChars = 32;

char receivedChars[numChars];

boolean newData = false;

uint16_t instr, a, b, y;


void setup() {
    pinMode(i0, INPUT);
    pinMode(i1, INPUT);
    pinMode(i2, INPUT);
    pinMode(i3, INPUT);

    pinMode(data, OUTPUT);
    pinMode(latch, OUTPUT);
    pinMode(clock, OUTPUT);
    pinMode(reset, OUTPUT);
    pinMode(enable, OUTPUT);

    digitalWrite(reset, 1);
    digitalWrite(enable, 1);

    Serial.begin(9600);
    Serial.println("<Arduino is ready>");
}

void loop() {
    recvWithStartEndMarkers();
    showNewData();
    instr = hexToInt(receivedChars);
    if(receivedChars[1] == '+'){
        y = 0b1111;
    }
    else y = 0b1110;

    recvWithStartEndMarkers();
    showNewData();
    a = hexToInt(receivedChars);

    recvWithStartEndMarkers();
    showNewData();
    b = hexToInt(receivedChars);

    uint16_t val = 0b0;
    val |= (y<<12) | (instr<<8) | (a<<4) | b;

    sendReg();

    digitalWrite(enable, 0);
    delay(100);

    int outp = 0b0;
    outp |= digitalRead(i3), outp = outp << 1;
    outp |= digitalRead(i2), outp = outp << 1;
    outp |= digitalRead(i1), outp = outp << 1;
    outp |= digitalRead(i0);
    Serial.print("~~");
    Serial.print(outp);
    Serial.print("~~\n");

    digitalWrite(enable, 1);
    digitalWrite(reset, 0);
    delay(1);
    digitalWrite(reset, 1);
}

void sendReg(uint16_t v){
    digitalWrite(latch, 0);
    shiftOut(data, clock, LSBFIRST, v);
    shiftOut(data, clock, LSBFIRST, v>>8);
    digitalWrite(latch, 1);
}


int hexToInt(char chars[]){
    if(chars[0] >= '0' && chars[0] <= '9'){
        return (chars[0] - '0');
    }
    else if(chars[0] >= 'A' && chars[0] <= 'F'){
        return (chars[0] - 'A');
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
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0';
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
        Serial.print(receivedChars);
        Serial.print("\n");
        newData = false;
    }
}
