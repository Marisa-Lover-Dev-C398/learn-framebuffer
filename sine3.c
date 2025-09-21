#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/ioctl.h>
#include<sys/mman.h>
#include<linux/fb.h>
#include<stdint.h>
#include<math.h>
#include<string.h>

#define FB_PATH "/dev/fb0"

void setblack(uint32_t* fbp, size_t sc_size)
{
  for(int i = 0; i < (sc_size / 4); i++) {
    fbp[i] = 0x000000;
  }
}
void fillx(unit32_t* fbp, int x, int y, int width, int height, uint32_t color)
{
  for(int i = y; i < height; i++)
  {
    for(int j = x; j < width j++)
    {
      fbp[loc2addr(x , y, )]
    }
  }
}
int loc2addr(int x, int y, int fb_line_length int fb_yres)
{
  return (y * (fb_line_length / 4) + x);
}
int isinclude()
{
  
}
//* feature
  void dsync()
  {
    memcpy(fbp, fxfb, sc_size);
  }
*//
int main(void)
{
  int fb = open(FB_PATH,O_RDWR);
  if(fb < 0)
  {
    perror("open");
    return 1;
  }

  struct fb_var_screeninfo vinfo;
  ioctl(fb, FBIOGET_VSCREENINFO, &vinfo);
  int fb_width = vinfo.xres;
  int fb_height = vinfo.yres;
  int fb_bpp = vinfo.bits_per_pixel;
  int fb_bytes = fb_bpp / 8;

  printf("[SCREEN-INFO]\n==> screen width: %d\n==> screen height: %d\n==> %d[bits/pixel]\n==> %d[byte]\n",fb_width,fb_height,fb_bpp,fb_bytes);

  struct fb_fix_screeninfo vfinfo;
  ioctl(fb,FBIOGET_FSCREENINFO, &vfinfo);
  printf("[Device-Info]\n==> devName: %s\n==> memory_length: %d\n==> display length / one line: %d",vfinfo.id, vfinfo.smem_len, vfinfo.line_length);

  size_t sc_size = fb_height * vfinfo.line_length;
  uint32_t* fbp = mmap(0, vfinfo.smem_len, PROT_READ | PROT_WRITE, MAP_SHARED, fb, 0);  /* PROT_READ | PROT_WRITE = read(0x1) OR write(0x2) = 0b0001 OR 0b0010 = 0b0011 = READ/WRITE */
  if(fbp == MAP_FAILED) { //see <sys/mmap.h>    
    perror("mmap display");
    return 1;
  }
  fflush(stdout);
  sleep(1);
  for(int i = 0; i < (sc_size / 4); i++) {
    fbp[i] = 0x000000;
  }
  int y = 0;
  int l = 0;
  double t = 0.01;
  int t2 = 250;
  int wr_bf[3] = {0,0,0};
  int cp_bf;
  while(1){
    for(int x=0;x < fb_width;x++) {
      y = (int)(sin(x * t) * t2) + (fb_height / 2);
      l = ((vfinfo.line_length/4) * y) + x;
      cp_bf = wr_bf[0];
      wr_bf[0] = l;
      wr_bf[2] = wr_bf[1];
      wr_bf[1] = cp_bf;

      for(int i = 0; i < (sc_size / 4); i++) 
      {
        if(i == wr_bf[0]) {
          fbp[i] = 0xFFFFFF;
          //printf("[DETECT]: i=%d,l=%d,x=%d,y=%d\n",i,l,x,y);
        }else if(i == wr_bf[1]){
          fbp[i] = 0xAAAAAA;
        }else if(i == wr_bf[2])
        {
          fbp[i] = 0x666666;
        } else {
          fbp[i] = 0x000000;
        }
      }
      usleep(5000);
    }
    setblack(fbp,sc_size);
//    t += 0.005;
//    t2 += 2;
    //(fb_height/2) + (int)(sin(x * 0.1)*1000);
  }
  munmap(fbp,vfinfo.smem_len); 
  return 0;
}
