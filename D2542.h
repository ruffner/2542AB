#ifndef H_2542AB
#define H_2542AB

#include "Arduino.h"

// TODO: store digit codes in a singe byte
//       and ditch this quick fix. 
static const bool CHARS[10][7] = {{1,1,1,1,1,1,0},
                              {0,1,1,0,0,0,0},
                              {1,1,0,1,1,0,1},
                              {1,1,1,1,0,0,1},
                              {0,1,1,0,0,1,1},
                              {1,0,1,1,0,1,1},
                              {1,0,1,1,1,1,1},
                              {1,1,1,0,0,0,0},
                              {1,1,1,1,1,1,1},
                              {1,1,1,1,0,1,1}};

class D2542 {
 public:
  
  D2542();
  //      A            B           C           D
  D2542(int16_t Ap, int16_t Bp, int16_t Cp, int16_t Dp,
	//   E         F           G       decimal point
        int16_t Ep, int16_t Fp, int16_t Gp, int16_t pP,
	// numbering starts with the half digit and moves left
	// ground1   ground2     ground3      ground4
        int16_t g1, int16_t g2, int16_t g3, int16_t g4);

  // getters and setters for changeable settings

  // the number to show, 0-1999
  void setNumber(int num);
  int getNumber();
  
  // easy way to put a limit on what is showing
  void setMax(int m);
  int getMax();
  void setMin(int m);
  int getMin();

  // decimal point
  void setDP(bool d);
  bool getDP();


  // this just controls how many NOPs each digit 
  // is on as it scans to update. the number correlates 
  // directly to the NOP count, past 40  or so (~2.5ms @ 16Mhz)
  // the difference becomes less noticeable
  void setBrightness(int b);
  int getBrightness();
  
  // enables the timer1 overflow interrupt that
  // controls refreshing, default is about 31/sec
  void on();

  // disables the interrupt and darkens the display
  void off();
  // getter
  bool isOn();
  
  // the real ISR's shoe into the members
  static void isr();

 protected:
  // the meat of the ISR routine
  void update();

 private:
  // configure the update routine
  void setupTimer1();

  // pin containers
  int16_t segments[7];
  int16_t pPin;
  int16_t grounds[4];

  // the caps
  int max;
  int min;
  // 0 will just be very dim, past 40 its just wasteful
  int brightness;

  // the reference for the ISR to use
  static  D2542* handler;

  int curNum;
  bool isDispOn;

  // decimal control
  bool dp;

};

#endif
