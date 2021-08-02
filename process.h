//
// Created by Jesse on 10/31/2020.
//

#ifndef UNTITLED_PROCESS_H
#define UNTITLED_PROCESS_H

#include "sound.h"

sound* mix(sound *s[], float w[], int c);
sound* modulate(sound *s1, sound *s2);
sound* filter(sound *s, float fir[], int c);
sound* reverb(sound *s, float delay, float attenuation);
sound* echo(sound *s, float delay, float attenuation);

#endif //UNTITLED_PROCESS_H
