int latchPin = 12;
int clockPin = 11;
int dataPin = 13;
const int COUNT = 2;
byte ledStatus[COUNT]= {0}; 

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void fillValueToArray(byte value) {
  for (int i = 0;i < COUNT; i += 1) {
    ledStatus[i] = value;
  }
}

void TshiftOutHC595(int dataPin, int clockPin, byte ledStatus[]) {
  digitalWrite(latchPin, LOW);
  
  for (int i = 0; i < COUNT; i++) {
    shiftOut(dataPin,clockPin,MSBFIRST,ledStatus[i]);  
  }
  
  digitalWrite(latchPin, HIGH);
}

void PshiftOutHC595(int dataPin, int clockPin, byte ledStatus[]) {
  digitalWrite(latchPin, LOW);
  
  for (int i = 0; i < COUNT; i++) {
    shiftOut(dataPin,clockPin,LSBFIRST,ledStatus[i]);  
  }
  
  digitalWrite(latchPin, HIGH);
}

void loop() { 
  {
    fillValueToArray(0);
  for (int i = COUNT - 1; i >= 0 ; i--) {
    for (byte j=0;j<8;j++) {
      ledStatus[i] = (ledStatus[i] << 1) | 1;
      TshiftOutHC595(dataPin,clockPin,ledStatus);
      delay(100);
    }    
  }
  for (int i = COUNT - 1; i >= 0 ; i--) {
    for (byte j=0;j<8;j++) {
      ledStatus[i] = (ledStatus[i] << 1);
      TshiftOutHC595(dataPin,clockPin,ledStatus);
      delay(100);
    }    
  }
  }
 {
  fillValueToArray(0);
  for (int i = 0; i < COUNT; i++) {
    for (byte j=0;j<8;j++) {
      ledStatus[i] = (ledStatus[i] << 1) | 1;
      PshiftOutHC595(dataPin,clockPin,ledStatus);
      delay(100);
    }    
  }
  for (int i = 0; i < COUNT; i++) {
    for (byte j=0;j<8;j++) {
      ledStatus[i] = (ledStatus[i] << 1);
      PshiftOutHC595(dataPin,clockPin,ledStatus);
      delay(100);
    }    
  } 
 }
}
