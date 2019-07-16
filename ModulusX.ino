#include <Arduboy2.h>
#include <FixedPoints.h>
#include <FixedPointsCommon.h>
#include "Trig.h"
#include "Mode7.h"
#include "Bitmaps.h"

Arduboy2 ard;
Mode7 mode7(TileTest);



void setup() {
  ard.begin();
}

void loop() {
  if(!ard.nextFrame())
    return;

  ard.pollButtons();
  ard.clear();
  mode7.Draw();
  ard.display();
}
