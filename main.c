//
// Created by Jesse on 9/10/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <assert.h>
#include <stdbool.h>
#include "gensnd.h"
#include "process.h"

int main(int argc, char* argv[]) {
    if(argc < 2){
        printf("This application requires 2 arguments \n"
               "(Example 1) playsong testsong.txt mysong.txt \t||this will output to a txt file named mysong.\n");
    }

    char str[255];
    FILE *fp;
    fp = fopen(argv[1] , "r");
    //if there was a problem opening file we throw an error and return -1
    if(fp == NULL) {
        perror("Error opening file");
        return(-1);
    }

    //initiate counters to keep track of how large the respective
    //struct pointers are
    int lineCount = 0;
    int numWaves = 0;
    int numSounds = 0;
    int songSize = 0;
    int sampleRate = 0;
    float songLength = 0.00f;
    //read through entire file so we can
    while(fgets(str, sizeof str, fp) !=NULL){
        char * ptr;
        ptr = strtok(str, "\n");
        strcpy(str, ptr);
        ptr = strtok(NULL, "\n");

        //we can set the sample rate on the first pass because it doesn't need
        //extra iteration to get more info beyond the one line
        if(strcmp(str, "SAMPLERATE\n") == 3) {
            fgets(str, sizeof str, fp);
            ptr = strtok(str, "\n");
            sampleRate = atoi(ptr);
            ptr = strtok(NULL, "\n");
        }

        //if line is WAVE increase number of waves by 1
        if(strcmp(str, "WAVE\n") == 3) {
            numWaves++;
        }
        //if line is SOUND increase number of sounds by 1
        if(strcmp(str, "SOUND\n") == 3) {
            numSounds++;
        }

        //If line is SOUND we read through all the remaining lines, ignoring
        //new lines and returns and incrementing by 1
        if(strcmp(str, "SONG\n") == 3) {
            while(fgets(str, sizeof str, fp) !=NULL){
                ptr = strtok(str, "\n");
                if(strcmp(ptr, "\n") != 3){
                    songSize++;
                }
                ptr = strtok(NULL, "\n");
            }
        }
        lineCount++;
    }


    //rewind file to beginning
    rewind(fp);
    //using information from first iteration we
    //can intialize the pointers with correct memory size
    wave * waveList = calloc(numWaves, sizeof(wave));
    wsound * waveSoundList = calloc(numSounds, sizeof(wsound));
    note * notes = calloc(songSize, sizeof(note));

    //read through file again
    while(fgets(str, sizeof str, fp) !=NULL){
        //keep track of current cursor position in file
        int curPos = ftell(fp);
        char * ptr;
        ptr = strtok(str, "\n");
        strcpy(str, ptr);

        //if line is WAVE read through file until we encounter a line named SOUND
        if(strcmp(str, "WAVE\n") == 3) {
            int waveIndex = 0;
            bool resetCursor = false;
            while(fgets(str, sizeof str, fp) !=NULL){
                if(resetCursor == false){
                    fseek(fp, curPos, 0);
                    resetCursor = true;
                }else{
                    fgets(str, sizeof str, fp);
                }

                if(strcmp(ptr, "SOUND\r\n") ==0)break;
                //this is for the second iteration through file when adding all the
                //waves to an array.
                wave * wv = readWave(fp);
                *(waveList+waveIndex) = *wv;
                waveIndex++;
            }
            for(int i = 0; i < numWaves; i++){
                waveList = (waveList+i);

            }
            waveList -= numWaves-1;
            curPos = ftell(fp);
        }
        if(strcmp(str, "SOUND\n") == 3) {
            printf("Sound section\n");
            //this is for the second iteration through file when adding all the
            //sounds to an array.
            int soundIndex = 0;
            bool resetCursor = false;
            while(fgets(str, sizeof str, fp) !=NULL){
                //reset cursor pos to right before we read the first while loop
                if(resetCursor == false){
                    fseek(fp, curPos, 0);
                    resetCursor = true;
                }

                //if we are at the song section exit while loop
                if(strcmp(ptr, "SONG\r\n") ==0)break;
                //iterate through sound section of the file
                //using readSound function to add new pointer to array
                    wsound * ws = readSound(fp, waveList);
                    *(waveSoundList+soundIndex) = *ws;
                    soundIndex++;

            }

            curPos = ftell(fp);
        }

        if(strcmp(str, "SONG\n") == 3) {
            fseek(fp, curPos, 0);
            int noteCounter = 0;
            while(fgets(str, sizeof str, fp) !=NULL){
                ptr = strtok(str, "\n");
                //iterate through the song section of the file, skipping line returns
                //write these to the notes pointer
                if(strcmp(ptr, "\n") != 3){
                    *(notes+noteCounter) = *readSong(fp);
                    noteCounter++;
                }

                ptr = strtok(NULL, "\n");
            }
            notes -= numSounds-2;
            for(int i = 0; i < songSize; i++){
                float tmpTime = notes->time + notes->duration;
                if(tmpTime > songLength){
                    songLength = tmpTime;
                }
                notes+=1;
            }
            notes -= songSize;
        }
        ptr = strtok(NULL, "\n");
        lineCount++;

    }
    fclose(fp);

    //Create a new file to write the song to.
    FILE * fo;
    fo = fopen(argv[2], "w+");
    sound * song = writeSong(notes, waveSoundList,songLength, sampleRate, numSounds);
    outputSound(song, fo);
    fclose(fo);
    return 0;
}
//while(fgets(str, sizeof str, fp) !=NULL){
//int sndWaves = 0;
//if(strcmp(ptr, "\n") == 3) break;
//}
