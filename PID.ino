
#define input_pin 0               // Kullanacağımız pinleri belirliyoruz.
#define role_pin 6
#include <PID_v1.h>
int Setpoint, Input, Output;      // Değişkenleri tanımlıyoruz.

double Kp=1, Ki=5, Kd=1;          // Ayar parametrelerimizi tanımlayıp belirliyoruz.


PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

int WindowSize = 1000;           // Pulse için belirlediğimiz maksimum süre.
unsigned long windowStartTime;

void setup()
{
  Serial.begin(9600);
  windowStartTime = millis();               // Değişkenlerimizi atıyoruz, analog iletişimi başlatıyoruz. https://steemit.com/utopian-io/@drencolha/arduino-pid-library-kurulumu-ve-kullanimi-turkish-tutorial
  Setpoint = 90;                            // Suyun gelmesini istediğimiz sıcaklık değeri.

                           
  myPID.SetOutputLimits(0, WindowSize);     // PWM işleminin gerçekleşme süre aralığını belirliyoruz.

  myPID.SetMode(AUTOMATIC);                 // PID kontrolörümüzü açıyoruz.
}

void loop()
{
  Input = analogRead(input_pin);            // PID kontrolörümüze göre rölenin açık duruma geçmesi
  myPID.Compute();                          // veya kapalı duruma geçmesini sağlayan kod.


  if (millis() - windowStartTime > WindowSize)
  { 
    windowStartTime += WindowSize;
  }
  if (Output < millis() - windowStartTime) digitalWrite(role_pin, HIGH);
  else digitalWrite(role_pin, LOW);

}

