#include "objects.h"
#include <conio.h>
#include "engine.h"
#include <string.h>
#include <math.h>

GtkWidget *grid;
GtkWidget *gridArrows;
GtkWidget *upButton,*leftButton, *rightButton,*downButton;

int posX, posY;
int mapLength, mapWidth;
int dstn,moves;
int setAlready;
int bestScore[8][3];

GtkWidget *buttonTab[20][20];
GtkWidget *bestScoreButtons[8][4];
GtkWidget *congratulationsButton;
GtkWidget *prevBestButton;


char map[20][20];
bool bestScoreadded=false;


//function author: Michael B. https://www.youtube.com/watch?v=1LppFd7dTMI&list=PLN_MPJUQgPVpkVVSJ8qrzk65FHnUtO6BF&index=
void load_css(void){

    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;

    const gchar *css_style_file="style.css";
    GFile *css_fp = g_file_new_for_path(css_style_file);
    GError *error=0;

    provider = gtk_css_provider_new ();
    display = gdk_display_get_default ();
    screen = gdk_display_get_default_screen (display);

    //tylko te 2 komenty sa wazne
    gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION); //600
    gtk_css_provider_load_from_file(provider,css_fp, &error);

    g_object_unref (provider);
}

void buttonSetName(GtkWidget **button, char digital){
    if(digital==' ')
        gtk_widget_set_name(*button,"empty_square");
        else if(digital=='O')
            gtk_widget_set_name(*button,"out_of_map_square");
            else if(digital=='#')
                gtk_widget_set_name(*button,"border_square");
                else if(digital=='D')
                    gtk_widget_set_name(*button,"destination_square");
                    else if(digital=='C')
                        gtk_widget_set_name(*button,"chest_square");
                        else if(digital=='S')
                            gtk_widget_set_name(*button,"set_square");
                            else if(digital=='P')
                                gtk_widget_set_name(*button,"player_square");

}
void startGame(){
    clearMap();
    loadMapFromFile();
    printMap();
}
void menuMode(){
    gameOn=false;
    gtk_window_set_title(GTK_WINDOW(window),"Sokoban");
    gtk_widget_set_name(window,"Map_Menu");

    gtk_widget_set_size_request(window, 800, 480);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);  //okno wyswietli sie na srodku ekranu
    gtk_container_set_border_width(GTK_CONTAINER(window),10);
    gtk_widget_show_all(window);
   if(arrowsAdded)
        gtk_widget_hide(gridArrows);
    gtk_widget_hide(grid);
    gtk_widget_hide(endGrid);
    gtk_widget_hide(scoreGrid);



}
void mapMode(){
    if(randomOn)
        gtk_window_set_title(GTK_WINDOW(window),"RandomMap");
    else{
        char textTemp[6];
        itoa(mapNumber,textTemp,10);
        char text[50]="Map";
        strcat(text,textTemp);
        gtk_window_set_title(GTK_WINDOW(window),text);
    }

    gtk_widget_set_name(window, "Map_Window");
    gtk_widget_set_size_request(window, mapWidth*40, (mapLength+2)*40);
    gtk_container_set_border_width(GTK_CONTAINER(window),10);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);

    gtk_widget_show_all(window);
    gtk_widget_hide(menuGrid);
    gtk_widget_hide(endGrid);
    gtk_widget_hide(scoreGrid);
      if(bestScoreadded)
        gtk_widget_hide(scoreGrid);

}
void startNextMap(){
    if(mapNumber<8){
        mapNumber++;
        startGame();
    }
}
void endOfGame(){
    gameOn=false;
    gtk_widget_set_size_request(window, 400, 400);
    gtk_widget_set_name(window,"EndOfGame");
    if(!congratulationAdded){
        congratulationAdded=true;;
        congratulationsButton=gtk_button_new_with_label("a");
        gtk_widget_set_name(congratulationsButton,"end_Button");
        prevBestButton=gtk_button_new_with_label("");
        gtk_widget_set_name(prevBestButton,"end_Button");
        GtkWidget *menu,*leave, *next;
        menu=gtk_button_new_with_label("Menu"), next=gtk_button_new_with_label("Next Map"), leave=gtk_button_new_with_label("Leave");
        g_signal_connect (G_OBJECT (menu), "clicked",G_CALLBACK (menuMode), NULL);
        g_signal_connect (G_OBJECT (next), "clicked",G_CALLBACK (startNextMap), NULL);
        g_signal_connect (G_OBJECT (leave), "clicked",G_CALLBACK (gtk_main_quit), NULL);

        gtk_widget_set_name(menu,"end_Button");        gtk_widget_set_name(next,"end_Button");        gtk_widget_set_name(leave,"end_Button");
        gtk_grid_attach(GTK_GRID(endGrid),congratulationsButton,0,0,3,1);
        gtk_grid_attach(GTK_GRID(endGrid),prevBestButton,0,1,3,1);
        gtk_grid_attach(GTK_GRID(endGrid),leave,1,2,1,1);
        gtk_grid_attach(GTK_GRID(endGrid),next,2,2,1,1);
        gtk_grid_attach(GTK_GRID(endGrid),menu,0,2,1,1);
    }
    char text[]="Congratulation! You won in ";
    char movesSTR[4];
    itoa(moves,movesSTR,10);
    strcat(text,movesSTR);
    strcat(text," moves");
    gtk_button_set_label(GTK_BUTTON(congratulationsButton),text);


    char prevBest[4];
    itoa(bestScore[mapNumber-1][0],prevBest,10);
    if(moves<bestScore[mapNumber-1][0]||bestScore[mapNumber-1][0]==-1){
        if(bestScore[mapNumber-1][0]==-1){
           char text2[]="The map didn't have saved scores";
            gtk_button_set_label(GTK_BUTTON(prevBestButton),text2);
        }
        else{
            char text2[]="It's new highes score! Previous was ";
            strcat(text2,prevBest);
            strcat(text2," moves");
            gtk_button_set_label(GTK_BUTTON(prevBestButton),text2);
        }
        bestScore[mapNumber-1][2]=bestScore[mapNumber-1][1];
        bestScore[mapNumber-1][1]=bestScore[mapNumber-1][0];
        bestScore[mapNumber-1][0]=moves;
    }
    else{
        char text2[]="Best score on this map is ";
        strcat(text2,prevBest);
        strcat(text2," moves");
        gtk_button_set_label(GTK_BUTTON(prevBestButton),text2);
        if(moves<bestScore[mapNumber-1][1]||bestScore[mapNumber-1][1]==-1){
            bestScore[mapNumber-1][2]=bestScore[mapNumber-1][1];
            bestScore[mapNumber-1][1]=moves;
        }
            else if(moves<bestScore[mapNumber-1][2]||bestScore[mapNumber-1][2]==-1)
                bestScore[mapNumber-1][2]=moves;
    }
    gtk_widget_show_all(window);
    gtk_widget_hide(menuGrid);
    gtk_widget_hide(grid);
    gtk_widget_hide(gridArrows);
    if(bestScoreadded)
        gtk_widget_hide(scoreGrid);

    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);

}
void addArrows(){
    arrowsAdded=true;
    gridArrows=gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(gridArrows),6);
    gtk_grid_set_row_spacing(GTK_GRID(gridArrows),2);
    gtk_box_pack_start(GTK_BOX(box),gridArrows,TRUE,TRUE,0);

    GtkWidget *exitButton,*restartButton;
    upButton=gtk_button_new();leftButton=gtk_button_new();    rightButton=gtk_button_new();    downButton=gtk_button_new();
    gtk_widget_set_name(GTK_WIDGET(downButton),"down_Button");
    gtk_widget_set_name(GTK_WIDGET(upButton),"up_Button");
    gtk_widget_set_name(GTK_WIDGET(rightButton),"right_Button");
    gtk_widget_set_name(GTK_WIDGET(leftButton),"left_Button");
    exitButton = gtk_button_new();
    restartButton=gtk_button_new();
    gtk_widget_set_name(GTK_WIDGET(exitButton),"exit_Button");
    gtk_widget_set_name(GTK_WIDGET(restartButton),"restart_Button");


    gtk_grid_attach(GTK_GRID(gridArrows),upButton,1,0,1,1);
    gtk_grid_attach(GTK_GRID(gridArrows),restartButton,5,0,1,1);
    gtk_grid_attach(GTK_GRID(gridArrows),leftButton,0,1,1,1);
    gtk_grid_attach(GTK_GRID(gridArrows),downButton,1,1,1,1);
    gtk_grid_attach(GTK_GRID(gridArrows),rightButton,2,1,1,1);
    gtk_grid_attach(GTK_GRID(gridArrows),exitButton,5,1,1,1);

    g_signal_connect (G_OBJECT (restartButton), "clicked",G_CALLBACK (restartGame), NULL);
    g_signal_connect (G_OBJECT (exitButton), "clicked",G_CALLBACK (menuMode), NULL);
    g_signal_connect (G_OBJECT (upButton), "clicked",G_CALLBACK (moveUp),NULL);
    g_signal_connect (G_OBJECT (leftButton), "clicked",G_CALLBACK (moveLeft), NULL);
    g_signal_connect (G_OBJECT (downButton), "clicked",G_CALLBACK (moveDown), NULL);
    g_signal_connect (G_OBJECT (rightButton), "clicked",G_CALLBACK (moveRight), NULL);
}
void clearMap(){
    for(int i=0;i<mapWidth;i++){
    gtk_grid_remove_column(GTK_GRID(grid),0);
    }
}
void printMap(){
    for(int i=0;i<mapLength;i++){
        for(int j=0;j<mapWidth;j++){
                if(map[i][j]!='O'){
                GtkWidget *button;
                button=gtk_button_new();
                buttonSetName(&button,map[i][j]);
                gtk_grid_attach(GTK_GRID(grid),button,j,i,1,1);
                buttonTab[i][j]=button;
                }
        }
    }
    if(!arrowsAdded){
        addArrows();
        arrowsAdded=true;
        }
    mapMode();
  }
