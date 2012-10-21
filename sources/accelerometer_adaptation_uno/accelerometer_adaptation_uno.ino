#ifndef AcceleroMMA7361_h
#define AcceleroMMA7361_h
#include <Arduino.h>

class AcceleroMMA7361
{
        public:
                AcceleroMMA7361();
                void begin();
                void begin(int sleepPin, int selfTestPin, int zeroGPin, int
gSelectPin, int xPin, int yPin, int zPin);
                int getXRaw();
                int getYRaw();
                int getZRaw();
                int getXVolt();
                int getYVolt();
                int getZVolt();
                int getXAccel();
                int getYAccel();
                int getZAccel();
                void getAccelXYZ(int *_XAxis, int *_YAxis, int *_ZAxis);
                int getTotalVector();
                void setOffSets(int xOffSet, int yOffSet, int zOffSet);
                void calibrate();               // only to be executed when Z-axis is oriented to

                                                        // it calculates the offset values by assuming  Z = +1 G ; X and Y  = 0 G
                void setARefVoltage(double _refV);
                void setAveraging(int avg);
                int getOrientation();
                void setSensitivity(boolean sensi);
                void sleep();
                void wake();

        private:
                int _mapMMA7361V(int value);
                int _mapMMA7361G(int value);
                int _sleepPin;
                int _selfTestPin;
                int _zeroGPin;
                int _gSelectPin;
                int _xPin;
                int _yPin;
                int _zPin;
                int _offSets[3];
                int _polarities[3];
                double _refVoltage;
                int _average;
                boolean _sleep;
                boolean _sensi;
};
#endif

AcceleroMMA7361::AcceleroMMA7361()
{
}

void AcceleroMMA7361::begin()
{
        begin(13, 12, 11, 10, A0, A1, A2);
}

void AcceleroMMA7361::begin(int sleepPin, int selfTestPin, int
zeroGPin, int gSelectPin, int xPin, int yPin, int zPin)
{
        pinMode(sleepPin, OUTPUT);
        pinMode(selfTestPin, OUTPUT);
        pinMode(zeroGPin, INPUT);
        pinMode(gSelectPin, INPUT);
        pinMode(xPin, INPUT);
        pinMode(yPin, INPUT);
        pinMode(zPin, INPUT);
        digitalWrite(sleepPin,HIGH);
        digitalWrite(selfTestPin,LOW);
        _sleepPin = sleepPin;
        _selfTestPin = selfTestPin;
        _zeroGPin = zeroGPin;
        _gSelectPin = gSelectPin;
        _xPin = xPin;
        _yPin = yPin;
        _zPin = zPin;
        _sleep = false;
        setOffSets(0,0,0);
        setARefVoltage(5);
        setAveraging(10);
        setSensitivity(HIGH);
}

/// <summary>
/// setOffSets( int offSetX, int offSetY, int offSetZ): Sets the

/// The parameters are the offsets expressed in G-force (100 = 1 G)
/// Offsets are added to the raw datafunctions
/// </summary>
void AcceleroMMA7361::setOffSets(int xOffSet, int yOffSet, int zOffSet)
{
        if (_refVoltage==3.3)
        {
                _offSets[0]= map(xOffSet,0,3300,0,1024);
                _offSets[1]= map(yOffSet,0,3300,0,1024);
                _offSets[2]= map(zOffSet,0,3300,0,1024);
        }
        else
        {
                _offSets[0]= map(xOffSet,0,5000,0,1024);
                _offSets[1]= map(yOffSet,0,5000,0,1024);
                _offSets[2]= map(zOffSet,0,5000,0,1024);
        }
}

/// <summary>
/// setARefVoltage(double _refV): Sets the AREF voltage to external,

/// default is 5 when no AREF is used. When you want to use 3.3 AREF,

/// 3.3 V VCC pin. This increases accuracy
/// </summary>
void AcceleroMMA7361::setARefVoltage(double refV)
{
        _refVoltage = refV;
        if (refV == 3.3)
        {
                analogReference(EXTERNAL);
        }
}

/// <summary>
/// setAveraging(int avg): Sets how many samples have to be averaged

/// </summary>
void AcceleroMMA7361::setAveraging(int avg)
{
        _average = avg;
}

/// <summary>
/// setSensitivity sets the sensitivity to +/-1.5 G (HIGH) or +/-6 G

/// </summary>
void AcceleroMMA7361::setSensitivity(boolean sensi)
{
        _sensi = sensi;
        digitalWrite(_gSelectPin, !sensi);
}

