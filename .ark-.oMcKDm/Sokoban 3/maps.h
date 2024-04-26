#ifndef MAPS_H_INCLUDED
#define MAPS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

 struct mapInfo{
    int length,width;
    int posX,posY;
    int dstn;//number of chests and destinations
    int setAlready;
    char playerOnDst;
    char map[10][12];
};

extern struct mapInfo maps[3];
//extern char map[][20];
extern char map2[][20];

void initMap1();
void initMap2();
void initMapInformation();
void generateRandomMap(int length, int width, int mapdst,int posX, int posY);
void printMapConsole(int length, int width, char map[length][width]);









#endif // MAPS_H_INCLUDED