void restartGame(){
    clearMap();
    loadMapFromFile();
    printMap();
}
void loadMapFromFile(){
    gameOn=true;
    setAlready=0;
    dstn=0;
    moves=0;
    randomOn=false;
    char fileName[15];
    mapLength=0; mapWidth=0;
    playerOnDst=' ';

    fileName[0]='m';    fileName[1]='a';    fileName[2]='p'; fileName[3]='s';
    fileName[4]='/';    fileName[5]='/';    fileName[6]='m'; fileName[7]='a';
    fileName[8]='p';    fileName[10]='.';    fileName[11]='t'; fileName[12]='x';
    fileName[13]='t';

    fileName[9]=mapNumber+'0';


     FILE *file  = fopen(fileName, "r"); // read only
     if (file == NULL)
            {
              printf("Opening file Error!\n");
              exit(-1);
            }
    char digital;
    mapLength=0; mapWidth=0;
    while ((digital = getc(file)) != '\n'){
            map[0][mapWidth]=digital;
            mapWidth++;
    }
    mapLength++;
    putchar('\n');

    int i=0;
    while ((digital = getc(file)) != EOF){

            if(digital!='\n'){
                map[mapLength][i]=digital;
            }else{
                mapLength++;
                i=-1;
            }
            if(digital=='P'){
                posX=i;
                posY=mapLength;
            }
            if(digital=='D')
                dstn++;
            i++;
    }
    mapLength++;

   int fclose(FILE *file);
}
void saveBestResults(){
    FILE *file  = fopen("bestResults.txt", "w");
     if (file == NULL)
            {
              printf("Opening file Error!\n");
              exit(-1);
            }

    for(int i=0;i<8;i++){
        for(int j=0;j<3;j++){
            char snum[6];
            itoa(bestScore[i][j],snum,10);
            fputs(snum, file);
            if(j<2)
                fputs(" ", file);

        }
        fputs("\n", file);

    }
    fclose(file);
}
void printBestResult(){
     if(!bestScoreadded){
        GtkWidget *buttonn;
        buttonn=gtk_button_new();
        g_signal_connect (G_OBJECT (buttonn), "clicked",G_CALLBACK (menuMode), NULL);
        gtk_widget_set_name(buttonn,"exit_Button");
        gtk_grid_attach(GTK_GRID(scoreGrid),buttonn,0,0,1,1);
        bestScoreadded=true;

        for(int i=0;i<8;i++){
            for(int j=0;j<4;j++){
                GtkWidget *buttonn;
                buttonn=gtk_button_new();
                gtk_widget_set_name(buttonn,"none_Background");
                gtk_grid_attach(GTK_GRID(scoreGrid),buttonn,j+1,i,1,1);
                bestScoreButtons[i][j]=buttonn;

                if(j==0){
                    gtk_widget_set_name(buttonn,"MapInfo");
                    char snum[6]="Map ";
                    snum[4]='0'+i+1;
                    gtk_button_set_label(GTK_BUTTON(buttonn),snum);
                }
            }
        }
        }

    for(int i=0;i<8;i++){
        for(int j=1;j<4;j++){
            if(bestScore[i][j-1]!=-1){
                char snum[6];
                itoa(bestScore[i][j-1], snum, 10);
                gtk_button_set_label(GTK_BUTTON(bestScoreButtons[i][j]),snum);
                }else{
                    gtk_button_set_label(GTK_BUTTON(bestScoreButtons[i][j])," ");
                    }
                }
        }

    gtk_widget_show_all(window);
    if(arrowsAdded)
        gtk_widget_hide(gridArrows);
    gtk_widget_hide(endGrid);
    gtk_widget_hide(grid);
    gtk_widget_hide(menuGrid);
    gtk_window_set_title(GTK_WINDOW(window),"Best_Score");
    gtk_widget_set_name(window,"Map_Window");
    gtk_widget_set_size_request(window, 9*32, 3*32);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);  //okno wyswietli sie na srodku ekranu
    gtk_container_set_border_width(GTK_CONTAINER(window),10);

    }