/// <summary>
/// sleep lets the device sleep (when device is sleeping already this

/// </summary>
void AcceleroMMA7361::sleep()
{
        if (!_sleep)
        {
                digitalWrite(_sleepPin, LOW);
                _sleep = true;
        }
}

/// <summary>
/// wake enables the device after sleep (when device is not sleeping


/// </summary>
void AcceleroMMA7361::wake()
{
        if (_sleep == true)
        {
                digitalWrite(_sleepPin, HIGH);
                _sleep = false;
                delay(2);
        }
}

/// <summary>
/// getXRaw(): Returns the raw data from the X-axis analog I/O port of

/// </summary>
int AcceleroMMA7361::getXRaw()
{
        return analogRead(_xPin)+_offSets[0]+2;
}

/// <summary>
/// getYRaw(): Returns the raw data from the Y-axis analog I/O port of

/// </summary>
int AcceleroMMA7361::getYRaw()
{
        return analogRead(_yPin)+_offSets[1]+2;
}

/// <summary>
/// getZRaw(): Returns the raw data from the Z-axis analog I/O port of

/// </summary>
int AcceleroMMA7361::getZRaw()
{
        return analogRead(_zPin)+_offSets[2];
}

/// <summary>
/// getXVolt(): Returns the voltage in mV from the X-axis analog I/O

/// </summary>
int AcceleroMMA7361::getXVolt()
{
        return _mapMMA7361V(getXRaw());
}

/// <summary>
/// getYVolt(): Returns the voltage in mV from the Y-axis analog I/O

/// </summary>
int AcceleroMMA7361::getYVolt()
{
        return _mapMMA7361V(getYRaw());
}

/// <summary>
/// getZVolt(): Returns the voltage in mV from the Z-axis analog I/O

/// </summary>
int AcceleroMMA7361::getZVolt()
{
        return _mapMMA7361V(getZRaw());
}

/// <summary>
/// getXAccel(): Returns the acceleration of the X-axis as a int (1 G = 100.00)
/// </summary>
int AcceleroMMA7361::getXAccel()
{
        int sum = 0;
        for (int i = 0;i<_average;i++)
        {
                sum = sum + _mapMMA7361G(getXRaw());
        }
        return sum/_average;
}

/// <summary>
/// getYAccel(): Returns the acceleration of the Y-axis as a int (1 G = 100.00)
/// </summary>
int AcceleroMMA7361::getYAccel()
{
        int sum = 0;
        for (int i = 0;i<_average;i++)
        {
                sum = sum + _mapMMA7361G(getYRaw());
        }
        return sum/_average;
}

/// <summary>
/// getZAccel(): Returns the acceleration of the Z-axis as a int (1 G = 100.00)
/// </summary>
int AcceleroMMA7361::getZAccel()
{
        int sum = 0;
        for (int i = 0;i<_average;i++)
        {
                sum = sum + _mapMMA7361G(getZRaw());
        }
        return sum/_average;
}

/// <summary>
/// getAccelXYZ(int *_XAxis, int *_YAxis, int *_ZAxis) returns all

/// </summary>
void AcceleroMMA7361::getAccelXYZ(int *_XAxis, int *_YAxis, int *_ZAxis)
{
        int sum[3];
        sum[0] = 0;
        sum[1] = 0;
        sum[2] = 0;
        for (int i = 0;i<_average;i++)
        {
                sum[0] = sum[0] + _mapMMA7361G(getXRaw());
                sum[1] = sum[1] + _mapMMA7361G(getYRaw());
                sum[2] = sum[2] + _mapMMA7361G(getZRaw());
        }
        *_XAxis = sum[0]/_average;
        *_YAxis = sum[1]/_average;
        *_ZAxis = sum[2]/_average;
}

/// <summary>
/// mapMMA7361V: calculates and returns the voltage value derived from

/// </summary>
int AcceleroMMA7361::_mapMMA7361V(int value)
{
        if (_refVoltage==3.3)
        {
                return map(value,0,1024,0,3300);
        }
        else
        {
                return map(value,0,1024,0,5000);
        }
}

/// <summary>
/// mapMMA7361G: calculates and returns the accelerometer value in


/// </summary>
int AcceleroMMA7361::_mapMMA7361G(int value)
{
        if(_sensi == false)
        {
                if (_refVoltage==3.3)
                {
                        return map(value,0,1024,-825,800);
                }
                else
                {
                        return map(value,0,1024,-800,1600);
                }
        }
        else
        {
                if (_refVoltage==3.3)
                {
                        return map(value,0,1024,-206,206);
                }
                else
                {
                        return map(value,0,1024,-260,419);
                }
        }
}

