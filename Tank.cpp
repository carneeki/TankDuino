#include "Arduino.h"
#include "Tank.h"

Tank::Tank(byte pinLF, byte pinLR, byte pinRF, byte pinRR)
{
  lf = pinLF;
  lr = pinLR;
  rf = pinRF;
  rr = pinRR;

  pinMode(lf, OUTPUT);
  pinMode(lr, OUTPUT);
  pinMode(rf, OUTPUT);
  pinMode(rr, OUTPUT);

  _stopAll();
}

void Tank::setCannon(byte pinCannon)
{
  cannon = pinCannon;
  pinMode(cannon, OUTPUT);
}

/*
 * BOOM!
 */
void Tank::fire()
{
  unsigned long start = millis();
  _stopAll();

  while(millis() - start <= 100)
  {
    digitalWrite(cannon, HIGH);

    // recoil!
    analogWrite(lr,255);
    analogWrite(rr,255);
  }

  digitalWrite(cannon, LOW);
  _stopAll();
}

/*
 * drive forwards for n seconds
 */
void Tank::forwards(unsigned long ms)
{
  // left forward, right forwards
  _drive(ms, lf, rf);
}

/*
 * pivot left for n seconds
 */
void Tank::left(unsigned long ms)
{
  // left reverse, right forwards
  _drive(ms, lr, rf);
}

/*
 * drive backwards for n seconds
 */
void Tank::reverse(unsigned long ms)
{
  // left reverse, right reverse
  _drive(ms, lr, rr);
}

/*
 * pivot right for n seconds
 */
void Tank::right(unsigned long ms)
{
  // left forwards, right reverse
  _drive(ms, lf, rr);
}

void Tank::_drive(unsigned long ms, byte pin1, byte pin2)
{
  unsigned long start;

  _stopAll();
  start = millis();

  while(millis() - start <= ms )
  {
    analogWrite(pin1,255);
    analogWrite(pin2,255);
  }

  _stopAll();
}

void Tank::_stopAll()
{
  analogWrite(lf,0);
  analogWrite(rf,0);
  analogWrite(lr,0);
  analogWrite(rr,0);
}