//random map inicjalization
void readBestResults(){
    FILE *file  = fopen("bestResults.txt", "r"); // read only
    if (file == NULL)
            {
              printf("Opening file Error!\n");
              exit(-1);
            }
    int score=0;
    for(int j=0;j<8;j++){
       for(int index=0;index<3;index++){
            fscanf (file, "%d", &score);
            bestScore[j][index]=score;
            score=0;
        }
    }
    int fclose(FILE *file);
    }
void initMapInformation(){
    moves=0;
    gameOn=true;
    randomOn=true;

srand(time(NULL));
mapLength=rand()%11 +6;
mapWidth=rand()%11 +6;
do{
    posX=1+rand()%(mapWidth-2);
}while(posX>=mapWidth);

do{
    posY=1+rand()%(mapLength-2);
}while(posY>=mapLength);

dstn=1+rand()%5;
setAlready=0;
playerOnDst=' ';
}
void generateRandomMap(){
    randomOn=true;
    for(int i=1;i<mapLength-1;i++){
        for(int j=1;j<mapWidth-1;j++){
            map[i][j]=' ';
        }
    }
    for(int i=0;i<mapWidth;i++){
        map[0][i]='#';
        map[mapLength-1][i]='#';
    }
    for(int i=0;i<mapLength;i++){
        map[i][0]='#';
        map[i][mapWidth-1]='#';
    }
    map[posY][posX]='P';

    int dstSet=0,chestSet=0,x,y;
    do{
        x=2+rand()%(mapWidth-4);
        y=2+rand()%(mapLength-4);
        if(map[y][x]==' '){
            chestSet++;
            map[y][x]='C';
        }
    }while(chestSet!=dstn);

    do{
        x=1+rand()%(mapWidth-2);
        y=1+rand()%(mapLength-2);
        if(map[y][x]==' '){
            dstSet++;
            map[y][x]='D';
        }
    }while(dstSet!=dstn);

}
void saveRandomMap(){
    FILE *file  = fopen("map0.txt", "w");
     if (file == NULL)
        {
            printf("Opening file Error!\n");
            exit(-1);
        }

    for(int i=0;i<mapLength;i++){
        for(int j=0;j<mapWidth;j++){
            fputc(map[i][j], file);
        }
        if(i!=mapLength-1)
            fputs("\n", file);
    }
    fclose(file);
}
void printrandomMap(){
    mapNumber=0;
    clearMap();
    initMapInformation();
    generateRandomMap();
    saveRandomMap();
    randomOn=true;
    printMap();
}




