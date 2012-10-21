
int ledPin = 13;
int knockSensor = 0;               
byte val = 0;
int statePin = LOW;
int THRESHOLD = 100;

void setup() {
 pinMode(ledPin, OUTPUT); 
 beginSerial(9600);
}

void loop() {
  val = analogRead(knockSensor);     
  if (val >= THRESHOLD) {
    statePin = !statePin;
    digitalWrite(ledPin, statePin);
    printString("Knock!");
    printByte(10);
    printByte(13);
  }
  delay(100);  // we have to make a delay to avoid overloading the serial port
}


int knockSensor = 0
void setup() {
  
