//
// Created by Jesse on 10/30/2020.
//

#ifndef UNTITLED_SOUND_H
#define UNTITLED_SOUND_H


typedef struct sound_t {
    int length;
    float rate;
    float * samples;
} sound;

typedef struct wave_t{
    char name[255];
    char type[255];
    float delay;
    float attenuation;
} wave;

typedef struct wsound_t{
    char name[255];
    wave * waves;
    float * mix;
    int waveCount;
} wsound;

typedef struct note_t{
    char sound[255];
    int key;
    float time;
    float duration;
} note;

#endif //UNTITLED_SOUND_H
