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

inline uint8_t GetPixel(const uint8_t * bitmap, uint8_t x, uint8_t y, uint8_t width)
{
	const uint8_t row = (y / 8);
	const uint8_t bitShift = (y % 8);
	const uint8_t bitMask = (1 << bitShift);
	const uint8_t byteValue = pgm_read_byte(&bitmap[2 + (row * width) + x]);

	return static_cast<uint8_t>((byteValue & bitMask) >> bitShift);
}

inline uint8_t GetPixel(const uint8_t * bitmap, uint8_t x, uint8_t y)
{
	const uint8_t width = pgm_read_byte(&bitmap[0]);

	return GetPixel(bitmap, x, y, width);
}

inline uint8_t GetPixelWrapped(const uint8_t * bitmap, uint8_t x, uint8_t y)
{
	const uint8_t width = pgm_read_byte(&bitmap[0]);
	const uint8_t height = pgm_read_byte(&bitmap[1]);
	
	const uint8_t wrappedX = (x % width);
	const uint8_t wrappedY = (y % height);
	
	return GetPixel(bitmap, wrappedX, wrappedY, width);
}

void Mode7::Draw()
{	
	constexpr uint8_t bufferWidth = WIDTH;
	constexpr uint8_t bufferHeight = (HEIGHT / 8);

	for(uint8_t x = 0; x < bufferWidth; ++x)
	{
		for(uint8_t y = 0; y < bufferHeight; ++y)
		{
			const uint8_t row = (y * 8);
		
			uint8_t BufferByte = 0;
			
			for(uint8_t i = 0; i < 8; ++i)
			{
				BufferByte <<= 1;
				
				uint8_t PixelValue = GetPixelWrapped(this->Bitmap, x, row + i);
				
				BufferByte |= PixelValue;
			}
			
			Arduboy2Base::sBuffer[(y * WIDTH) + x] = BufferByte;
		}
	}
}
