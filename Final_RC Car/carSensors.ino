int LeftF = 10; 
int LeftB = 9; 
int RightF = 5; 
int RightB = 6;
int vel = 255; // Vel(0-255)
int state = 'g'; // init state

//flame
int flameInput = 13;
int flamestate;

//ultra
int pin_echo=3;
int pin_trig=4;

//mic
int mic = 2;
int micval = 0;

//line tracking
int CentreIR=8;
int LeftIR=7;
int RightIR=12;

//light
int RightSensor=A2;
int LeftSensor=A1;
int cent=A3;
int SensorRight;
int SensorLeft;
int Scent;


void setup() 
{ 
  Serial.begin(9600); // Bluetooth
  //motion
  pinMode(RightF, OUTPUT);
  pinMode(RightB, OUTPUT);
  pinMode(LeftF, OUTPUT);
  pinMode(LeftB, OUTPUT);
  
  //flame
  pinMode(flameInput, INPUT);
  
  //ultra
  pinMode(pin_trig, OUTPUT);
  pinMode(pin_echo, INPUT);
  
  //mic
  pinMode(mic, INPUT);
  
  //line
  pinMode(CentreIR,INPUT);
  pinMode(LeftIR,INPUT);
  pinMode(RightIR,INPUT);

  //light
  pinMode(LeftSensor, INPUT);
  pinMode(RightSensor, INPUT);
  pinMode(cent, INPUT);

} 


