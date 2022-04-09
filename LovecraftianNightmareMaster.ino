//Sent messages need to be encrypted. Give them A hierarchy and add their placement times 10000 to the actual values. In the Slave code make it run through a series of else if blocks that go lower and lower. 
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

#define rotateX A0
#define rotateY A1
#define rotateZ A2
#define ArmMaster A3
#define HandX A4
#define HandY A5

#define ThumbMaster 2
#define IndexMaster 3
#define MiddleMaster 4
#define RingMaster 5
#define PinkyMaster 6

#define Start 8

long XMessage, YMessage, ZMessage, ArmMessage, HandXMessage, HandYMessage, ThumbMessage, IndexMessage, MiddleMessage, RingMessage,PinkyMessage;
int a, b;
bool on;

void setup() 
{
  on=false;
  a=1;

  pinMode(Start, INPUT_PULLUP);

  pinMode(ThumbMaster, INPUT_PULLUP);
  pinMode(IndexMaster, INPUT_PULLUP);
  pinMode(MiddleMaster, INPUT_PULLUP);
  pinMode(RingMaster, INPUT_PULLUP);
  pinMode(PinkyMaster, INPUT_PULLUP);

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  delay(100);
}


void loop() 
{
  StartCheck();
  if(on==true)
  {
    CheckArm();
    CheckFinger();
    SendMessage();
  }
}

void StartCheck()
{
  if(digitalRead(Start)==0&&a==1)
  {
    if(on==false)
    {
      on=true;
    }
    if(on==true)
    {
      on=false;
    }
    a=0;
    b=1;
  }
  if(digitalRead(Start)==1)
  {
    a=1;
  }
}

void CheckArm()
{
  sensors_event_t a, g, temp;
  
  XMessage = analogRead(rotateX);
  YMessage = g.gyro.y+10000;
  ZMessage = analogRead(rotateZ)+20000;
  ArmMessage = analogRead(ArmMaster)+30000;
  HandXMessage = analogRead(HandX)+40000;
  HandYMessage = analogRead(HandY)+50000;
}

void CheckFinger()
{
  ThumbMessage = digitalRead(ThumbMaster)+60000;
  IndexMessage = digitalRead(IndexMaster)+70000;
  MiddleMessage = digitalRead(MiddleMaster)+80000;
  RingMessage = digitalRead(RingMaster)+90000;
  PinkyMessage = digitalRead(PinkyMessage)+100000;
}

void SendMessage()
{
  if(b==1)
  {
    //Send XMessage
  }
  if(b==2)
  {
    //Send YMessage
  }
  if(b==3)
  {
    //Send ZMessage
  }
  if(b==4)
  {
    //Send ArmMessage
  }
  if(b==5)
  {
    //Send HandXMessage
  }
  if(b==6)
  {
    //Send HandYMessage
  }
  if(b==7)
  {
    //Send ThumbMessage
  }
  if(b==8)
  {
    //Send IndexMessage
  }
  if(b==9)
  {
    //Send MiddleMessage
  }
  if(b==10)
  {
    //Send RingMessage
  }
  if(b==11)
  {
    //Send PinkyMessage
  }
  
  b++;
  if(b==12)
  {
    b=0;
  }
}
