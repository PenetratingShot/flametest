/*
    vesa.c
    Copyright Shreyas Lad (PenetratingShot) 2020

    VESA Implementation
*/

#include <drivers/vesa.h>

fbargs_t args = {0, 0, 0, 0, 0};
uint64_t* addr = 0x00000000FD000000;

// epic Roboto-Light bitmap
uint8_t gylph_bitmap[] = {
    /* U+20 " " */
    0x0,

    /* U+21 "!" */
    0xff,
    0x10,

    /* U+22 "\"" */
    0xb6,
    0x80,

    /* U+23 "#" */
    0x12,
    0x12,
    0x22,
    0xff,
    0x24,
    0x24,
    0x24,
    0x24,
    0xff,
    0x44,
    0x48,
    0x48,

    /* U+24 "$" */
    0x10,
    0x71,
    0x14,
    0x18,
    0x30,
    0x10,
    0x1c,
    0xc,
    0x6,
    0xc,
    0x1c,
    0x6f,
    0x84,
    0x8,

    /* U+25 "%" */
    0x70,
    0x22,
    0x8,
    0x92,
    0x28,
    0x72,
    0x1,
    0x0,
    0x58,
    0x29,
    0x12,
    0x44,
    0x92,
    0x24,
    0x6,

    /* U+26 "&" */
    0x38,
    0x22,
    0x11,
    0x8,
    0x82,
    0x81,
    0x81,
    0xc1,
    0x92,
    0x85,
    0x41,
    0x31,
    0x8f,
    0x20,

    /* U+27 "'" */
    0xe0,

    /* U+28 "(" */
    0x12,
    0x44,
    0x88,
    0x88,
    0x88,
    0x88,
    0x44,
    0x42,
    0x10,

    /* U+29 ")" */
    0x84,
    0x22,
    0x21,
    0x11,
    0x11,
    0x11,
    0x22,
    0x44,
    0x80,

    /* U+2A "*" */
    0x10,
    0x23,
    0x59,
    0xc2,
    0x85,
    0x10,
    0x0,

    /* U+2B "+" */
    0x10,
    0x20,
    0x47,
    0xf1,
    0x2,
    0x4,
    0x8,

    /* U+2C "," */
    0x54,

    /* U+2D "-" */
    0xf0,

    /* U+2E "." */
    0x80,

    /* U+2F "/" */
    0x4,
    0x20,
    0x82,
    0x10,
    0x42,
    0x8,
    0x21,
    0x4,
    0x10,
    0x80,

    /* U+30 "0" */
    0x38,
    0x8a,
    0xc,
    0x18,
    0x30,
    0x60,
    0xc1,
    0x83,
    0x5,
    0x11,
    0xc0,

    /* U+31 "1" */
    0x1f,
    0x11,
    0x11,
    0x11,
    0x11,
    0x11,

    /* U+32 "2" */
    0x3c,
    0x46,
    0x82,
    0x82,
    0x2,
    0x4,
    0x8,
    0x18,
    0x10,
    0x20,
    0x40,
    0xff,

    /* U+33 "3" */
    0x3d,
    0x8e,
    0x8,
    0x10,
    0x47,
    0x1,
    0x1,
    0x83,
    0x5,
    0x11,
    0xc0,

    /* U+34 "4" */
    0x2,
    0x3,
    0x2,
    0x81,
    0x41,
    0x21,
    0x10,
    0x88,
    0x84,
    0xff,
    0x81,
    0x0,
    0x80,
    0x40,

    /* U+35 "5" */
    0x7e,
    0x81,
    0x2,
    0xb,
    0x98,
    0x80,
    0x81,
    0x3,
    0x5,
    0x11,
    0xc0,

    /* U+36 "6" */
    0x18,
    0x41,
    0x4,
    0xb,
    0x98,
    0xa0,
    0xc1,
    0x83,
    0x5,
    0x11,
    0xc0,

    /* U+37 "7" */
    0xfe,
    0x4,
    0x10,
    0x20,
    0x81,
    0x2,
    0x8,
    0x10,
    0x40,
    0x82,
    0x0,

    /* U+38 "8" */
    0x7d,
    0x8e,
    0xc,
    0x14,
    0x47,
    0x11,
    0x41,
    0x83,
    0x7,
    0x1b,
    0xc0,

    /* U+39 "9" */
    0x38,
    0x8a,
    0xc,
    0x18,
    0x30,
    0x51,
    0x9d,
    0x2,
    0x8,
    0x31,
    0x80,

    /* U+3A ":" */
    0x80,
    0x80,

    /* U+3B ";" */
    0x40,
    0x1,
    0x50,

    /* U+3C "<" */
    0x2,
    0x18,
    0xc6,
    0x6,
    0x3,
    0x1,
    0x80,

    /* U+3D "=" */
    0xfe,
    0x0,
    0x7,
    0xf0,

    /* U+3E ">" */
    0x80,
    0xc0,
    0x60,
    0x30,
    0x8e,
    0x20,
    0x0,

    /* U+3F "?" */
    0x7b,
    0x38,
    0x41,
    0x4,
    0x21,
    0x8,
    0x20,
    0x0,
    0x8,

    /* U+40 "@" */
    0xf,
    0x80,
    0x83,
    0x8,
    0x4,
    0x86,
    0x2c,
    0x48,
    0xc4,
    0x46,
    0x22,
    0x32,
    0x11,
    0x90,
    0x8c,
    0x84,
    0x62,
    0x64,
    0x9c,
    0xc6,
    0x0,
    0x18,
    0x0,
    0x7c,
    0x0,

    /* U+41 "A" */
    0xc,
    0x3,
    0x0,
    0xc0,
    0x48,
    0x12,
    0x4,
    0x82,
    0x10,
    0x84,
    0x7f,
    0x90,
    0x24,
    0xa,
    0x1,

    /* U+42 "B" */
    0xfc,
    0x86,
    0x82,
    0x82,
    0x86,
    0xf8,
    0x86,
    0x81,
    0x81,
    0x81,
    0x82,
    0xfc,

    /* U+43 "C" */
    0x3c,
    0x31,
    0x90,
    0x50,
    0x28,
    0x4,
    0x2,
    0x1,
    0x0,
    0x81,
    0x20,
    0x98,
    0xc7,
    0x80,

    /* U+44 "D" */
    0xf8,
    0x86,
    0x82,
    0x81,
    0x81,
    0x81,
    0x81,
    0x81,
    0x81,
    0x82,
    0x86,
    0xf8,

    /* U+45 "E" */
    0xff,
    0x2,
    0x4,
    0x8,
    0x1f,
    0xa0,
    0x40,
    0x81,
    0x2,
    0x7,
    0xf0,

    /* U+46 "F" */
    0xff,
    0x2,
    0x4,
    0x8,
    0x10,
    0x3f,
    0x40,
    0x81,
    0x2,
    0x4,
    0x0,

    /* U+47 "G" */
    0x3e,
    0x30,
    0x90,
    0x30,
    0x8,
    0x4,
    0x2,
    0x1f,
    0x1,
    0x80,
    0xa0,
    0x58,
    0x63,
    0xc0,

    /* U+48 "H" */
    0x81,
    0x81,
    0x81,
    0x81,
    0x81,
    0xff,
    0x81,
    0x81,
    0x81,
    0x81,
    0x81,
    0x81,

    /* U+49 "I" */
    0xff,
    0xf0,

    /* U+4A "J" */
    0x2,
    0x4,
    0x8,
    0x10,
    0x20,
    0x40,
    0x81,
    0x83,
    0x7,
    0x13,
    0xc0,

    /* U+4B "K" */
    0x83,
    0x86,
    0x84,
    0x88,
    0x90,
    0xa0,
    0xd0,
    0x88,
    0x84,
    0x84,
    0x82,
    0x81,

    /* U+4C "L" */
    0x81,
    0x2,
    0x4,
    0x8,
    0x10,
    0x20,
    0x40,
    0x81,
    0x2,
    0x7,
    0xf0,

    /* U+4D "M" */
    0xc0,
    0x78,
    0xf,
    0x1,
    0xd0,
    0x5a,
    0xb,
    0x22,
    0x64,
    0x4c,
    0x89,
    0x8a,
    0x31,
    0x46,
    0x30,
    0xc2,
    0x10,

    /* U+4E "N" */
    0x81,
    0xc1,
    0xc1,
    0xa1,
    0x91,
    0x91,
    0x89,
    0x89,
    0x85,
    0x83,
    0x83,
    0x81,

    /* U+4F "O" */
    0x3e,
    0x31,
    0x90,
    0x50,
    0x18,
    0xc,
    0x6,
    0x3,
    0x1,
    0x80,
    0xa0,
    0x98,
    0xc7,
    0xc0,

    /* U+50 "P" */
    0xfc,
    0x82,
    0x81,
    0x81,
    0x81,
    0x82,
    0xfc,
    0x80,
    0x80,
    0x80,
    0x80,
    0x80,

    /* U+51 "Q" */
    0x3e,
    0x31,
    0x90,
    0x50,
    0x18,
    0xc,
    0x6,
    0x3,
    0x1,
    0x80,
    0xa0,
    0x98,
    0xc7,
    0xc0,
    0x10,
    0x4,

    /* U+52 "R" */
    0xfc,
    0x82,
    0x81,
    0x81,
    0x81,
    0x82,
    0xfc,
    0x84,
    0x86,
    0x82,
    0x81,
    0x81,

    /* U+53 "S" */
    0x3c,
    0xc2,
    0x81,
    0x81,
    0xc0,
    0x30,
    0xe,
    0x3,
    0x81,
    0x81,
    0x43,
    0x3c,

    /* U+54 "T" */
    0xff,
    0x84,
    0x2,
    0x1,
    0x0,
    0x80,
    0x40,
    0x20,
    0x10,
    0x8,
    0x4,
    0x2,
    0x1,
    0x0,

    /* U+55 "U" */
    0x81,
    0x81,
    0x81,
    0x81,
    0x81,
    0x81,
    0x81,
    0x81,
    0x81,
    0x81,
    0x42,
    0x3c,

    /* U+56 "V" */
    0x80,
    0x90,
    0x24,
    0x9,
    0x4,
    0x21,
    0x8,
    0x41,
    0x20,
    0x48,
    0x12,
    0x3,
    0x0,
    0xc0,
    0x30,

    /* U+57 "W" */
    0x41,
    0x5,
    0xc,
    0x14,
    0x30,
    0x90,
    0xa2,
    0x24,
    0x88,
    0x92,
    0x22,
    0x49,
    0x9,
    0x14,
    0x28,
    0x50,
    0x61,
    0x41,
    0x86,
    0x4,
    0x8,

    /* U+58 "X" */
    0x40,
    0x90,
    0x88,
    0x42,
    0x41,
    0xc0,
    0x60,
    0x30,
    0x28,
    0x12,
    0x10,
    0x98,
    0x48,
    0x10,

    /* U+59 "Y" */
    0x80,
    0xa0,
    0x90,
    0x44,
    0x42,
    0x20,
    0xa0,
    0x70,
    0x10,
    0x8,
    0x4,
    0x2,
    0x1,
    0x0,

    /* U+5A "Z" */
    0xff,
    0x3,
    0x2,
    0x4,
    0xc,
    0x8,
    0x10,
    0x30,
    0x20,
    0x40,
    0xc0,
    0xff,

    /* U+5B "[" */
    0xf2,
    0x49,
    0x24,
    0x92,
    0x49,
    0x27,

    /* U+5C "\\" */
    0x81,
    0x4,
    0x8,
    0x20,
    0x81,
    0x4,
    0x10,
    0x20,
    0x81,
    0x4,

    /* U+5D "]" */
    0xe4,
    0x92,
    0x49,
    0x24,
    0x92,
    0x4f,

    /* U+5E "^" */
    0x23,
    0x15,
    0x29,
    0x44,

    /* U+5F "_" */
    0xfe,

    /* U+60 "`" */
    0x94,

    /* U+61 "a" */
    0x3d,
    0x8e,
    0x8,
    0x13,
    0xf8,
    0x60,
    0xc3,
    0x7a,

    /* U+62 "b" */
    0x81,
    0x2,
    0x5,
    0xcc,
    0x50,
    0x60,
    0xc1,
    0x83,
    0x7,
    0x15,
    0xc0,

    /* U+63 "c" */
    0x3c,
    0x8e,
    0xc,
    0x8,
    0x10,
    0x20,
    0xa3,
    0x3c,

    /* U+64 "d" */
    0x2,
    0x4,
    0x9,
    0xd4,
    0x70,
    0x60,
    0xc1,
    0x83,
    0x5,
    0x19,
    0xd0,

    /* U+65 "e" */
    0x38,
    0x8a,
    0xc,
    0x1f,
    0xf0,
    0x20,
    0x21,
    0x3c,

    /* U+66 "f" */
    0x3a,
    0x10,
    0x8f,
    0x21,
    0x8,
    0x42,
    0x10,
    0x84,
    0x0,

    /* U+67 "g" */
    0x3a,
    0x8e,
    0xc,
    0x18,
    0x30,
    0x60,
    0xa3,
    0x3a,
    0x5,
    0x11,
    0xc0,

    /* U+68 "h" */
    0x82,
    0x8,
    0x2e,
    0xce,
    0x18,
    0x61,
    0x86,
    0x18,
    0x61,

    /* U+69 "i" */
    0x9f,
    0xf0,

    /* U+6A "j" */
    0x20,
    0x12,
    0x49,
    0x24,
    0x92,
    0x70,

    /* U+6B "k" */
    0x81,
    0x2,
    0x4,
    0x28,
    0x92,
    0x28,
    0x70,
    0x91,
    0x12,
    0x24,
    0x20,

    /* U+6C "l" */
    0xff,
    0xf0,

    /* U+6D "m" */
    0xb9,
    0xd9,
    0xce,
    0x10,
    0xc2,
    0x18,
    0x43,
    0x8,
    0x61,
    0xc,
    0x21,
    0x84,
    0x20,

    /* U+6E "n" */
    0xbb,
    0x38,
    0x61,
    0x86,
    0x18,
    0x61,
    0x84,

    /* U+6F "o" */
    0x3c,
    0x42,
    0x81,
    0x81,
    0x81,
    0x81,
    0x81,
    0x42,
    0x3c,

    /* U+70 "p" */
    0xb9,
    0x8a,
    0xc,
    0x18,
    0x30,
    0x60,
    0xe2,
    0xb9,
    0x2,
    0x4,
    0x0,

    /* U+71 "q" */
    0x3a,
    0x8e,
    0xc,
    0x18,
    0x30,
    0x60,
    0xa3,
    0x3a,
    0x4,
    0x8,
    0x10,

    /* U+72 "r" */
    0xbc,
    0x88,
    0x88,
    0x88,
    0x80,

    /* U+73 "s" */
    0x7a,
    0x38,
    0x70,
    0x30,
    0x38,
    0x71,
    0x78,

    /* U+74 "t" */
    0x21,
    0x9,
    0xf2,
    0x10,
    0x84,
    0x21,
    0x8,
    0x30,

    /* U+75 "u" */
    0x86,
    0x18,
    0x61,
    0x86,
    0x18,
    0x73,
    0x74,

    /* U+76 "v" */
    0x82,
    0x85,
    0xa,
    0x22,
    0x45,
    0x6,
    0xc,
    0x10,

    /* U+77 "w" */
    0x46,
    0x24,
    0x62,
    0x46,
    0x24,
    0xa2,
    0x29,
    0x42,
    0x94,
    0x29,
    0x41,
    0x8,
    0x10,
    0x80,

    /* U+78 "x" */
    0x42,
    0xc8,
    0x90,
    0xc1,
    0x3,
    0x9,
    0x22,
    0x42,

    /* U+79 "y" */
    0x82,
    0x85,
    0x11,
    0x22,
    0x45,
    0x6,
    0xc,
    0x10,
    0x20,
    0xc3,
    0x0,

    /* U+7A "z" */
    0xfe,
    0x8,
    0x20,
    0xc1,
    0x4,
    0x10,
    0x60,
    0xfe,

    /* U+7B "{" */
    0x8,
    0x88,
    0x42,
    0x10,
    0x8c,
    0xc3,
    0x8,
    0x42,
    0x10,
    0x82,
    0x8,

    /* U+7C "|" */
    0xff,
    0xfc,

    /* U+7D "}" */
    0x82,
    0x8,
    0x42,
    0x10,
    0x86,
    0x9,
    0x88,
    0x42,
    0x10,
    0x88,
    0x80,

    /* U+7E "~" */
    0x70,
    0xc4,
    0x61,
    0xc0};

void setScreen() { ; }

void setPixel(uint64_t x, uint64_t y, uint32_t color) {
  size_t fb_i = x + (args.fbpitch / sizeof(uint32_t)) * y;
  addr[fb_i] = color;
}

void clearPixel(uint64_t x, uint64_t y) {
  size_t fb_i = x + (args.fbpitch / sizeof(uint32_t)) * y;
  addr[fb_i] = 0xFFFFFFFF;
  return;
}