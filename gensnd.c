//
// Created by Jesse on 9/10/2020.
//

#include <math.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "gensnd.h"
#include <string.h>

#define pi 3.14159265
float tPi = pi * 2;

//Sound generation

sound *gensine(float hertz, float sample_rate, float duration) {
    int length = sample_rate * duration;
    //memory is allocated to do stuff
    sound *ptr = malloc(sizeof(sound));
    ptr->samples = malloc(length * sizeof(float));
    ptr->rate = sample_rate;
    ptr->length = length;

    for (int i = 0; i < length; i++) {
        //we find how many ticks there are by dividing sampling rate
        //by frequency of samples taken.
        float ticks = sample_rate / hertz;
        //we find the currently cycle by dividing by the ticks.
        float cycles = (float) i / ticks;
        //current position on the wave
        float radi = tPi * cycles;
        radi = sinf(radi);
        //pass into sin function to normalize between -1 and 1
        //giving the wave result.
        //Using radi because it is already allocated in memory.
        (ptr->samples[i]) = radi;
    }
    return ptr;
}

sound *genSawtooth(float hertz, float sample_rate, float duration) {
    int length = sample_rate * duration;
    //memory is allocated to do stuff
    sound *ptr = malloc(sizeof(sound));
    ptr->samples = malloc(length * sizeof(float));
    ptr->rate = sample_rate;
    ptr->length = length;
    float radi = 0;

    for (int i = 0; i < length; i++) {

        ptr->samples[i] = radi / tPi * 2 - 1;
        //we find how many ticks there are by dividing sampling rate
        //by frequency of samples taken.
        float ticks = sample_rate / hertz;

        radi += tPi / ticks;
        //pass into sin function to normalize between -1 and 1
        //giving the wave result.
        //Using radi because it is already allocated in memory.
        while (radi >= tPi)
            radi -= tPi;
    }
    return ptr;
}

sound *genSquare(float hertz, float sample_rate, float duration) {
    int length = sample_rate * duration;
    //memory is allocated to do stuff
    sound *ptr = malloc(sizeof(sound));
    ptr->samples = malloc(length * sizeof(float));
    ptr->rate = sample_rate;
    ptr->length = length;
    int count = 0;
    float radi = 0;
    for (int i = 0; i < length; i++) {
        if (count % 2 == 0) ptr->samples[i] = -1;
        else ptr->samples[i] = 1;

        //we find how many ticks there are by dividing sampling rate
        //by frequency of samples taken.
        float ticks = sample_rate / hertz;

        radi += tPi / ticks;
        if (radi >= pi) {
            count++;
        }
        while (radi >= pi) {
            radi -= pi;
        }
    }
    return ptr;
}

sound *genTriangle(float hertz, float sample_rate, float duration) {
    int length = sample_rate * duration;
    //memory is allocated to do stuff
    sound *ptr = malloc(sizeof(sound));
    ptr->samples = malloc(length * sizeof(float));
    ptr->rate = sample_rate;
    ptr->length = length;
    int count = 0;
    float radi = 0;
    for (int i = 0; i < length; i++) {
        if (count % 2 == 0) ptr->samples[i] = -1 + radi / tPi;
        else ptr->samples[i] = 1 - radi / tPi;

        //we find how many ticks there are by dividing sampling rate
        //by frequency of samples taken.
        float ticks = sample_rate / hertz;
        //current position on the wave
        radi += tPi / ticks;
        if (radi >= pi) {
            count++;
        }
        while (radi >= pi) {
            radi -= pi;
        }
    }
    return ptr;
}

sound *genDTMF(char key, float sample_rate, float duration) {
    int length = sample_rate * duration;
    sound *ptr = malloc(sizeof(sound));

    sound *ptr2 = malloc(sizeof(sound));

    sound *ret = malloc(sizeof(sound));
    ret->samples = malloc(length * sizeof(float));
    ret->length = length;
    ret->rate = 8000;
    //switch case for selecting what tones to combine.
    switch (putchar(tolower(key))) {
        case '0':
            ptr = gensine(941, 8000, 0.5f);
            ptr2 = gensine(1336, 8000, 0.5f);
            break;
        case '1':
            ptr = gensine(697, 8000, 0.5f);
            ptr2 = gensine(1209, 8000, 0.5f);
            break;
        case '2':
            ptr = gensine(697, 8000, 0.5f);
            ptr2 = gensine(1336, 8000, 0.5f);
            break;
        case '3':
            ptr = gensine(697, 8000, 0.5f);
            ptr2 = gensine(1447, 8000, 0.5f);
            break;
        case '4':
            ptr = gensine(770, 8000, 0.5f);
            ptr2 = gensine(1209, 8000, 0.5f);
            break;
        case '5':
            ptr = gensine(770, 8000, 0.5f);
            ptr2 = gensine(1336, 8000, 0.5f);
            break;
        case '6':
            ptr = gensine(770, 8000, 0.5f);
            ptr2 = gensine(1477, 8000, 0.5f);
            break;
        case '7':
            ptr = gensine(852, 8000, 0.5f);
            ptr2 = gensine(1209, 8000, 0.5f);
            break;
        case '8':
            ptr = gensine(852, 8000, 0.5f);
            ptr2 = gensine(1336, 8000, 0.5f);
            break;
        case '9':
            ptr = gensine(852, 8000, 0.5f);
            ptr2 = gensine(1477, 8000, 0.5f);
            break;
        case '*':
            ptr = gensine(941, 8000, 0.5f);
            ptr2 = gensine(1209, 8000, 0.5f);
            break;
        case '#':
            ptr = gensine(941, 8000, 0.5f);
            ptr2 = gensine(1477, 8000, 0.5f);
            break;
        case 'a':
            ptr = gensine(697, 8000, 0.5f);
            ptr2 = gensine(1633, 8000, 0.5f);
            break;
        case 'b':
            ptr = gensine(770, 8000, 0.5f);
            ptr2 = gensine(1633, 8000, 0.5f);
            break;
        case 'c':
            ptr = gensine(852, 8000, 0.5f);
            ptr2 = gensine(1633, 8000, 0.5f);
            break;
        case 'd':
            ptr = gensine(941, 8000, 0.5f);
            ptr2 = gensine(1633, 8000, 0.5f);
            break;
        default:
            ptr = genSilence(8000, 0.25f);
            ptr2 = genSilence(8000, 0.25f);
            break;
    }

    //loop combines the tones and averages them.
    for (int i = 0; i < length; i++) {
        ret->samples[i] = (ptr->samples[i] + ptr2->samples[i]) / 2;
    }
    free(ptr);
    free(ptr2);
    return ret;
}

