#include<VirtualWire.h>
  String message="";      
  char* msg="";           
  int buttonState = 0;    
  unsigned long pressStartTime = 0;   
  unsigned long pressDuration = 0;    
  unsigned long idleStartTime = 0;    
  unsigned long idleDuration = 0;     
void setup() 
{
  Serial.begin(9600); 
  pinMode(5,INPUT);   
  pinMode(8,OUTPUT);  
  vw_set_tx_pin(2);   
  vw_set_ptt_inverted(true); 
  vw_setup(2000);      
}
 void Transmite(char* msg)
 {
    vw_send((uint8_t *)msg, strlen(msg));   
    vw_wait_tx();           
    message="";   
    digitalWrite(8,true); 
    delay(1000);                     
    digitalWrite(8,false);        
 }
void loop() {
   buttonState = digitalRead(5);  
   if(buttonState==1)
   {
     pressStartTime = millis();    
   }
  while (buttonState == HIGH) 
  {    
    idleDuration=0;          
    buttonState = digitalRead(5);   
    pressDuration = millis() - pressStartTime; 
  } 
  if(pressDuration>=5000)  {
    message="COM. NU FUNCT.";   
  }
  else if(pressDuration>=2500)  {
    message="C";     
  }
  else if(pressDuration>=1500)  {
    message+="S";   
  }
   else if (pressDuration >= 500)     {
     message+="-";    
    } 
    else if(pressDuration>=100)    {
     message+=".";   
    }
    Serial.println(message);      
    pressDuration=0;           
    if (buttonState == LOW) 
  {
    idleStartTime = millis();    
  } 
    while(buttonState==0)  {
    idleDuration=millis()-idleStartTime;      
    buttonState = digitalRead(5);           
     if(idleDuration>3000)     {    
      msg=message.c_str();   
      Serial.println(msg);   
      Transmite(msg);         
      idleDuration=0;        
      break;
    }
  }   
} 
