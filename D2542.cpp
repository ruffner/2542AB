#include <Arduino.h>
#include "D2542.h"

/*
     A
    ---
 F | G | B
    ---
 E |   | C
    ---
     D
*/

D2542*  D2542::isr_handler;

ISR(TIMER1_COMPA_vect)
{
  D2542::isr();
}

//--
// public functions
//--

D2542::D2542()
{

}

D2542::D2542(int16_t Ap, int16_t Bp, int16_t Cp, int16_t Dp,
             int16_t Ep, int16_t Fp, int16_t Gp, int16_t pP,
             int16_t g1, int16_t g2, int16_t g3, int16_t g4)
{
  int i;
  
  segments[0] = Ap;
  segments[1] = Bp;
  segments[2] = Cp;
  segments[3] = Dp;
  segments[4] = Ep;
  segments[5] = Fp;
  segments[6] = Gp;
  grounds[0] = g1;
  grounds[1] = g2;
  grounds[2] = g3;
  grounds[3] = g4;
  pPin = pP;
  
  for(i = 0; i < 7; i++)
    pinMode(segments[i], OUTPUT);
  for(i = 0; i < 4; i++)
    pinMode(grounds[i], OUTPUT);
  pinMode(pPin, OUTPUT);
  
  for(i = 0; i < 4; i++)
    digitalWrite(grounds[i], HIGH);
  
  dp = true;
  curNum = 0;
  isDispOn = false;
  max = 1999;
  min = 0;
  isr_handler = this;
  setupTimer1();
}

void D2542::setNumber(int num)
{
  if(num < min) num = min;
  if(num > max) num = max;
  curNum = num;
}

int D2542::getNumber()
{
  return curNum;
}

void D2542::on()
{
  // enable the interrupt that cycles the updates
  // on the display
  TIMSK1 |= (1 << OCIE1A);
  isDispOn = true;
}


void D2542::off()
{
  // stop interrupting us
  TIMSK1 &= ~(1 << OCIE1A);
  isDispOn = false;
}

bool D2542::isOn()
{
  return isDispOn;
}

void D2542::setMax(int nMax)
{
  max = nMax;
  if(max > 1999)
    max = 1999;
}

int D2542::getMax()
{
  return max;
}

void D2542::setMin(int nMin)
{
  min = nMin;
  if(min < 0)
    min = 0;
}

void D2542::setBrightness(int b)
{
  if(b > 100) b = 100;
  brightness = b;
}

int D2542::getBrightness()
{
  return brightness;
}

void D2542::isr()
{
  if(isr_handler)
    isr_handler->update();
}

//---
// private functions
//---

// setup the interrupt timer to update the display
void D2542::setupTimer1()
{
  TCCR1B |= (1 << WGM12) | (1 << CS11) | (1 << CS10);
  // 32 ms period, 31.25 updates/sec
  OCR1AL = 8;
}

void D2542::update()
{
  int i, j;

  uint8_t digits[4];
  digits[0] = floor(curNum/1000.0);
  digits[1] = floor(((curNum - (digits[0]*1000))/100));
  digits[2] = floor((curNum % 100)/10);
  digits[3] = floor((curNum % 10));

  ld = digits[3];

  for(i = 0; i < 4; i++) {
    for(j = 0; j < 7; j++) {
      if(!i) {
        digitalWrite(segments[1], digits[0]);
        digitalWrite(segments[2], digits[0]);
        break;
      }
      if(i == 2)
	digitalWrite(pPin, dp);

      digitalWrite(segments[j], CHARS[digits[i]][j]);
    }
    digitalWrite(grounds[i], LOW); 
    for(j=0; j < brightness; j++) __asm__("nop\n\t");
    digitalWrite(grounds[i], HIGH);
  }
}