/// <summary>
/// calibrate(): Sets X and Y values via setOffsets to zero. The Z

/// WARNING WHEN CALIBRATED YOU HAVE TO MAKE SURE THE Z-AXIS IS

/// </summary>
void AcceleroMMA7361::calibrate()
{
        Serial.println(getOrientation());
        Serial.print("\nCalibrating MMA7361011");
        double var = 5000;
        double sumX = 0;
        double sumY = 0;
        double sumZ = 0;
        for (int i = 0;i<var;i++)
        {
                sumX = sumX + getXVolt();
                sumY = sumY + getYVolt();
                sumZ = sumZ + getZVolt();
                if (i%100 == 0)
                {
                        Serial.print(".");
                }
        }
        if (_sensi == false)
        {
                setOffSets(1672 - sumX / var,1671 - sumY / var, + 1876 - sumZ / var);
        }
        else
        {
                setOffSets(1650 - sumX / var,1650 - sumY / var, + 2450 - sumZ / var);
        }
        if (abs(getOrientation())!=3)
        {
                Serial.print("\nunable to calibrate");
                setOffSets(0,0,0);
        }
        else
        {
                Serial.print("\nDONE");
        }
}

/// <summary>
/// getOrientation returns which axis perpendicular with the earths

/// negative depending on which side of the axis is pointing downwards
/// </summary>
int AcceleroMMA7361::getOrientation()
{
        int gemiddelde = 10;
        int x = 0;
        int y = 0;
        int z = 0;
        int xAbs = 0;
        int yAbs = 0;
        int zAbs = 0;
        for(int i = 0; i<gemiddelde ; i++)      //We take in this case 10

        {
                x = x+getXAccel();
                y = y+getYAccel();
                z = z+getZAccel();
        }
        x= x/gemiddelde;
        y = y/gemiddelde;
        z = z/gemiddelde;
        xAbs = abs(100-abs(x));
        yAbs = abs(100-abs(y));
        zAbs = abs(100-abs(z));
        if (xAbs<yAbs&&xAbs<zAbs)
        {
                if (x>0)
                {
                        return 1;
                }
                return -1;
        }
        if (yAbs<xAbs&&yAbs<zAbs)
        {
                if (y>0)
                {
                        return 2;
                }
                return -2;
        }
        if (zAbs<xAbs&&zAbs<yAbs)
        {
                if (z>0)
                {
                        return 3;
                }
                return -3;
        }
        return 0;
}
/// <summary>
/// getTotalVector returns the magnitude of the total acceleration

/// </summary>
int AcceleroMMA7361::getTotalVector()
{
        return sqrt(square(_mapMMA7361G(getXRaw())) +
square(_mapMMA7361G(getYRaw())) + square(_mapMMA7361G(getZRaw())));
}


AcceleroMMA7361 accelero;

int x;
int y;
int z;
int i;
int counter = 0;
int current_coordinates[] = {0,0,0};
int scale_x[] = {-50,50}; // needs tuning
int scale_y[] = {-50,50}; // needs tuning
int scale_z[] = {-50,50}; // needs tuning
int previous_scale_x[] = {-0,0}; //tuning needed
int previous_scale_y[] = {-0,0}; //tuning needed
int previous_scale_z[] = {-0,0}; //tuning needed

void setup()
{
  Serial.begin(9600);
  accelero.begin(13, 12, 11, 10, A0, A1, A2); // (int sleepPin, int selfTestPin, int zeroGPin, int gSelectPin, int xPin, int yPin, int zPin);
                                              // WAŻNE: podłączyć 3V3 do AREF'u!!!!
  accelero.setARefVoltage(3.3); //sets the AREF voltage to 3.3V
  accelero.setSensitivity(HIGH); //sets the sensitivity to +/-6G
  accelero.calibrate();
  
}

