#pragma once 
#include <Arduboy2.h>

class Mode7{
  public:
    Mode7(const uint8_t *bitmap){ Bitmap = bitmap; Rotation = 0; Xpos = 0; Ypos = 0; };
    void Draw();
    void SetRotation(uint8_t r){ Rotation = r; };
    void SetPosition(uint16_t x, uint16_t y){ Xpos = x; Ypos = y; };
  private:
    uint8_t Rotation;
    uint16_t Xpos,Ypos;
    const uint8_t *Bitmap;
};

