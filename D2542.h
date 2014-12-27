#ifndef H_2542AB
#define H_2542AB

#include "Arduino.h"

// TODO: store digit codes in a singe byte
//       and ditch this quick fix
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
  D2542(int16_t Ap, int16_t Bp, int16_t Cp, int16_t Dp,
        int16_t Ep, int16_t Fp, int16_t Gp, int16_t pP,
        int16_t g1, int16_t g2, int16_t g3, int16_t g4);

  void setNumber(int num);
  int getNumber();

  void setMax(int m);
  int getMax();
  void setMin(int m);
  int getMin();

  void setBrightness(int brightness);
  int getBrightness();
  
  void on();
  void off();
  bool isOn();
  
  static void isr();

  int ld;

 protected:
  void update();

 private:
  int16_t segments[7];
  int16_t pPin;
  int16_t grounds[4];

  int max;
  int min;
  int brightness;

  static  D2542* isr_handler;

  int curNum;
  bool isDispOn;
  bool dp;

  void setupTimer1();

};

#endif
