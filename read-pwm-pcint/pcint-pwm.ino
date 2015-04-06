volatile uint32_t chan[8];


//this works only with attachInterrupts()...
//it is not right
// Board	int.0	int.1	int.2	int.3	int.4	int.5
//Mega2560	 2	  3	  21	  20	  19	  18


//CHANNEL 1-INT2-PIN19
//CHANNEL 2-PCINT6-PIN12
//CHANNEL-3 - PCINT16-ANALOG8
//CHANNEL 4-PCINT5-PIN11
//CHANNEL-5 - PCINT17-ANALOG9
//CHANNEL 6-PCINT4-PIN10
//CHANNEL-7 - PCINT18-ANALOG10
//CHANNEL 8-PCINT0-PIN53


void setup(){
  Serial.begin(115200);
  Serial.println("\nHello world");

  ADCSRA=0;

  PCICR=(1<<PCIE2)|(1<<PCIE0);
  PCMSK2=1<<PCINT16;

  //attachInterrupt(4,  channel1, CHANGE);
  EICRA=0b00010000;
  //EICRB=0b00000001;
  EIMSK=1<<INT2;
  pwmInitialize();
}

void pwmInitialize()
{
  TCCR5A = 0x00;	   
  TCCR5B = (1<<CS51);  
  TIMSK5 = 0x00;
}


ISR(INT2_vect){
  static uint32_t start;

  if(digitalRead(19)){
    
    TCNT5=0;

  }
  else{
    PCMSK0=1<<PCINT6;
    chan[0]=TCNT5/2;
  }
}

ISR(PCINT2_vect){
  
  static uint32_t start2;
  if(PCMSK2&(1<<PCINT16)){
    if(PINK&(1<<PK0))
    {
      
      TCNT5=0;
    }
    else{
      PCMSK2=1<<PCINT17;
      chan[2]=TCNT5/2;
    }
  }
  else if(PCMSK2&(1<<PCINT17)){
    if(PINK&(1<<PK1))
    {
     
      TCNT5=0;
    }
    else{
      PCMSK2=1<<PCINT18;
      chan[4]=TCNT5/2;
    }
  }

  else if(PCMSK2&(1<<PCINT18)){
    if(PINK&(1<<PK2))
    {
      TCNT5=0;
    }
    else{
      PCMSK2=1<<PCINT16;
      chan[6]=TCNT5/2;
    }
  }
}

ISR(PCINT0_vect){
  
  static uint32_t start1;
  
  if(PCMSK0&(1<<PCINT6)){
    if(digitalRead(12))
    {
      
      TCNT5=0;
    }
    else{
      PCMSK0=1<<PCINT5;
      chan[1]=TCNT5/2;
    }
  }

  else if(PCMSK0&(1<<PCINT5)){
    if(digitalRead(11))
    {
      TCNT5=0;
    }
    else{
      PCMSK0=1<<PCINT4;
      chan[3]=TCNT5/2;
    }
  }

  else if(PCMSK0&(1<<PCINT4)){
    if(digitalRead(10))
    {
     
      TCNT5=0;
    }
    else{
      PCMSK0=1<<PCINT0;
      chan[5]=TCNT5/2;
    }
  }

  else if(PCMSK0&(1<<PCINT0)){
    if(digitalRead(53))
    {
      TCNT5=0;
    }
    else{
      PCMSK0=1<<PCINT6;
      chan[7]=TCNT5/2;
    }
  }



}
void loop(){
  for(int i=0;i<8;i++)
  {
    Serial.print(chan[i]);
    Serial.print('\t');

  }
  Serial.println();
  //delay(100);
}
