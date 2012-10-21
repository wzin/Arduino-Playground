
#include <PinChangeInt.h>
//available pins : 10->15,50->52

#define firstPin 30
#define lastPin 32

int i ;
int count;

uint8_t latest_interrupted_pin;
uint8_t interrupt_count[lastPin]={0}; //  possible arduino pins

void quicfunc() {
  latest_interrupted_pin=PCintPort::arduinoPin;
  interrupt_count[latest_interrupted_pin]++;
}

void interruptDigitalPortSetup(int portNumber){
  pinMode(portNumber, INPUT); digitalWrite(portNumber, HIGH);
  PCintPort::attachInterrupt(portNumber, &quicfunc, CHANGE);
  Serial.print("Enabling interrupt on port number: ");Serial.println(i);
}
 
void setup() {
  /*pinMode(22, INPUT); digitalWrite(22, HIGH);
  PCintPort::attachInterrupt(22, &quicfunc, CHANGE);
  pinMode(23, INPUT); digitalWrite(23, HIGH);
  PCintPort::attachInterrupt(23, &quicfunc, CHANGE);*/
  Serial.begin(115200);
  Serial.println("---------------------------------------");
  Serial.print("firstpin:");Serial.println(firstPin);
  Serial.print("lastpin:");Serial.println(lastPin);
  
  for (i=firstPin; i < lastPin; i++ ){
  interruptDigitalPortSetup(i);
  } 
}




void loop() {

  for (i=firstPin; i < lastPin; i++) {
    if (interrupt_count[i] != 0) {
      count=interrupt_count[i];
      interrupt_count[i]=0;
      Serial.print("Count for pin ");
      if (i < 14) {
        Serial.print("D");
        Serial.print(i, DEC);
      } else {
        Serial.print("AI");
        Serial.print(i-14, DEC);
      }
      Serial.print(" is ");
      Serial.println(count, DEC);
    }
  }
}



