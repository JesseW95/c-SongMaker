//
// Created by Jesse on 9/10/2020.
//

#ifndef UNTITLED_GENSND_H
#define UNTITLED_GENSND_H
#include "sound.h"

sound * genSilence(float sample_rate, float duration);

//sound generation
sound * gensine(float hertz, float sample_rate, float duration);
sound * genSquare( float hertz, float sample_rate, float duration);
sound * genTriangle( float hertz, float sample_rate, float duration);
sound * genSawtooth( float hertz, float sample_rate, float duration);

//for reading through file and storing a struct holding sound information
wave * readWave(FILE * name);
wsound * readSound(FILE * name, wave * waves);
note * readSong(FILE *file);

sound * writeSong(note * notes, wsound * sounds,float songLength, int sampleRate, int soundSize);

sound * genDTMF(char key, float sample_rate, float duration);
int outputSound( sound *s, FILE *f);

#endif //UNTITLED_GENSND_H
