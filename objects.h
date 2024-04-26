#ifndef _OBJECTS
#define _OBJECTS

#include <gtk/gtk.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "engine.h"

extern GtkWidget* window;
extern GtkWidget *grid;
extern GtkWidget *gridArrows;
extern bool arrowsAdded;
extern GtkWidget *button6;
extern GtkWidget *box;
extern GtkWidget *menuGrid;
extern GtkWidget *upButton,*leftButton, *rightButton,*downButton;
extern GtkWidget *endGrid;
extern GtkWidget *scoreGrid;



extern int posX, posY;
extern int mapLength, mapWidth;
extern int setAlready;
extern int dstn;
extern GtkWidget *buttonTab[20][20];
extern GtkWidget *bestScoreButtons[8][4];

extern char map[][20];
extern int mapNumber;
extern char playerOnDst;
extern int moves;
extern bool gameOn,congratulationAdded;
extern int bestScore[8][3];
extern bool randomOn;
extern bool bestScoreadded;




void startGame();
void buttonSetName(GtkWidget **button, char digital);
void loadMapFromFile();
void printMap();
void clearMap();
void menuMode();
void mapMode();
void restartGame();
void load_css(void);
void generateRandomMap();
void initMapInformation();
void printrandomMap();
void endOfGame();
void readBestResults();
void printBestResult();
void saveBestResults();
void printrandomMap();
void saveRandomMap();





#endif // _OBJECTS
