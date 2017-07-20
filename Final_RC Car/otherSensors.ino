//temp
int IN1=3;
int IN2=6;
int buzzer=8;
int temp=A0;

//ldr
int LDRPin = 1;
int Vo2;

//tilt
int tilt=12;
int led=13;
int buzzer2=4;

void setup() {
  //temp
  pinMode(IN1,OUTPUT);
pinMode(IN2,OUTPUT);
pinMode(buzzer,OUTPUT);
//ldr
pinMode(2, OUTPUT);
Serial.begin(9600);
//tilt
pinMode(tilt,INPUT);
pinMode(led,OUTPUT);
pinMode(buzzer2,OUTPUT);


}
//ldr
boolean LDR(int outputPin) //LDR Function --> Light 
{
  
  Vo2 = analogRead(LDRPin);
  Serial.print("LDR Resistance: "); 
  Serial.print(Vo2);
  Serial.println(" "); 

  delay(500);
  
   if( Vo2 > 400)
   return 1;
   
   else
   return 0;
   

}


void loop() {
  //temp
float tempval=analogRead(A0);
Serial.println(tempval);
if(tempval>800)
{
  analogWrite(IN1,255);
  analogWrite(IN2,0);
}
else if(tempval>780)
{
  analogWrite(IN1,125);
  analogWrite(IN2,0);
}
else{
  analogWrite(IN1,0);
  analogWrite(IN2,0);
}
if(tempval>=780){
  digitalWrite(buzzer,HIGH);
  delay(500);
  digitalWrite(buzzer,LOW);
  delay(500);

}
else{
  digitalWrite(buzzer,LOW);
}  


  
  // ldr
  digitalWrite(2,LDR(2));
//tilt
int reading= digitalRead(tilt);
Serial.println(reading);
if(reading==1)
{
  digitalWrite(led,HIGH);
  digitalWrite(buzzer2,HIGH);
  
}
else
{
  digitalWrite(led,LOW);
  digitalWrite(buzzer2,LOW);
}

}
