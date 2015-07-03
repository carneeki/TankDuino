#include "Arduino.h"

class Tank
{
  public:
    Tank(byte pinLF, byte pinLR, byte pinRF, byte pinRR);
    void setCannon(byte pinCannon);
    void fire();
    void forwards(unsigned long ms);
    void reverse(unsigned long ms);
    void left(unsigned long ms);
    void right(unsigned long ms);
    void wait(unsigned long ms);

  private:
    byte cannon;
    byte lf;
    byte lr;
    byte rf;
    byte rr;
    void _stopAll();
    void _drive(unsigned long ms, byte pin1, byte pin2);
};
