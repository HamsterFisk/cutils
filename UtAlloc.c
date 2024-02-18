#include "UtAlloc.h"
#include "UtMem.c"

void *AllocStub(void *_, usize __) {
    return NULL;
}
void FreeStub(void *_, void *__, usize ___) {

}

void *Alloc(AL *allocator, usize size) {
    return allocator->alloc(allocator->data, size);
}

void Free(AL *allocator, void *memStart, usize size) {
    allocator->free(allocator->data, memStart, size);
}

#ifdef _Win32
void * Win32Alloc(void *_, usize size) {
    return VirtualAlloc(0, size, MEM_COMMIT, PAGE_READWRITE);
}
void Win32Free(void *_, void *mem, usize __) {
    VirtualFree(mem, 0, MEM_RELEASE);
}

AL AlMakeWin32Alloc() {
    AL al = {0};
    al.alloc = Win32Alloc;
    al.free = Win32Free;
    al.data = NULL;

    return al;
}
#endif

void *ScratchBufferAlloc(void *data, usize size) {
    ScratchBuffer *sb = (ScratchBuffer *)data;
    if (sb->ap + size >= sb->cap) {
        sb->ap = 0;
    }

    sb->ap += size;

    return sb->mem + sb->ap - size;
}

AL AlMakeScratchBuffer(AL *allocator, usize capacity) {
    u8 *alData = Alloc(allocator, capacity + sizeof(ScratchBuffer));
    AL al = {0};

    if (NULL == alData) {
        return al;
    }

    ScratchBuffer *sb = (ScratchBuffer *)alData;
    sb->cap = capacity;
    sb->ap = 0;
    sb->mem = alData + sizeof(ScratchBuffer);
    sb->alloc = allocator;
    
    ZeroMem(sb->mem, capacity);

    al.alloc = ScratchBufferAlloc;
    al.free = FreeStub;
    al.data = alData;

    return al;
}

AL AlMakeScratchBufferRaw(void *data, usize capacity) {
    AL al = {0};

    ScratchBuffer *sb = (ScratchBuffer *)data;
    sb->cap = capacity;
    sb->ap = 0;
    sb->mem = (u8 *)data + sizeof(ScratchBuffer);
    sb->alloc = NULL;
    
    ZeroMem(sb->mem, capacity);

    al.alloc = ScratchBufferAlloc;
    al.free = FreeStub;
    al.data = data;

    return al;
}
