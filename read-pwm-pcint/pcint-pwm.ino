volatile uint32_t chan[8];

void setup(){
  Serial.begin(115200);
  Serial.println("\nHello world");
  
  PCICR=(1<<PCIE2)|(1<<PCIE0);
  
  attachInterrupt(2,  channel1, CHANGE);
  //CHANNEL 1-INT2-PIN19
  //CHANNEL 2-PCINT6-PIN12
  //CHANNEL-3 - PCINT16-ANALOG8
  //CHANNEL 4-PCINT5-PIN11
  //CHANNEL-5 - PCINT17-ANALOG9
  //CHANNEL 6-PCINT4-PIN10
  //CHANNEL-7 - PCINT18-ANALOG10
  //CHANNEL 8-PCINT0-PIN53
}

void channel1(){
 static uint32_t start;
 if(digitalRead(19)){
   start=micros();
 }
 else{
   PCMSK0=1<<PCINT6;
   chan[0]=(uint32_t)(micros()-start);
   
 }
}

ISR(PCINT2_vect){
static uint32_t start2;
if(PCMSK2&(1<<PCINT16)){
    if(PINK&(1<<PK0))
    {
      start2=micros();
    }
    else{
      PCMSK2=1<<PCINT17;
   chan[2]=(uint32_t)(micros()-start2);
    }
  }
  else if(PCMSK2&(1<<PCINT17)){
    if(PINK&(1<<PK1))
    {
      start2=micros();
    }
    else{
      PCMSK2=1<<PCINT18;
   chan[4]=(uint32_t)(micros()-start2);
    }
  }
  
  else if(PCMSK2&(1<<PCINT18)){
    if(PINK&(1<<PK2))
    {
      start2=micros();
    }
    else{
      PCMSK2=1<<PCINT16;
   chan[6]=(uint32_t)(micros()-start2);
    }
  }
}

ISR(PCINT0_vect){
  static uint32_t start1;
  if(PCMSK0&(1<<PCINT6)){
    if(digitalRead(12))
    {
      start1=micros();
    }
    else{
      PCMSK0=1<<PCINT5;
   chan[1]=(uint32_t)(micros()-start1);
    }
  }
  
  else if(PCMSK0&(1<<PCINT5)){
  if(digitalRead(11))
    {
      start1=micros();
    }
    else{
      PCMSK0=1<<PCINT4;
   chan[3]=(uint32_t)(micros()-start1);
    }
  }
  
  else if(PCMSK0&(1<<PCINT4)){
  if(digitalRead(10))
    {
      start1=micros();
    }
    else{
      PCMSK0=1<<PCINT0;
   chan[5]=(uint32_t)(micros()-start1);
    }
  }
  
  else if(PCMSK0&(1<<PCINT0)){
  if(digitalRead(53))
    {
      start1=micros();
    }
    else{
      PCMSK0=1<<PCINT6;
   chan[7]=(uint32_t)(micros()-start1);
    }
  }
  
  
  
}
void loop(){
  
}
