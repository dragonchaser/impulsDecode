int pin = 2;
uint8_t dialResult = 0;
uint8_t previousReadValue = 0;
uint8_t bouncedialResult = 0;
void setup() {
  Serial.begin(9600);
  pinMode(pin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(pin), isrDial, CHANGE); 
}

void loop() {
  
}

void isrDial() {
  do {
    uint8_t data = digitalRead(pin);
    if(data == 1 && data != previousReadValue) {
      ++dialResult;
    }
    if(data == 0 && data == previousReadValue) {
      ++bouncedialResult;
      delay(150);
    }
    if(bouncedialResult > 200) {
      if(dialResult > 1) {
        Serial.print("dialResult: ");
        Serial.println(dialResult-1);
      }
      dialResult = 0;
      bouncedialResult = 0;
    }
    previousReadValue = data;
    delay(5);
  } while(dialResult > 0);
}


