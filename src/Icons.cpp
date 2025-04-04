#include "Icons.h"
// 'heavy-rain', 32x32px
const unsigned char epd_bitmap_heavy_rain [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x7f, 0xe0, 0x00, 0x00, 0xff, 0xf0, 0x00, 
	0x01, 0xff, 0xf8, 0x00, 0x03, 0xff, 0xff, 0x80, 0x03, 0xff, 0xff, 0xe0, 0x07, 0xff, 0xff, 0xf0, 
	0x0f, 0xff, 0xff, 0xf8, 0x1f, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xfe, 
	0x7f, 0xff, 0xff, 0xfe, 0x7f, 0xff, 0xff, 0xfe, 0x7f, 0xff, 0xff, 0xfe, 0x7f, 0xff, 0xff, 0xfc, 
	0x3f, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xf8, 0x1f, 0xff, 0xff, 0xf0, 0x0f, 0xff, 0xff, 0xe0, 
	0x03, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x02, 0x08, 0x20, 0x80, 0x02, 0x08, 0x20, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x82, 0x08, 0x00, 0x00, 0x82, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
// 'sunny', 32x32px
const unsigned char icon_sunny [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0x82, 0x00, 0x00, 0xc3, 0xce, 0x00, 
	0x00, 0xf7, 0xfe, 0x00, 0x00, 0xff, 0xfe, 0x00, 0x00, 0xff, 0xff, 0x70, 0x1f, 0xff, 0xff, 0xf0, 
	0x0f, 0xff, 0xff, 0xf0, 0x0f, 0xff, 0xff, 0xe0, 0x07, 0xff, 0xff, 0xe0, 0x07, 0xff, 0xff, 0xf8, 
	0x1f, 0xff, 0xff, 0xfe, 0x7f, 0xff, 0xff, 0xfc, 0x7f, 0xff, 0xff, 0xf8, 0x1f, 0xff, 0xff, 0xf0, 
	0x0f, 0xff, 0xff, 0xf8, 0x0f, 0xff, 0xff, 0xfc, 0x1f, 0xff, 0xff, 0xfe, 0x3f, 0xff, 0xff, 0xfe, 
	0x7f, 0xff, 0xff, 0xf0, 0x07, 0xff, 0xff, 0xe0, 0x07, 0xff, 0xff, 0xf0, 0x07, 0xff, 0xff, 0xf0, 
	0x07, 0xff, 0xff, 0xf0, 0x0f, 0xff, 0xff, 0x00, 0x00, 0x7f, 0xff, 0x00, 0x00, 0x7f, 0xff, 0x00, 
	0x00, 0x7b, 0xe7, 0x00, 0x00, 0x21, 0xc2, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00
};
// 'cloudy', 32x32px
const unsigned char epd_bitmap_cloudy [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 
	0x00, 0x3f, 0xc0, 0x00, 0x00, 0x7f, 0xe0, 0x00, 0x00, 0xff, 0xf0, 0x00, 0x01, 0xff, 0xff, 0x00, 
	0x01, 0xff, 0xff, 0xc0, 0x01, 0xff, 0xff, 0xe0, 0x03, 0xff, 0xff, 0xe0, 0x0f, 0xff, 0xff, 0xe0, 
	0x1f, 0xff, 0xff, 0xf0, 0x3f, 0xff, 0xff, 0xf8, 0x3f, 0xff, 0xff, 0xfe, 0x3f, 0xff, 0xff, 0xfe, 
	0x3f, 0xff, 0xff, 0xff, 0x3f, 0xff, 0xff, 0xff, 0x3f, 0xff, 0xff, 0xff, 0x3f, 0xff, 0xff, 0xff, 
	0x1f, 0xff, 0xff, 0xfe, 0x1f, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xf8, 0x7f, 0xff, 0xfe, 0x00, 
	0xff, 0xff, 0xfe, 0x00, 0xff, 0xff, 0xfe, 0x00, 0xff, 0xff, 0xfc, 0x00, 0x7f, 0xff, 0xf8, 0x00, 
	0x3f, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// 'fog', 32x32px
const unsigned char epd_bitmap_fog [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0x1f, 0xff, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xc7, 0xfe, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xfc, 0x78, 
	0x00, 0xff, 0xfc, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x07, 0xfc, 0x3f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};