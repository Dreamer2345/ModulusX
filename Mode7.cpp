#include <Arduboy2.h>
#include "Mode7.h"

bool GetPixelOnTexture(const uint8_t *bitmap,uint8_t x, uint8_t y){
  uint8_t Width = pgm_read_byte(bitmap);
  uint8_t Height = pgm_read_byte(++bitmap);
  bitmap++;   
  uint8_t BytesPerRow = Height << 3;
  uint8_t byteY = (y << 3) % BytesPerRow;
  uint8_t byteX = (x % Width); 
  uint8_t *MemAddr = (uint8_t *)(bitmap + ((byteX - 1) * BytesPerRow)+byteY);
 
  uint8_t subByteY = y % 8;
  uint8_t BitMask = 1 << subByteY;
  uint8_t ByteFromBitmap = pgm_read_byte(MemAddr);
  uint8_t Return = (ByteFromBitmap & BitMask) >> subByteY;
  
  if(Return == 1)
    return true;
  else
    return false;
}

void Mode7::Draw(){
  for(uint8_t x = 0; x < 128; x++)
    for(uint8_t y = 0; y < 8; y++)
    {
      uint8_t BufferByte = 0;
      for(uint8_t i = (y * 8); i < (y * 8)+8; i++){
        bool PixelValue = GetPixelOnTexture(Bitmap,x,y+i);
        if(PixelValue){
          BufferByte |= 1;
        }
        BufferByte = BufferByte << 1;
      }
      Arduboy2Base::sBuffer[(x * 8) + (y)] = BufferByte;
    }
}
