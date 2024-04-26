#include "engine.h"
#include "objects.h"




char playerOnDst=' ';

void move2(int R,int UP){
      if(map[posY+UP][posX+R]!='#'){
            if(map[posY+UP][posX+R]==' '||map[posY+UP][posX+R]=='D'){
                map[posY][posX]=playerOnDst;
                buttonSetName(&buttonTab[posY][posX],playerOnDst);
                posY+=UP;posX+=R;
                if(map[posY][posX]=='D')
                    playerOnDst='D';
                else
                    playerOnDst=' ';
                map[posY][posX]='P';
                buttonSetName(&buttonTab[posY][posX],'P');


            }else if(map[posY+UP][posX+R]=='S'){
                if(map[posY+2*UP][posX+2*R]!='#'&&map[posY+2*UP][posX+2*R]!='S'&&map[posY+2*UP][posX+2*R]!='C'){
                    map[posY][posX]=playerOnDst;
                    buttonSetName(&buttonTab[posY][posX],playerOnDst);
                    posY+=UP;posX+=R;
                    buttonSetName(&buttonTab[posY][posX],'P');
                    playerOnDst='D';

                    setAlready--;
                    if(map[posY+UP][posX+R]=='D'){
                        map[posY+UP][posX+R]='S';
                        buttonSetName(&buttonTab[posY+UP][posX+R],'S');
                        setAlready++;
                    }
                    else{
                        map[posY+UP][posX+R]='C';
                        buttonSetName(&buttonTab[posY+UP][posX+R],'C');

                    }
                }

            }else if(map[posY+2*UP][posX+2*R]==' '||map[posY+2*UP][posX+2*R]=='D'){
                    map[posY][posX]=playerOnDst;
                    buttonSetName(&buttonTab[posY][posX],playerOnDst);

                    posY+=UP;posX+=R;
                   if(map[posY][posX]=='D')
                        playerOnDst='D';
                    else
                        playerOnDst=' ';
                    map[posY][posX]='P';
                    buttonSetName(&buttonTab[posY][posX],'P');


                    if(map[posY+UP][posX+R]=='D'){
                        setAlready++;
                        map[posY+UP][posX+R]='S';
                        buttonSetName(&buttonTab[posY+UP][posX+R],'S');

                    }
                    else{
                        map[posY+UP][posX+R]='C';
                        buttonSetName(&buttonTab[posY+UP][posX+R],'C');
                    }

                    }
        }
        moves++;
    if(setAlready==dstn){
        endOfGame();
    }
}
void moveUp(){
    move2(0,-1);
    //printMapConsole();
    }
void moveLeft(){
    move2(-1,0);
    }
void moveRight(){
    move2(1,0);
    }
void moveDown(){
    move2(0,1);
    }


