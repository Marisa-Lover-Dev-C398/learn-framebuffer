#include <stdint.h> 
#ifdef LIBMARIX_FB_H
#define LIBMARIX_FB_H

struct dot {
  int x;
  int y;
  uint32_t color;
};

struct obj {
  struct dot* shape;
  size_t size;
  int x;
  int y;
};

struct fb_info {
  uint32_t* fbp;
  int fb_width;
  int fb_height;
  size_t sc_size;
};

int minit();

void fill(int x, int y, int width, int height, uint32_t color);

int loc2addr(int x, int y);

void dsync();

#endif
