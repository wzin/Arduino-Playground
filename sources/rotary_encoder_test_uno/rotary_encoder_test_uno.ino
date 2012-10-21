int encoderPins[] = {22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52}; // definicja tablicy z numerami pinow
int numberOfPins = sizeof(encoderPins)/sizeof(int); // ilosc elementow tablicy encoderPins czyli ilosc pinow
int numberOfEncoders = numberOfPins/2;
int encoderState[] = {0}; // stan wartosci inkrementalnej encodera midi 0-255
int pinHistory[] = {0}; // binarny stan na danym pinie
int counter = 0;    //this variable will be changed by encoder input
int readDataA;  //tymczasowa wartosc na aktualne zczytanie pinu A
int readDataB;  //tymczasowa wartosc na aktualne zczytanie pinu B
int pinA; //Zmienna uzywana lokalnie do pinu A 
int pinB; //Zmienna uzywana lokalnie do pinu B
int i = 0; // blah i
int a = 0; // blah a


// SETUP FUNCTIONS
void setupEncoderMatrix() {
Serial.println("Cleaning logical encoder counters");
for(i=0 ; i <= numberOfEncoders ; i++) { 
  Serial.print(i);
  Serial.print(",");
  encoderState[i] = 0; 
  }
  Serial.println("Done.");
} 
void setupDigitalInputs(){
  Serial.println("Setting physical inputs and pullup resistors");
  for (i=0;  i < numberOfPins ; i++ ) {
    Serial.print(encoderPins[i]);
    Serial.print(","); 
    pinMode(encoderPins[i], INPUT);
    digitalWrite(encoderPins[i], HIGH);
  }
  Serial.println("Done.");
}
void setupPinHistory() {
Serial.println("Cleaning logical pin states history");
for(i=0 ; i < numberOfPins ; i++) { 
  Serial.print(i);
  Serial.print(",");
  pinHistory[i] = 0; 
  }
Serial.println("Done.");
} 

// END OF SETUP FUNCTIONS

void setup()
{ 
  Serial.begin (115200);
  Serial.println("BLAH -----------------> Start");
  Serial.print("Number of pins that we use:"); Serial.println(numberOfPins);
  Serial.print("We have this number of encoders:");Serial.println(numberOfPins/2);
  setupDigitalInputs();
  setupEncoderMatrix();
  setupPinHistory();
}
 
void loop()
{
  for (i=0 ; i <= numberOfPins ; i++  ) {
  pinA = i;
  pinB = i+1;
  i++;
  readDataA = digitalRead(encoderPins[pinA]);
  readDataB = digitalRead(encoderPins[pinB]);
  if ( readDataA != pinHistory[pinA] | readDataB != pinHistory[pinB] ) {
    Serial.print("PIN number: "); Serial.print(encoderPins[pinA]); Serial.print("/current state : "); Serial.print(readDataA); Serial.print("/previous:"); Serial.println(pinHistory[pinA]);
    Serial.print("PIN number: "); Serial.print(encoderPins[pinB]); Serial.print("/current state : "); Serial.print(readDataB); Serial.print("/previous:"); Serial.println(pinHistory[pinB]);
    pinHistory[pinA] = readDataA;
    pinHistory[pinB] = readDataB;
  }  
  }
  delay(1000);
  Serial.println("---------------");
  
}