float UltraSonic()
{
  digitalWrite(pin_trig,LOW);
  delayMicroseconds(2);
  digitalWrite(pin_trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(pin_trig,LOW);
  delayMicroseconds(2);
 
 
  int duration=pulseIn(pin_echo,HIGH);
  int distance =duration*(0.343/2);
  float x =constrain(distance,0,5000);
  Serial.println("ultra");
  Serial.println(x);

  return(x);
}



void Forward()

{
analogWrite(LeftB, 0); 
analogWrite(RightB, 0); 
analogWrite(LeftF, vel); 
analogWrite(RightF, vel); 
}



void Backward()

{
analogWrite(LeftB, vel); 
analogWrite(RightB, vel); 
analogWrite(LeftF, 0); 
analogWrite(RightF, 0); 
}



void Right()

{
analogWrite(LeftB, 0); 
analogWrite(RightB, vel); 
analogWrite(LeftF, vel); 
analogWrite(RightF, 0); 
}




void Left()

{
analogWrite(LeftB, vel); 
analogWrite(RightB, 0); 
analogWrite(LeftF, 0); 
analogWrite(RightF, vel); 
}


void RightForward()

{
analogWrite(LeftB, 0); 
analogWrite(RightB, 0); 
analogWrite(LeftF, vel); 
analogWrite(RightF, 0); 
}



void RightBackward()

{
   //light
SensorLeft = 1023 - analogRead(LeftSensor);
//delay(1);
SensorRight = 1023 - analogRead(RightSensor);
//delay(1);
Scent = 1023 - analogRead(cent);
//SensorDifference = abs(SensorLeft - SensorRight);  
Serial.print("Left Sensor = "); 
Serial.print(SensorLeft); 
Serial.print("\t");
Serial.print("Right Sensor = ");
Serial.print(SensorRight); 
Serial.print("\t");
Serial.print("Scent = ");
Serial.print(cent); 
Serial.print("\t");
if (SensorLeft > SensorRight && Scent > SensorRight && SensorRight < 10) 
{
 RightForward();
 Serial.println("Right"); 
 delay(50);
}
if (SensorRight > SensorLeft && Scent >SensorLeft && SensorLeft<10) 
{
 LeftForward();
 Serial.println("Left"); 
 delay(50);
}
if ( SensorLeft>Scent && SensorRight>Scent  && Scent<10 )
{
 Forward();
 Serial.println("Forward"); 
 delay(50);
}

// ==>? momkn ntr n4el el if bta3t el stop

if ( SensorLeft>10 && SensorRight>10  && Scent>10 )
{
 Stop();
 Serial.println("stop"); 
 //delay(50);  
}

}



void LeftForward()

{
analogWrite(LeftB, 0); 
analogWrite(RightB, 0); 
analogWrite(LeftF, 0); 
analogWrite(RightF, vel);   
}



  

void LeftBackward()

{
analogWrite(LeftB, 0); 
analogWrite(RightB, vel); 
analogWrite(LeftF, 0); 
analogWrite(RightF, 0); 
}

void Stop()

{

analogWrite(LeftB, 0); 
analogWrite(RightB, 0); 
analogWrite(LeftF, 0); 
analogWrite(RightF, 0); 

}



void loop() 
{
 

  //flame
flamestate = digitalRead(flameInput);
Serial.println("flame"); 
Serial.println(flamestate); 
if(flamestate == LOW)
{
Backward();
delay(2000);
Stop();
}


 

  //mic
micval = digitalRead(mic);
Serial.println("mic");
Serial.println(micval);
if (micval == 1)
{
 Forward();
 delay(3000);
 Stop();
}

 
  //line
if(digitalRead(CentreIR)==HIGH && digitalRead(RightIR)==LOW && digitalRead(LeftIR)==LOW )
{
analogWrite(LeftB, 0); 
analogWrite(RightB, 0); 
analogWrite(LeftF, 100); 
analogWrite(RightF, 100); 

}
if(digitalRead(RightIR)==LOW && digitalRead(CentreIR)==LOW && digitalRead(LeftIR)==HIGH )
{
analogWrite(LeftB, 0); 
analogWrite(RightB, 0); 
analogWrite(LeftF, 0); 
analogWrite(RightF, 150); 
delay(200);

}
if(digitalRead(RightIR)==LOW && digitalRead(CentreIR)==HIGH && digitalRead(LeftIR)==HIGH )
{
analogWrite(LeftB, 0); 
analogWrite(RightB, 0); 
analogWrite(LeftF, 0); 
analogWrite(RightF, 150); 
delay(500);

}
if(digitalRead(RightIR)==HIGH && digitalRead(CentreIR)==LOW && digitalRead(LeftIR)==LOW )
{
analogWrite(LeftB, 0); 
analogWrite(RightB, 0); 
analogWrite(LeftF, 150); 
analogWrite(RightF, 0); 
delay(500);
}
if(digitalRead(RightIR)==HIGH && digitalRead(CentreIR)==HIGH && digitalRead(LeftIR)==LOW )
{
analogWrite(LeftB, 0); 
analogWrite(RightB, 0); 
analogWrite(LeftF, 150); 
analogWrite(RightF, 0); 
delay(500);
}
if(digitalRead(RightIR)==HIGH && digitalRead(CentreIR)==HIGH && digitalRead(LeftIR)==HIGH )
{
 Stop();
}
if(digitalRead(RightIR)==LOW && digitalRead(CentreIR)==LOW && digitalRead(LeftIR)==LOW )
{
 Stop();
}

 //app

if(Serial.available()>0)
{ // Bluetooth Data
state = Serial.read();
}

 Serial.println(state);
 
if(state=='F') // Forward
Forward();

if(state=='B') // Backward
Backward();

if(state=='R') // Right
Right();

if(state=='L') // Left
Left();

if(state=='I') // RF
RightForward();

if(state=='G') // LF
LeftForward();

//acc 
if(state=='H') // LB
LeftBackward();

//ultra
if(state=='J') // RB
RightBackward();

if(state=='S') // Stop
Stop();


//ultra
if(state==86)
{
 do
{
   Forward();
   if(UltraSonic()>200 && UltraSonic()<800)
   {
    analogWrite(LeftB, 0); 
    analogWrite(RightB, 0); 
    analogWrite(LeftF, 100); 
    analogWrite(RightF, 100);
    Serial.println("speed is 100");
    
    }

   
}
while(UltraSonic()>200); 
Stop();
}


//if (estado =='f'){ //  ON  

//}
//if (estado=ppppppppppppp='g'){ // OFF 
//}

}


//note
//small v=118 sound off
//86=sound on


