//
// Created by Jesse on 10/30/2020.
//
#include "iosnd.h"

int outputSound(sound *s, FILE *f){
    int length = s->length * s->rate;
    for(int i = 0; i< length; i++){
        fprintf(f, "%f\n", *s->samples);
        s->samples++;
    }
return 0;
}