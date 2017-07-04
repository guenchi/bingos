#ifndef __FRAME_H__
#define __FRAME_H__

#include "multiboot.h"

typedef struct {
    unsigned int present : 1;
    unsigned int rw : 1;
    unsigned int user : 1;
    unsigned int write_through : 1;
    unsigned int cache_disabled : 1;
    unsigned int accessed : 1;
    unsigned int size : 1;
    unsigned int unused : 5;
    unsigned int addr : 20;
} page_dir_entry_t;

typedef struct {
    unsigned int present : 1;
    unsigned int rw : 1;
    unsigned int user : 1;
    unsigned int write_through : 1;
    unsigned int cache_disabled : 1;
    unsigned int accessed : 1;
    unsigned int dirty : 1;
    unsigned int global : 1;
    unsigned int unused : 4;
    unsigned int addr : 20;
} page_tabl_entry_t;

typedef struct { page_dir_entry_t tabls[1024]; } page_dir_t;

typedef struct { page_tabl_entry_t pages[1024]; } page_tabl_t;

void frame_init(struct multiboot_info *mbi);

ptr_t get_physaddr(ptr_t virtualaddr);
#endif