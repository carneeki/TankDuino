#include "Arduino.h"
#include "Tank.h"

Tank tank(3,5,6,9);

void setup()
{
  // put your setup code here, to run once:
  tank.setCannon(13); // pin 13 is often used for an onboard LED
}

void loop()
{
  doSquare(4000,1000); // 20s to complete a square
}

/*
 * Draw a square. NOTE: turning 90 degrees might take a little experimentation
 * to get the timing right!
 *
 * unsigned long fwdS number of milliseconds to drive forwards for
 * unsigned long leftS number of milliseconds for left turns
 */
void doSquare(unsigned long fwd, unsigned long left)
{
  for(int i=0; i <=3; i++)
  {
    tank.forwards(fwd);
    tank.left(left);
  }
  // at the end of the square, maybe fire the cannon
  tank.fire();
  tank.forwards(100); // correct for recoil ;)
}
