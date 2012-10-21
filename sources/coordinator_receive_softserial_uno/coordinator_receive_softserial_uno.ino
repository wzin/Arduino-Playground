#- piny na coordinatorze sa podlaczone DIN -> TX (pin 3) , DOUT->RX (pin 2)
#
#http://arduino.cc/hu/Reference/SoftwareSerial < manual softserial
#
#--------------------------------------------- 
#include <SoftwareSerial.h>

SoftwareSerial xbee2(2, 3); // RX, TX 

void setup()
{
Serial.begin(9600);
xbee2.begin(9600);
 }

void loop()
{
if (xbee2.available())
    Serial.write(xbee2.read());
}
