/*
I have used arduino mega 2560 to read ppm stream from ArduPPM.
Pin 48 of Arduino Mega is Input Cature Pin which copies value of timer5(16 Bit timer on atmega2560) at the trigerring event.
This Code could interfere the pwm operation of some pins and limit the number f servos that could be arranged to the Arduino Mega 2560

This method of reading ppm stream reduces the total number of times isr executed to read the whole frame of rc receiver.
It is used by me in my Quadcopter Project!
*/

int ppm[10]; 
volatile boolean ppm_syn = false;


void setup()
{
  Serial.begin(115200);
  Serial.println("ready");
  
  pinMode(48, INPUT);
  
  for(int i=0;i<10;i++)
  {
    ppm[i]=0;
  }
  
  TCCR5A = 0x00;	   
  TCCR5B = 0x00;
  TCCR5B = (1<<CS51) | (1<<ICES5);  
  TIMSK5 = 0x00;
  TIMSK5 = _BV(ICIE5)|_BV(ICNC5);   
}

ISR(TIMER5_CAPT_vect)
{
  static unsigned long counter;
  static byte channel;

  counter = ICR5;
  TCNT5 = 0;

  if(counter > 3820 )
  {  
    channel = 0;
    ppm_syn=true;
  }
  else if(ppm_syn)
  { 
    ppm[channel] = counter/2;
    channel++;
  }
  
}

void loop()
{

   for(int i=0;(ppm[i]!=0);i++)
  {
    Serial.print(ppm[i]);
    Serial.print("  ");
  }
  
  Serial.println("");
  delay(100);  
}
