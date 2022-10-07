#include "minicrt.h"

typedef struct _heap_header {
    enum {
        HEAP_BLOCK_FREE = 0xABABABAB,  // magic number of free block
        HEAP_BLOCK_USED = 0xCDCDCDCD,  // magic number of used block
    } type;
    // size include header size
    // "unsigned" is shorthand for "unsigned int"
    unsigned size;
    struct _heap_header *next;
    struct _heap_header *prev;
} heap_header;

#define ADDR_ADD(a,o) (((char *)(a)) + (o))
#define HEADER_SIZE (sizeof(heap_header))

static heap_header *list_head = NULL;

void free(void *ptr) {
    heap_header* header = (heap_header*)ADDR_ADD(ptr, -HEADER_SIZE);
    if(header->type != HEAP_BLOCK_USED)
        return;
    heap_header* header_next = header->next;
    if(header_next != NULL && header_next->type == HEAP_BLOCK_FREE) {
        header->size += header_next->size;
        header->next = header_next->next;
        if(header_next->next != NULL)
            header_next->next->prev = header;
    }
    heap_header* header_prev = header->prev;
    if(header_prev != NULL && header_prev->type == HEAP_BLOCK_FREE) {
        header_prev->size += header->size;
        header_prev->next = header->next;
        if(header->next != NULL)
            header->next->prev = header_prev;
    }
}

void* malloc(unsigned size) {
    if(size == 0)
        return NULL;
    heap_header* p = list_head;
    while(p != NULL) {
        if(p->type == HEAP_BLOCK_FREE && p->size-HEADER_SIZE >= size) {
            if (p->size - size >= 3 * HEADER_SIZE) {
                // split space
                heap_header* new_header = (heap_header *)ADDR_ADD(p, HEADER_SIZE+size);
                new_header->type = HEAP_BLOCK_FREE;
                new_header->size = p->size - size - HEADER_SIZE;
                new_header->prev = p;
                new_header->next = p->next;
                p->size = size + HEADER_SIZE;
                p->next = new_header;
            }
            p->type = HEAP_BLOCK_USED;
            return ADDR_ADD(p, HEADER_SIZE);
        }
        p = p->next;
    }
    return NULL;
}

static long brk(void* end_data_segment) {
    // brk syscall number is 12
    // parameter is boundery address want to set, return value is the actually address been set
    //
    // it is different from unistd.h's brk()
    // I can't find the document about syscall brk(if you find please tell me)
    // The only message I find is source code:
    // https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/tree/mm/mmap.c
    //
    asm("syscall \n\t"
        ::"a"(12), "D"(end_data_segment));
    // syscall return to rax, which is conform to the calling convention
    // so no need to write function return statement
}

int mini_crt_heap_init() {
    // 32MB heap size, include head size
    unsigned long heap_size = 32*1024*1024;
    void *base = (void*)brk(0);
    void* end = ADDR_ADD(base, heap_size);
    end = (void*)brk(end);
    if(!end)
        return 0;
    list_head = (heap_header*)base;
    list_head->size = heap_size;
    list_head->type = HEAP_BLOCK_FREE;
    list_head->next = NULL;
    list_head->prev = NULL;
    return 1;
}
