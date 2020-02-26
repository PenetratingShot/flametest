#include "kernel.h"

multiboot_memory_map_t* mmap;
uint32_t largestUseableMem = 0;

extern uint64_t __kernel_end;

void kmain(multiboot_info_t* mbd) {
  // disableCursor();
  /*args.fbaddr = mbd->framebuffer_addr;
  args.fbpitch = mbd->framebuffer_pitch;
  args.fbwidth = mbd->framebuffer_width;
  args.fbheight = mbd->framebuffer_height;
  args.fbbpp = mbd->framebuffer_bpp;

  coffset.roffset = mbd->framebuffer_red_field_position;
  coffset.goffset = mbd->framebuffer_green_field_position;
  coffset.boffset = mbd->framebuffer_blue_field_position;

  sprintf("Red: %d | Green: %d | Blue: %d\n",
		  coffset.roffset,
		  coffset.goffset,
		  coffset.boffset);*/

  isr_install();
  irq_install();

  // drawLogo();
  // wait_s(2);
  // enableCursor();

  clear();
  formatTime();
  kprint("flameOS\n");

  kprint("It is ");
  kprint(format);
  kprint(".");
  kprint("\nuser@flameOS # ");

  /*sprintf("\nBitmap Addr: %d\n", (uint64_t)bitmap);
  sprintf("MBD Total Mem: %d\n", mbd->mem_upper);
  sprintf("Framebuffer: %d\n", mbd->framebuffer_addr);
  sprintf("Screen: %dx%d | Pitch: %d\n",
		  args.fbwidth,
		  args.fbheight,
		  args.fbpitch);

  read_rtc();
  uint64_t framebuffer_size = mbd->framebuffer_height * mbd->framebuffer_pitch;
  sprintf("Framebuffer Calc: %d\n",
		  (framebuffer_size + 0x2000000 - 1) / 0x2000000);
  sprintf("fb_i: %d\n", 100 * (args.fbpitch / sizeof(uint32_t)) * 100);

  // test();
  vmap((uint64_t*)addr, (uint64_t)addr, 1);
  // setLargePixel(10, 10, createColor(LightRed));
  setPixel(0, 0, createColor(LightRed));*/
}

void user_input(char* input) {
  if (strcmp(input, "halt") == 0) {
	kprint("Halting CPU");
	asm volatile("hlt");
  } else if (strcmp(input, "time") == 0) {
	formatTime();

	kprint(format);
  } else if (strcmp(input, "clear") == 0) {
	clear();

	formatTime();

	kprint("flameOS\n");

	kprint("It is ");
	kprint(format);
	kprint(".");
  } else if (strcmp(input, "testMem") == 0) {
	uint64_t* addr = (uint64_t*)malloc(35);
	sprint("Addr: ");
	sprint_uint((uint64_t)addr);
	sprint("\n");
  } else if (strcmp(input, "res") == 0) {
	// getResolution();
  } else if (strcmp(input, "neofetch") == 0) {
	// neofetch(largestUseableMem);
  } else if (strcmp(input, "uptime") == 0) {
	calculateUptime();
  } else if (strcmp(input, "drives") == 0) {
	drive_scan();
	if (hdd.mp == 0 || hdd.mp48 == 0) {
	  kprint("Primary IDE, Master Drive (Drive 1): Online\n");
	} else {
	  kprint("Primary IDE, Master Drive (Drive 1): Offline\n");
	}
	if (hdd.ms == 0 || hdd.ms48 == 0) {
	  kprint("Primary IDE, Slave Drive (Drive 2): Online\n");
	} else {
	  kprint("Primary IDE, Slave Drive (Drive 2): Offline\n");
	}
	if (hdd.sp == 0 || hdd.sp48 == 0) {
	  kprint("Secondary IDE, Master Drive (Drive 3): Online\n");
	} else {
	  kprint("Secondary IDE, Master Drive (Drive 3): Offline\n");
	}
	if (hdd.ss == 0 || hdd.ss48 == 0) {
	  kprint("Secondary IDE, Slave Drive (Drive 4): Online\n");
	} else {
	  kprint("Secondary IDE, Slave Drive (Drive 4): Offline\n");
	}
  } else if (strcmp(input, "read") == 0) {
	read_disk(0);
  } else if (strcmp(input, "driveTest") == 0) {
	writeIn[0] = 0x1111;
	write(0, 0);
  } else {
	if (strcmp(input, "") == 0) {

	} else {
	  kprint("Unrecognized command: ");
	  kprint(input);
	}
  }
  kprint("\nuser@flameOS # ");
}