sound *genSilence(float sample_rate, float duration) {
    int length = sample_rate * duration;
    sound *psilence = malloc(sizeof(sound));
    psilence->samples = malloc(length * sizeof(float));
    psilence->rate = sample_rate;
    psilence->length = length;
    for (int i = 0; i < length; i++) {
        //since there's no sound we just output 0 for the duration
        psilence->samples[i] = 0.00f;
    }
    return psilence;
}

int outputSound(sound *s, FILE *f) {
    for (int i = 0; i < s->length; i++) {
        fprintf(f, "%f\n", s->samples[i]);
    }
    return 0;
}


//helper functions
wave *readWave(FILE *file) {
    wave * wv = malloc(sizeof (wave));
    char tmp[255];
    for (int i = 0; i < 3; i++) {
        char *ptr;
        fgets(tmp, sizeof tmp, file);
        ptr = strtok(tmp, "\n");
            switch(i){
                case 0:
                    strcpy(wv->name, ptr);
                    break;
                case 1:
                    strcpy(wv->type, ptr);
                    break;
                case 2:
                    ptr = strtok(tmp, " ");
                    wv->delay = atof(ptr);
                    ptr = strtok(NULL, " ");
                    wv->attenuation = atof(ptr);
                    break;
                default:
                    break;
            }
    }
    return wv;
}

wsound * readSound(FILE *file, wave * waves) {
    wsound * ws = malloc(sizeof (wsound));
    char tmp[255];
    int c = 0;
    int numWaves  = 0;
    int filePos = ftell(file);
    while(strcmp(tmp, "SOUND\r\n") != 0) {
        char *ptr;
        fgets(tmp, sizeof tmp, file);
        ptr = strtok(tmp, "\n");
        if(strcmp(ptr, "\r") == 0 ) {
            numWaves++;
            break;
        }
    }
    numWaves--;

    ws->mix = malloc(numWaves * sizeof(float));
    ws->waves = malloc(numWaves * sizeof(wave));

    fseek(file, filePos, 0);

    while(strcmp(tmp, "SOUND\r\n") != 0) {
        char *ptr;
        fgets(tmp, sizeof tmp, file);
        ptr = strtok(tmp, "\n");
        if(strcmp(ptr, "\r") == 0 ) {
            filePos = ftell(file);
            break;
        }
        if(c == 0) {
            strcpy(ws->name, ptr);
            fgets(tmp, sizeof tmp, file);
        }
                ptr = strtok(tmp, " ");
                if(strcmp(waves->name, ptr)){
                    memcpy(ws->waves, waves, sizeof(wave));
                    ptr = strtok(NULL, " ");
                    *ws->mix = atof(ptr);

                    ws->waves += 1;
                    ws->mix += 1;
                }
                waves = waves+1;
            c++;
        ptr = strtok(NULL, "\n");
    }
    ws->waveCount = c;
    ws->waves -= ws->waveCount;
    ws->mix -= ws->waveCount;
    fseek(file, filePos, 0);
    return ws;
}

note * readSong(FILE *file) {
    note * rnote = malloc(sizeof (note));
    char tmp[255];
    char *ptr;
    fgets(tmp, sizeof tmp, file);
    ptr = strtok(tmp, "\n");
    int soundIndex = 0;
    ptr = strtok(tmp, " ");
    memcpy(rnote->sound, ptr, sizeof(wsound));

    ptr = strtok(NULL, " ");
    rnote->key = atoi(ptr);

    ptr = strtok(NULL, " ");
    rnote->time = atof(ptr);

    ptr = strtok(NULL, " ");
    rnote->duration = atof(ptr);

    ptr = strtok(NULL, "\n");
    return rnote;
}

//file = file to write to
//notes = array of notes
//songLength = notes furthest start + length
//sampleRate = sample rate read from file
sound * writeSong(note * notes, wsound * sounds, float songLength, int sampleRate, int soundSize){
    int length = songLength * sampleRate;
    sound * songNotes = malloc(length * sizeof(sound));
    //initialize all samples to 0 to account for silence
    for(int i = 0; i < length; i++){
        songNotes->samples = 0;
    }

    for(int i = 0; i < soundSize; i++){
        printf("%d \n",strcmp(notes->sound, sounds->name));
        int soundCounter = 0;
        while(strcmp(notes->sound, sounds->name) != -13){
            if(soundCounter > soundSize){
                break;
            }
            sounds++;
            soundCounter++;
        }
        for(int j =0; j< sounds->waveCount; j++){
            
        }

        notes++;
        soundCounter = 0;

    }

}