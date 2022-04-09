#include <Servo.h>
Servo zRotate, yRotate, xRotate, Arm, xHand, yHand, Thumb, Index, Middle, Ring, Pinky;

#define Zrotate 2
#define Yrotate 3
#define Xrotate 4
#define arm 5
#define Xhand 6
#define Yhand 7
#define thumb 8
#define index 9
#define middle 10
#define ring 11
#define pinky 12

#define Start 53
#define PhoneStart 52

#define Test 13

int zAngle=0;
int yAngle=0;
int xAngle=0;
int ArmAngle=0;
int xHandAngle=0;
int yHandAngle=0;
int ThumbAngle=0;
int IndexAngle=0;
int MiddleAngle=0;
int RingAngle=0;
int PinkyAngle=0;

int XMessage, YMessage, ZMessage, ArmMessage, HandXMessage, HandYMessage, ThumbMessage, IndexMessage, MiddleMessage, RingMessage,PinkyMessage;
long SentMessage;
int a, b, c;
bool on;
bool onPhone;

int CharA, CharB, CharC, CharD, CharE, CharF;
int LastC;

char Value;
char LastValue;

bool ReceivedStatus;

void setup() 
{
  on=false;
  onPhone=false;
  
  a=1;
  b=1;
  c=1;
  
  pinMode(Start, INPUT_PULLUP);
  pinMode(PhoneStart, INPUT_PULLUP);

  pinMode(Test, OUTPUT);

  CharA=0;
  CharB=0;
  CharC=0;
  CharD=0;
  CharE=0;
  CharF=0;

  ReceivedStatus=false;

  Serial2.begin(9600);
}

void loop()
{
  StartCheck();
  if(on==true)
  {
   ReceiveMessage();
   Decode();
  }
  if(onPhone==true)
  {
    PhoneReceive();
    PhoneDecode();
  }
  if(onPhone==true||on==true)
  {
    Move();
  }
}

void StartCheck()
{
  if(digitalRead(Start)==0&&a==1)
  {
    if(on==false)
    {
      onPhone=false;
      on=true;
    }
    if(on==true)
    {
      on=false;
    }
    a=0;
  }

  if(digitalRead(PhoneStart)==0&&a==1)
  {
    if(onPhone==false)
    {
      on=false;
      onPhone=true;
    }
    if(onPhone==true)
    {
      onPhone=false;
    }
    a=0;
  }

  if(digitalRead(Start)==1 && digitalRead(PhoneStart)==1)
  {
    a=1;
  }
}

void ReceiveMessage()
{
  //Code to receive the message and make sentmessage equal to it
}

void Decode()
{
   if(SentMessage>=100000)
   {
    PinkyMessage = SentMessage-100000;
   }
   else if(SentMessage>=90000&&SentMessage<100000)
   {
    RingMessage = SentMessage-90000;
   }
   else if(SentMessage>=80000&&SentMessage<90000)
   {
    MiddleMessage = SentMessage-80000;
   }
   else if(SentMessage>=70000&&SentMessage<80000)
   {
    IndexMessage=SentMessage-70000;
   }
   else if(SentMessage>=60000&&SentMessage<70000)
   {
    ThumbMessage=SentMessage-60000;
   }
   else if(SentMessage>=50000&&SentMessage<60000)
   {
    HandYMessage=SentMessage-50000;
   }
   else if(SentMessage>=40000&&SentMessage<50000)
   {
    HandXMessage=SentMessage-40000;
   }
   else if(SentMessage>=30000&&SentMessage<40000)
   {
    ArmMessage=SentMessage-30000;
   }
   else if(SentMessage>=20000&&SentMessage<30000)
   {
    ZMessage=SentMessage-20000;
   }
   else if(SentMessage>=10000&&SentMessage<20000)
   {
    YMessage=SentMessage-10000;
   }
   else if(SentMessage<10000)
   {
    XMessage=SentMessage;
   }
}

void PhoneReceive()
{
  if(Serial2.available() > 0)
  {
    Value = Serial2.read();
  }

  if(Value==-2)
  {
    digitalWrite(13, HIGH);
  }
  
  if(Value==-3)
  {
    digitalWrite(13, LOW);
  }

  if(Value==-1)
  {
    
    LastC=CharC;
    while(LastC=CharC)
    {
      Value = Serial2.read();
      if(b==1)
      {
        LastValue = Value;
        b=0;
      }
      if(LastValue!=Value)
      {
        if(c==1)
        {
          CharA=Value;
          c++;
        }
        if(c==2)
        {
          CharB=Value;
          c++;
        }
        if(c==3)
        {
          CharC=Value;
          if(CharC==LastC)
          {
            c=1;
            LastC=100;
          }
          c=1;
        }
        b=1;
      }
    }
    ReceivedStatus=true;
  } 
}

void PhoneDecode()
{
  if(ReceivedStatus==true)
  {
    SentMessage= CharA*100+CharB*10+CharC;

    if(SentMessage<10)
    {
      zAngle= SentMessage*45-45;
    }
    if(SentMessage>=10&&SentMessage<20)
    {
      yAngle= (SentMessage-10)*45-45;
    }
    if(SentMessage>=20&&SentMessage<30)
    {
      xAngle= (SentMessage-20)*45-45;
    }
    if(SentMessage>=30&&SentMessage<40)
    {
      ArmAngle= (SentMessage-30)*45-45;
    }
    if(SentMessage>=40&&SentMessage<50)
    {
      xHandAngle= (SentMessage-40)*45-45;
    }
    if(SentMessage>=50&&SentMessage<60)
    {
      yHandAngle= (SentMessage-50)*45-45;
    }
    if(SentMessage>=60&&SentMessage<70)
    {
      //Code for finger change
    }
    if(SentMessage>=70&&SentMessage<80)
    {
      //Code for finger change
    }
    if(SentMessage>=80&&SentMessage<90)
    {
      //Code for finger change
    }
    if(SentMessage>=90&&SentMessage<100)
    {
      //Code for finger change
    }
    if(SentMessage>=100)
    {
      //Code for finger change
    }
  }
}

void Move()
{
  zRotate.write(zAngle);
  yRotate.write(yAngle);
  xRotate.write(xAngle);
  Arm.write(ArmAngle);
  xHand.write(xHandAngle);
  yHand.write(yHandAngle);
  Thumb.write(ThumbAngle);
  Index.write(IndexAngle);
  Middle.write(MiddleAngle);
  Ring.write(RingAngle);
  Pinky.write(PinkyAngle);
}
