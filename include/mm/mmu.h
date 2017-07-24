#ifndef __MMU_H__
#define __MMU_H__

#include "hal/isr.h"

#define PAGE_SIZE (4096)

#define PAGE_TABLE_INDEX(x) ((x) >> 12) & 0x03ff
#define PAGE_DIRECTORY_INDEX(x) (((x) >> 22) & 0x3ff)

/* Read CR0 */
static inline uint32_t x86_read_cr0() {
    uint32_t r;

    asm volatile("mov %%cr0, %0" : "=r"(r));
    return r;
}

/* Write CR0 */
static inline void x86_write_cr0(uint32_t val) { asm volatile("mov %0, %%cr0" ::"r"(val)); }

/* Write CR3 */
static inline void x86_write_cr3(uint32_t val) { asm volatile("mov %0, %%cr3" ::"r"(val)); }

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
} __attribute__((packed)) paged_entry_t;

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
} __attribute__((packed)) page_t;

enum PAGE_PDE_FLAGS {
    I86_PDE_PRESENT = 1,
    I86_PDE_WRITABLE = 2,
    I86_PDE_FRAME = 0x7FFFF000,
};

typedef struct { page_t pages[1024]; } page_tabl_t;

typedef struct {
    page_tabl_t* tabls[1024];     // virtual page table address
    paged_entry_t entries[1024];  // page table entry used by cr3
} page_dir_t;

void page_init();

void page_fault(registers_t regs);

page_t* get_page(uint32_t virt, int make, uint32_t flags);

void page_map(page_t* page, int kernel, int rw);
void page_identical_map(page_t* page, int kernel, int rw, uint32_t virt);
void page_unmap(page_t* page);
#endif