#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/ioctl.h>
#include<sys/mman.h>
#include<linux/fb.h>
#include<stdint.h>
#include<math.h>

#define FB_PATH "/dev/fb0"

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
  while(1){
    //(fb_height/2) + (int)(sin(x * 0.1)*100);
  }
  munmap(fbp,vfinfo.smem_len); 
}
