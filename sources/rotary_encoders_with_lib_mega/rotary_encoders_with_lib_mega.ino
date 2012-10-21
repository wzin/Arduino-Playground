int EncoderConnectedPins[16] = {22,23,24,25,26,27,28,29,30,31,32,34,35,36,37,38};
int PinState[16] = {};
int EncoderState[8] = {}; // We should read it from ableton on init

int NumberOfPins = sizeof(EncoderConnectedPins)/sizeof(int);
int NumberOfPhysicalEncoders = (NumberOfPins)/2;


//setup functions

void SetupDigitalInputs(){
  int state;
  int i;
  Serial.println("Setting physical inputs and pullup resistors");
   for (i=0;  i < NumberOfPins ; i++ ) { // setting HIGH state on pins
    Serial.print(EncoderConnectedPins[i]);
    Serial.print(","); 
    pinMode(EncoderConnectedPins[i], INPUT);
    digitalWrite(EncoderConnectedPins[i], HIGH);
  }
  Serial.println();
  
  Serial.print("   Inputs set to:"); 
  for (i=0;  i < NumberOfPins ; i++ ) { // Checking whether we have really set HIGH states on inputs
    
    state = digitalRead(EncoderConnectedPins[i]);
    Serial.print("PIN");Serial.print(i);Serial.print("->");Serial.print(state);Serial.print(";");   
  
  }  
  Serial.println();
  
  Serial.print("PinStates set to:");
  for (i=0 ; i < NumberOfPins ; i++ ) {
    PinState[i] = 0;
    Serial.print("PIN");Serial.print(i);Serial.print("->");Serial.print(PinState[i]);Serial.print(";");
    PinState[i+1] = 0;
    Serial.print("PIN");Serial.print(i+1);Serial.print("->");Serial.print(PinState[i+1]);Serial.print(";");
    i++;
  }
  Serial.println();
  Serial.println("------Done-------");
}

//end of setup functions

void setup() {

  Serial.begin(115200);
  SetupDigitalInputs();

}

int i;
int stateA;
int stateB;


void loop() {
   for (i=0;  i < NumberOfPins ; i++ ) {
    // i holds the index of current encoder
    stateA = digitalRead(EncoderConnectedPins[i]);
    stateB = digitalRead(EncoderConnectedPins[i+1]);
    if ((stateA != PinState[i]) | (stateB != PinState[i+1])) {   // Main logic
      Serial.print("PINA(");Serial.print(EncoderConnectedPins[i]);Serial.print(")");Serial.print("->");Serial.print(stateA);Serial.print("->previous(");Serial.print(PinState[i]);Serial.print(")");
      Serial.println();
      Serial.print("PINB(");Serial.print(EncoderConnectedPins[i+1]);Serial.print(")");Serial.print("->");Serial.print(stateB);Serial.print("->previous(");Serial.print(PinState[i+1]);Serial.print(")");   
      Serial.println();
    } // end of main logic 
    
      PinState[i] = stateA; // saving state of encoder A
      PinState[i+1] = stateB; // saving state of encoder B
      i++;
    }  
   // Saving state
  delay(6);
}





  
 
