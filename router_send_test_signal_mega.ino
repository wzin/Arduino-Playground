void setup()
{
 Serial.begin(9600);
 Serial1.begin(9600);
}

void loop()
{
 Serial.println("Hello USB");
 Serial1.println("What");
 delay(1000);
}
