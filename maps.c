#include "maps.h"
struct mapInfo maps[3];
char map2[20][20];



void initMap1(){
    maps[0].length=10;
    maps[0].width=12;
    maps[0].posX=8;
    maps[0].posY=4;
    maps[0].dstn=3;
    maps[0].setAlready=0;
    maps[0].playerOnDst=' ';

}

void initMap2(){
    maps[1].length=10;
    maps[1].width=12;
    maps[1].posX=8;
    maps[1].posY=4;
    maps[1].dstn=3;
    maps[1].setAlready=0;
    maps[1].playerOnDst=' ';
}
