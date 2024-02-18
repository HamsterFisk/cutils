#ifndef UT_ALLOC_H
#define UT_ALLOC_H

#include "UtTypes.h"

typedef void *(*ALP)(void *, usize);
typedef void(*DALP)(void *, void *,  usize);

void *AllocStub(void *_, usize __);
void FreeStub(void *_, void *__, usize ___);

typedef struct AL {
    ALP alloc;
    DALP free;
    void *data;
} AL;

void *Alloc(AL *allocator, usize size);
void Free(AL *allocator, void *memStart, usize size);

#ifdef _WIN32
void * Win32Alloc(void *_, usize size);
void Win32Free(void *_, void *mem, usize __);
AL AlMakeWin32Alloc();
#endif

typedef struct {
    usize ap;
    usize cap;
    u8 *mem;
    AL *alloc;
} ScratchBuffer;

void *ScratchBufferAlloc(void *data, usize size);

AL AlMakeScratchBuffer(AL *allocator, usize capacity);
AL AlMakeScratchBufferRaw(void *data, usize capacity);

typedef struct {
    usize ap;
    usize cap;
    u8 *mem;
    AL *alloc;
} MemoryArena;

void *ArenaAlloc(void *data, usize size);

AL AlMakeArena(AL *allocator, usize capacity);

#endif
