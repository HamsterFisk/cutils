#include "UtTimer.h"

UTimer MkUTimer(f64 trigger, BOOL startActive) {
    UTimer t;
    t.count = 0.0;
    t.trigger = trigger;
    t.active = startActive;
    
    return t;
}

void UTimerRest(UTimer *t) {
    t->count = 0.0;
    t->active = 1;
}
BOOL UTimerCheckTrigger(UTimer *t, BOOL resetOnTrigger) {
    if (t->count >= t->trigger) {
        if (resetOnTrigger) {
            t->count = 0;
            t->active = 1;
        } else {
            t->active = 0;
        }

        return 1;
    }

    return 0;
}

void UTimerTick(UTimer *t, usize tCount, f64 time) {
    for (usize i = 0; i < tCount; i++) {
        t[i].count += time;
    }
}
