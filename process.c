//
// Created by Jesse on 10/31/2020.
//
#include <stdlib.h>
#include <stdio.h>
#include "process.h"

sound* mix(sound *s[], float w[], int c){
    int totalLength = 0;
    float sampRate = 0;
    //this is for finding the longest sample size
    //so we can set the mix's length to that
    for(int i = 0; i < c; i++){
        if(s[i]->length > totalLength) {
            totalLength = s[i]->length;
            sampRate = s[i]->rate;
        }
    }

    //initialize a pointer to return with length = longest sample length
    //rate is set to largest sounds sample rate, just in case evne though it isnt used.
    sound * ptr = malloc(sizeof(sound));
    ptr->samples = malloc(totalLength * sizeof(float));
    ptr->rate = sampRate;
    ptr->length = totalLength;
    for(int i = 0; i < c; i++){
        //iterates all of the samples of s at current index i
        //adds them onto ptr samples at index j, so we don't need to
        //account for uneven array sizes throwing an out of bounds
        for(int j = 0; j < s[i]->length; i++){
            ptr->samples[j] += w[i] * s[i]->samples[j];
        }
    }

    return ptr;
}

sound* modulate(sound *s1, sound *s2){
    //if sound lengths aren't same return null
    if(s1->length != s2->length) return NULL;

    //initialize a return pointer with length = to s1's, we could also use s2
    //rate set to s1 just in case
    sound * ptr = malloc(sizeof(sound));
    ptr->samples = malloc(s1->length * sizeof(float));
    ptr->rate = s1->rate;
    ptr->length = s1->length;

    //iterate through s1 and s2 samples multiplying them together
    //and setting it at i
    for(int i = 0; i < ptr->length; i++){
        ptr->samples[i] = s1->samples[i] * s2->samples[i];
    }
    return ptr;
}

sound* filter(sound *s, float fir[], int c){
    sound * ptr = malloc(sizeof(sound));
    ptr->samples = malloc(s->length * sizeof(float));
    ptr->rate = s->rate;
    ptr->length = s->length;

    for(int i = 0; i < ptr->length; i++){
        for(int j = 0; j < c; j++){
            //only do stuff if sample exists at current index.
            if(i - j < 0){
                ptr->samples[i] = s->samples[i];
            }else{
                ptr->samples[i] += s->samples[i-j]*fir[j];
            }
        }
    }

    return ptr;
}

sound* reverb(sound *s, float delay, float attenuation){
    //sanity checks
    if(s == NULL){
        printf("Input sound is null");
        return NULL;
    }
    if(attenuation < 0.00f || attenuation > 1.00f){
        printf("Out of attenuation range (0 to 1)");
        return s;
    }
    if(delay < 0.00f || delay > 0.10f){
        printf("Out of delay range (0 to 0.1)");
        return s;
    }

    //delay loc is found from
    int delayLoc = (s->rate * delay)+1;
    float fir[delayLoc];
    //initialize all array values to 0, kept getting nan values for some reason
    for(int i = 0; i < delayLoc; i++){
        fir[i] = 0;
    }
    //set first element to 1
    fir[0] = 1;
    //set element at delays location
    fir[delayLoc-1] = attenuation;
    return filter(s, fir, delayLoc);
}

sound* echo(sound *s, float delay, float attenuation){
    //sanity checks
    if(s == NULL){
        printf("Input sound is null");
        return NULL;
    }
    if(attenuation < 0.00f || attenuation > 1.00f){
        printf("Out of attenuation range (0 to 1)");
        return s;
    }
    if(delay < 0.1f || delay > 1.00f){
        printf("Out of delay range (0.1 to 1)");
        return s;
    }

    //allocate memory for pointer and set its values = to s
    sound * ptr = malloc(sizeof(sound));
    ptr->samples = s->samples;
    ptr->rate = s->rate;
    ptr->length = s->length;

    int delayLoc = (int) (s->rate * delay) +1;
    float fir[delayLoc];
    //initialize all array values to 0, kept getting nan values for some reason
    for(int i = 0; i < delayLoc; i++){
        fir[i] = 0;
    }
    fir[delayLoc-1] = attenuation;
    for(int i = 0; i < ptr->length; i++){
        for(int j = 0; j < delayLoc; j++){
            //only do stuff if sample exists at current index.
            if(i - j < 0){
                ptr->samples[i] = s->samples[i];
            }else{
                ptr->samples[i] += s->samples[i-j]*fir[j];
            }
        }
    }
    return ptr;
}