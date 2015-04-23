volatile uint32_t chan[8];

//this works only with attachInterrupts()...
//it is not right
// Board	int.0	int.1	int.2	int.3	int.4	int.5
//Mega2560	 2	  3	  21	  20	  19	  18


//OC4A-DIGITAL PIN 6
//OC4B-DIGITAL PIN 7
//OC4C-DIGITAL PIN 8

//CHANNEL 1-PIN10
//CHANNEL 2-PIN11
//CHANNEL-3 - PK0 - ANALOG8
//CHANNEL 4-PK1 - ANALOG9
//CHANNEL-5 - PIN12
//CHANNEL 6-PK2 - ANALOG10
//CHANNEL-7 -PIN13
//CHANNEL 8-PK3-ANALOG11


void setup(){
  Serial.begin(115200);
  Serial.println("\nHello world");

  rcIntialize();
}

void rcIntialize(){

  ADCSRA=0;
  ADCSRB=0;

  DIDR2=0;
  DIDR0=0;

  DDRB&=~((1<<PB4)|(1<<PB5)|(1<<PB6)|(1<<PB7));
  DDRK&=~((1<<PK0)|(1<<PK1)|(1<<PK2)|(1<<PK3));

  PCICR=(1<<PCIE0)|(1<<PCIE2);
  PCMSK0=1<<PCINT4;
  PCMSK2=1<<PCINT16;
}


ISR(PCINT0_vect){

  static uint32_t start0[4];

  if(PCMSK0&(1<<PCINT4)){
    if(PINB&(1<<PB4))
    {
      start0[0]=micros();
    }
    else{
      PCMSK0=1<<PCINT5;
      chan[0]=(uint32_t)(micros()-start0[0]);
    }
  }
  else if(PCMSK0&(1<<PCINT5)){
    if(PINB&(1<<PB5))
    {
      start0[1]=micros();
    }
    else{
      PCMSK0=1<<PCINT6;
      chan[2]=(uint32_t)(micros()-start0[1]);
    }
  }
  else if(PCMSK0&(1<<PCINT6)){
    if(PINB&(1<<PB6))
    {
      start0[2]=micros();
    }
    else{
      PCMSK0=1<<PCINT7;
      chan[4]=(uint32_t)(micros()-start0[2]);
    }
  }
  else if(PCMSK0&(1<<PCINT7)){
    if(PINB&(1<<PB7))
    {
      start0[3]=micros();
    }
    else{
      PCMSK0=1<<PCINT4;
      chan[6]=(uint32_t)(micros()-start0[3]);
    }
  }
}


ISR(PCINT2_vect){

  static uint32_t start2[4];
  if(PCMSK2&(1<<PCINT16)){
    if(PINK&(1<<PK0))
    {
      start2[0]=micros();
    }
    else{
      PCMSK2=1<<PCINT17;
      chan[1]=(uint32_t)(micros()-start2[0]);

    }
  }
  else if(PCMSK2&(1<<PCINT17)){
    if(PINK&(1<<PK1))
    {
      start2[1]=micros();
    }
    else{
      PCMSK2=1<<PCINT18;
      chan[3]=(uint32_t)(micros()-start2[1]);
    }
  }
  else if(PCMSK2&(1<<PCINT18)){
    if(PINK&(1<<PK2))
    {
      start2[2]=micros();
    }
    else{
      PCMSK2=1<<PCINT19;
      chan[5]=(uint32_t)(micros()-start2[2]);
    }
  }
  else if(PCMSK2&(1<<PCINT19)){
    if(PINK&(1<<PK3))
    {
      start2[3]=micros();   
    }
    else{
      PCMSK2=1<<PCINT16;
      chan[7]=(uint32_t)(micros()-start2[3]);
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

}


