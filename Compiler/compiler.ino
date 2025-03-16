// Example 3 - Receive with start- and end-markers

const byte numChars = 32;
char receivedChars[numChars];

boolean newData = false;


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

void setup() {
    Serial.begin(9600);
    Serial.println("<Arduino is ready>");
}

void loop() {
    recvWithStartEndMarkers();
    showNewData();
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
                receivedChars[ndx] = '\0'; // terminate the string
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

bool isEql(char a[], char b[]){
    for(int i = 0; i < 3; i++){
        if(a[i] != b[i]){
            return false;
        }
    }
    return true;
}

int returnVal(int&val, int&flag){
  flag = 0;
  for(int i = 0; i < 18; ++i){
    if(isEql(receivedChars, instructions[i])){
      val = instr_codes[i];
      if(i == 2 || i == 4) flag = 1;
      else flag = 0;
      return 0;
    }
  }
  val = -1;
  flag = -1;
  return -1;
}

void showNewData() {
    if (newData == true) {
        Serial.print("Received: ");
        Serial.println(receivedChars);

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