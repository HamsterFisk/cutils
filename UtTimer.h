#ifndef UT_TIMER_H
#define UT_TIMER_H

#include "UtTypes.h"

typedef struct UTimer {
    BOOL active;
    f64 trigger;
    f64 count;
} UTimer;

UTimer MkUTimer(f64 trigger, BOOL startActive);

void UTimerRest(UTimer *t);
BOOL UTimerCheckTrigger(UTimer *t, BOOL resetOnTrigger);

void UTimerTick(UTimer *t, usize tCount, f64 time);

#endif
