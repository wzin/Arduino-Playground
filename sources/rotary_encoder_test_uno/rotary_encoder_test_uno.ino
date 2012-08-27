//encoder(PIN A) -> A0
//encoder(PIN B) -> A1
//*PIN A and B are located on the both sides of encoder
//encoder(PIN MIDDLE) -> ground
/* Rotary encoder read example */
#define ENC_A 10  
#define ENC_B 11
#define ENC_PORT PINE
int magicnumber = 2;
 
void setup()
{
  /* Setup encoder pins as inputs */
  pinMode(ENC_A, INPUT);
  digitalWrite(ENC_A, HIGH);
  pinMode(ENC_B, INPUT);
  digitalWrite(ENC_B, HIGH);
  Serial.begin (9600);
  Serial.println("Start");
}
 
void loop()
{
 static uint8_t counter = 0;    //this variable will be changed by encoder input
 int8_t tmpdata;
 /**/
  tmpdata = read_encoder();
  if( tmpdata ) {
  switch (counter) {
    case 0:
      if (tmpdata == +1 ) {
      Serial.print("Counter value: ");
      Serial.println(counter, DEC);
      counter += tmpdata*magicnumber;
      break;
      }
      if (tmpdata == -1) {
      Serial.print("Counter value: ");
      Serial.println(counter, DEC);
      break;
      }
    case 255:
      if (tmpdata == -1 ) {
      Serial.print("Counter value: ");
      Serial.println(counter, DEC);
      counter += tmpdata*magicnumber;
      break;
      }
      if (tmpdata == +1) {
      Serial.print("Counter value: ");
      Serial.println(counter, DEC);
      break;
      }
    case 254:
      if (tmpdata == -1 ) {
      Serial.print("Counter value: ");
      Serial.println(counter, DEC);
      counter += tmpdata*magicnumber;
      break;
      }
      if (tmpdata == +1) {
      Serial.print("Counter value: ");
      Serial.println(counter, DEC);
      break;
      }
    default:
      Serial.print("Counter value: ");
      Serial.println(counter, DEC);
      counter += tmpdata*magicnumber;   
  }
  }  
}
 
/* returns change in encoder state (-1,0,1) */
int8_t read_encoder()
{
  static int8_t enc_states[] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};
  static uint8_t old_AB = 0;
  /**/
  old_AB <<= 2;                 //remember previous state
  old_AB |= ( ENC_PORT & 0x03 );  //add current state
  return ( enc_states[( old_AB & 0x0f )]);
}
