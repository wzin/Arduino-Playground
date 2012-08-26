#include <SoftwareSerial.h>
SoftwareSerial xbee2(4, 3); // RX, TX
int inPin = 2;         // the number of the input pin
int outPin = 13;       // the number of the output pin
int state = HIGH; // the current state of the output pin
int previous_state ;
int reading;           // the current reading from the input pin
int previous = LOW;    // the previous reading from the input pin
// the follow variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long time = 0;         // the last time the output pin was toggled
long debounce = 200;   // the debounce time, increase if the output flickers
void setup()
{
  pinMode(inPin, INPUT);
  pinMode(outPin, OUTPUT);
  xbee2.begin(9600);
  Serial.begin(9600);
}
void loop()
{
  reading = digitalRead(inPin);
  // if the input just went from LOW and HIGH and we've waited long enough
  // to ignore any noise on the circuit, toggle the output pin and remember
  // the time
  if (reading == HIGH && previous == LOW && millis() - time > debounce) {
    if (state == HIGH)
      state = LOW;
    else
      state = HIGH;
    time = millis();    
  }

  digitalWrite(outPin, state);
  if (reading != previous) {
  if (state == HIGH)
  {
      overdrive_on();
}
  else {
      overdrive_off();
  }
  }
  previous = reading;
  delay(100);
}
void overdrive_on(){
      xbee2.write(0xB0); // MIDI control change; channel 3
      xbee2.write(0x29); // MIDI controller #1
      xbee2.write((byte)0x00); // MIDI controller value of 127
      Serial.println("on");
}

void overdrive_off(){
      xbee2.write(0xB0); // MIDI control change; channel 3
      xbee2.write(0x29); // MIDI controller #1
      xbee2.write(0x7F); // MIDI controller value of 127
      Serial.println("off");
}