void loop()
{
  //Reading the accelerometer coordinates values
  current_coordinates[0] = accelero.getXAccel();
  current_coordinates[1] = accelero.getYAccel();
  current_coordinates[2] = accelero.getZAccel();
  
  //Normalization
  for(i=0; i++ ; i < 3) {
  current_coordinates[i] = normalize(current_coordinates[i]);
  }
  
  //Adapting the scale for mapping
  
  scale_x[0] = min(current_coordinates[0],previous_scale_x[0]);
  scale_y[0] = min(current_coordinates[1],previous_scale_x[0]);
  scale_z[0] = min(current_coordinates[2],previous_scale_x[0]);
  scale_x[1] = max(current_coordinates[0],previous_scale_x[1]);
  scale_y[1] = max(current_coordinates[1],previous_scale_x[1]);
  scale_z[1] = max(current_coordinates[2],previous_scale_x[1]);
  
  //Mapowanie
  x = map(current_coordinates[0],scale_x[0],scale_x[1],0,127);
  y = map(current_coordinates[1],scale_y[0],scale_y[1],0,127);
  z = map(current_coordinates[2],scale_z[0],scale_z[1],0,127);
  
  //Zapisanie stanu
  //min
  previous_scale_x[0] = scale_x[0] ;
  previous_scale_y[0] = scale_y[0] ;
  previous_scale_z[0] = scale_z[0] ;
  //max
  previous_scale_x[1] = scale_x[1] ;
  previous_scale_y[1] = scale_y[1] ;
  previous_scale_z[1] = scale_z[1] ;
  
  if(counter == 10 ) { //set period of adaptation
    //min
    previous_scale_x[0] = previous_scale_x[0] +1 ;
    previous_scale_y[0] = previous_scale_y[0] +1 ;
    previous_scale_z[0] = previous_scale_z[0] +1 ;
    //max
    previous_scale_x[1] = previous_scale_x[1] -2 ;
    previous_scale_y[1] = previous_scale_y[1] -2 ;
    previous_scale_z[1] = previous_scale_z[1] -2 ;
    //min
    scale_x[0] = scale_x[0] +1 ;
    scale_y[0] = scale_y[0] +1 ;
    scale_z[0] = scale_z[0] +1 ;
    //max
    scale_x[1] = scale_x[1] -2 ;
    scale_y[1] = scale_y[1] -2 ;
    scale_z[1] = scale_z[1] -2 ;
   // Serial.println("Adaptation commited");
    counter = 0;
  }
 /* 
  Serial.println();
  Serial.print("X: ");
  Serial.print(scale_x[0]);
  Serial.print("->");
  Serial.print(scale_x[1]);
  Serial.print("/previous:");
  Serial.print(previous_scale_x[0]);
  Serial.print("->");
  Serial.print(previous_scale_x[1]);
  Serial.println();
  Serial.print("Y: ");
  Serial.print(scale_y[0]);
  Serial.print("->");
  Serial.print(scale_y[1]);
  Serial.print("/previous:");
  Serial.print(previous_scale_y[0]);
  Serial.print("->");
  Serial.print(previous_scale_y[1]);
  Serial.println();
  Serial.print("Z: ");
  Serial.print(scale_z[0]);
  Serial.print("->");
  Serial.print(scale_z[1]);
  Serial.print("/previous:");
  Serial.print(previous_scale_z[0]);
  Serial.print("->");
  Serial.print(previous_scale_z[1]);
  Serial.println();
  
  Serial.print("Current -> X: ");
  Serial.print(current_coordinates[0]);
  Serial.print(",Y: ");
  Serial.print(current_coordinates[1]);
  Serial.print(",Z: ");
  Serial.println(current_coordinates[2]);
  Serial.print("Our x,y,z ->");
  Serial.print(x);
  Serial.print(',');
  Serial.print(y);
  Serial.print(',');
  Serial.print(z);
  Serial.println();
  Serial.println("-------------");
  
  delay(1000);
  counter++;
  */
/*
  Serial.print("\nx: ");
  Serial.print(x);
  Serial.print(" \ty: ");
  Serial.print(y);
  Serial.print(" \tz: ");
  Serial.print(z);
  Serial.print("\tG*10^-2");
 delay(500); //make it readable  
*/
      Serial1.write(0xB0); // MIDI control change; channel 3
      Serial1.write(0x2A); // MIDI controller #1
      Serial1.write(x); // MIDI controller value of 127
      
     Serial1.write(0xB0); // MIDI control change; channel 3
     Serial1.write(0x2B); // MIDI controller #1
     Serial1.write(y); // MIDI controller value of 127
     
     Serial1.write(0xB0); // MIDI control change; channel 3
     Serial1.write(0x2C); // MIDI controller #1
     Serial1.write(z); // MIDI controller value of 127
delay(10);
}






int normalize(int newreading) {
  if (newreading > 180){
    return 180;
  } else {
    return newreading;
  }
  if (newreading < -180){
    return -180 ;
  } else {
    return newreading;
  }
}




