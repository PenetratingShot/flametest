/*
                pmm.c
                Copyright Shreyas Lad (PenetratingShot) 2020

                Physical Memory Manager
*/

#include <mm/pmm.h>

uint64_t* bitmap = (uint64_t*)&__kernel_end;

uint64_t totalmem;
uint64_t bitmapEntries;

/*********************
 * Public Memory API *
 *********************/
void memcpy(uint8_t* source, uint8_t* dest, uint32_t nbytes) {
  for (uint32_t i = 0; i < nbytes; i++) {
    *(dest + i) = *(source + i);
  }
}

void memset(void* dest, int val, size_t len) {
  for (uint8_t* temp = dest; len--;)
    *temp++ = val;
}

/*******************
 * Private PMM API *
 *******************/

/* Initialization */
void initMem(multiboot_info_t* mbd) {
  totalmem = (uint64_t)mbd->mem_upper;
  bitmapEntries = (uint64_t)(((totalmem * 1000) / PAGESIZE) /
                             8); // calculate the maximum amount of entries
                                 // possible in the bitmap to not overflow

  memset(bitmap, 0, (totalmem * 1000) / PAGESIZE / 8);
}

void* pmalloc(size_t pages) {
  uint64_t firstBit = 0;
  uint64_t concurrentBits = 0;
  uint64_t bitsToAlloc = pages + 1;

  for (uint64_t i = 0; i < bitmapEntries * 64; i++) {
    if (getAbsoluteBitState(bitmap, i) == 0) {
      if (concurrentBits == 0) {
        firstBit = i;
      }

      concurrentBits++;

      if (bitsToAlloc == concurrentBits) {
        goto alloc;
      }
    } else {
      firstBit = 0;
      concurrentBits = 0;

      continue;
    }
  }

  return NULL;

alloc:
  // iterate over bits now that a block has been found
  for (uint64_t i = firstBit; i < bitsToAlloc; i++) {
    setAbsoluteBitState(bitmap, i);
  }

  return (void*)(firstBit * PAGESIZE);
}

void pmfree(void* ptr, size_t pages) {
  uint64_t absoluteStartBit = (uint64_t)ptr / PAGESIZE;
  for (uint64_t i = absoluteStartBit; i < pages; i++) {
    setAbsoluteBitState(bitmap, i);
  }
}