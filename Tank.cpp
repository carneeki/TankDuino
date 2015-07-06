#include "Arduino.h"
#include "Tank.h"

/**
 * Create a new TankDuino object
 *
 * Drive motors are controlled via an H-bridge motor controller where each
 * transistor (or FET or similar) is controlled by one of four pins.
 *
 * Left Forward, Left Reverse, Right Forward, and Right Reverse.
 *
 * byte pinLF pin that left forward FET gate is connected to
 * byte pinLR pin that left reverse FET gate is connected to
 * byte pinRF pin that right forward FET gate is connected to
 * byte pinRR pin that right reverse FET gate is connected to
 */
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

/**
 * Control an LED (or piezo, or maybe both?) that is turned on and off when the
 * "cannon" is fired.
 * byte pinCannon pin that the cannon LED is connected to.
 */
void Tank::setCannon(byte pinCannon)
{
  cannon = pinCannon;
  pinMode(cannon, OUTPUT);
}

/**
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

/**
 * Drive forwards for n milliseconds.
 * unsigned long ms number of milliseconds to drive for
 */
void Tank::forwards(unsigned long ms)
{
  // left forward, right forwards
  _drive(ms, lf, rf);
}

/**
 * Pivot left for n milliseconds.
 * unsigned long ms number of milliseconds to drive for
 */
void Tank::left(unsigned long ms)
{
  // left reverse, right forwards
  _drive(ms, lr, rf);
}

/**
 * Drive backwards for n milliseconds.
 * unsigned long ms number of milliseconds to drive for
 */
void Tank::reverse(unsigned long ms)
{
  // left reverse, right reverse
  _drive(ms, lr, rr);
}

/**
 * Pivot right for n milliseconds.
 * unsigned long ms number of milliseconds to drive for
 */
void Tank::right(unsigned long ms)
{
  // left forwards, right reverse
  _drive(ms, lf, rr);
}

/**
 * Drive motors for n milliseconds. give it two pins.
 * DOES NOT check for shoot through conditions, so be careful to not
 * burn out the transistors/FETs.
 *
 * unsigned long ms number of milliseconds to drive for
 * byte pin1 one pin to control
 * byte pin2 the other pin to control
 */
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

/**
 * ensure all movement stopped
 */
void Tank::_stopAll()
{
  analogWrite(lf,0);
  analogWrite(rf,0);
  analogWrite(lr,0);
  analogWrite(rr,0);
}
