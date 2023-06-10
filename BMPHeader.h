#pragma once
#include <cinttypes>
#pragma pack(push, 1)
typedef struct
{
	uint8_t id[2];				 // Завжди дві літери 'B' і 'M'
	uint32_t filesize;			 // Розмір файла в байтах
	uint16_t reserved[2];		 // 0, 0
	uint32_t headersize;		 // 54L для 24-бітних зображень
	uint32_t infoSize;			 // 40L для 24-бітних зображень
	uint32_t width;				 // ширина зображення в пікселях
	uint32_t depth;				 // висота зображення в пікселях
	uint16_t biPlanes;			 // 1 (для 24-бітних зображень)
	uint16_t bits;				 // 24 (для 24-бітних зображень)
	uint32_t biCompression;	 // 0L
	uint32_t biSizeImage;		 // Можна поставити в 0L для зображень без компрессії (наш варіант)
	uint32_t biXPelsPerMeter; // Рекомендована кількість пікселів на метр, можна 0L
	uint32_t biYPelsPerMeter; // Те саме, по висоті
	uint32_t biClrUsed;		 // Для індексованих зображень, можна поставити 0L
	uint32_t biClrImportant;	 // Те саме
} BMPHEAD;

typedef struct
{
	uint8_t redComponent;
	uint8_t greenComponent;
	uint8_t blueComponent;
} PIXELDATA;
#pragma pack(pop)