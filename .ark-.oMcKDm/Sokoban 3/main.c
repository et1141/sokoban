#include "objects.h"
#include <gdk/gdkkeysyms.h>
#define mapCount 8

GtkWidget *number_button; char numb[4];
bool randomOn;


void nextMap(){
    if(mapNumber<mapCount)
        mapNumber++;
    //numb[0]=mapNumber+'0';
    //gtk_widget_set_name(number_button,numb);
    char snum[2];
    itoa(mapNumber, snum, 10);
    gtk_button_set_label(GTK_BUTTON(number_button),snum);
    }
void prevMap(){
    if(mapNumber>1)
        mapNumber--;
    numb[3]=mapNumber+'0';
    char snum[2];
    itoa(mapNumber, snum, 10);
    gtk_button_set_label(GTK_BUTTON(number_button),snum);
}

GtkWidget *box;
GtkWidget *window;
GtkWidget *menuGrid;
GtkWidget *endGrid;
GtkWidget *scoreGrid;


bool arrowsAdded,gameOn,congratulationAdded;
int mapNumber;
void resetBestResults(){
    for(int i=0;i<8;i++){
        for(int j=0;j<3;j++){
            bestScore[i][j]=-1;

        }
        }
}
void on_window_main_key_press_event(GtkWidget *widget, GdkEventKey *key, gpointer user_data) {
    char pressedKey = key->keyval; //Incase you need to find out what key got pressed
    if(gameOn){
    if(pressedKey=='w'||pressedKey=='W')
        move2(0,-1);

    else
        if(pressedKey=='s'||pressedKey=='S')
                move2(0,1);
        else
            if(pressedKey=='a'||pressedKey=='A')
                move2(-1,0);

            else
                if(pressedKey=='d'||pressedKey=='D')
                    move2(1,0);
    }
}



int main(int argc, char *argv[]){
    readBestResults();
    numb[0]='n';numb[1]='u';numb[2]='m';
    mapNumber=1;
    arrowsAdded=false; gameOn=false,congratulationAdded=false;
    mapWidth=0;

    //munu buttons
    GtkWidget *prev_button,*next_button;    GtkWidget *button2,*button3,*button4, *button5,*button6;
    gtk_init(&argc,&argv);
    load_css();

    window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window,"destroy",G_CALLBACK(gtk_main_quit),NULL);
    g_signal_connect(window, "key-press-event", G_CALLBACK(on_window_main_key_press_event), NULL);
    gtk_window_set_title(GTK_WINDOW(window),"Sokoban");
    gtk_widget_set_size_request(window, 800, 480);
    gtk_window_set_resizable (GTK_WINDOW(window), FALSE);

    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);  //okno wyswietli sie na srodku ekranu
    gtk_container_set_border_width(GTK_CONTAINER(window),10);

    //button with grids
    box=gtk_box_new(GTK_ORIENTATION_VERTICAL,1);
    gtk_container_add(GTK_CONTAINER(window),box);
    gtk_widget_set_name(box,"menu_Grid");

    menuGrid=gtk_grid_new();
    gtk_box_pack_start(GTK_BOX(box),menuGrid,1,1,1);
    gtk_widget_set_name(menuGrid,"menu_Grid");

    //1b
    number_button = gtk_button_new_with_label("1");
    gtk_widget_set_name(number_button,"number_Button");
    gtk_widget_set_size_request(number_button,32,32);
    gtk_grid_attach(GTK_GRID(menuGrid),number_button,1,3,1,1);

    //1c
    prev_button = gtk_button_new();
    gtk_widget_set_name(prev_button,"prev_Map");
    gtk_widget_set_size_request(prev_button,32,32);
    g_signal_connect (G_OBJECT (prev_button), "clicked",G_CALLBACK (prevMap), NULL);
    gtk_grid_attach(GTK_GRID(menuGrid),prev_button,0,3,1,1);

    //1a
    next_button = gtk_button_new();//_with_label ("=>");
    gtk_widget_set_name(next_button,"next_Map");
    gtk_widget_set_size_request(next_button,32,32);
    g_signal_connect (G_OBJECT (next_button), "clicked",G_CALLBACK (nextMap),NULL);  //hello to napisana przez nas funkcja
    gtk_grid_attach(GTK_GRID(menuGrid),next_button,2,3,1,1);

    //2
    button2= gtk_button_new_with_label ("Play");
    gtk_widget_set_name(button2,"menu_Button");
    g_signal_connect (G_OBJECT (button2), "clicked",G_CALLBACK (startGame),NULL);  //hello to napisana przez nas funkcja
    gtk_grid_attach(GTK_GRID(menuGrid),button2,0,5,3,1);

    //3
    button3 = gtk_button_new_with_label ("Random Map");
    gtk_widget_set_name(button3,"menu_Button");
    g_signal_connect (G_OBJECT (button3), "clicked",G_CALLBACK (printrandomMap), NULL);

    gtk_grid_attach(GTK_GRID(menuGrid),button3,0,6,3,1);


    //4
    button4 = gtk_button_new_with_label ("Best Scores");
    gtk_widget_set_name(button4,"menu_Button");
    g_signal_connect (G_OBJECT (button4), "clicked",G_CALLBACK (printBestResult), NULL);
    gtk_grid_attach(GTK_GRID(menuGrid),button4,0,7,3,1);

    //5
    button5 = gtk_button_new_with_label ("Reset Scores");
    gtk_widget_set_name(button5,"menu_Button");

    g_signal_connect (G_OBJECT (button5), "clicked",G_CALLBACK (resetBestResults), NULL);
    gtk_grid_attach(GTK_GRID(menuGrid),button5,0,8,3,1);

    //6
    button6 = gtk_button_new_with_label ("Quit");
    gtk_widget_set_name(button6,"menu_Button");
    g_signal_connect (G_OBJECT (button6), "clicked",G_CALLBACK (gtk_main_quit), NULL);
    gtk_grid_attach(GTK_GRID(menuGrid),button6,0,9,3,1);

    gtk_widget_show_all(window);

    grid=gtk_grid_new();
    gtk_box_pack_start(GTK_BOX(box),grid,TRUE,TRUE,0);

    scoreGrid=gtk_grid_new();
    gtk_box_pack_start(GTK_BOX(box),scoreGrid,TRUE,TRUE,0);


    endGrid=gtk_grid_new();
    gtk_box_pack_start(GTK_BOX(box),endGrid,TRUE,TRUE,0);
    gtk_grid_set_column_spacing(GTK_GRID(endGrid),1);
    gtk_grid_set_column_homogeneous(GTK_GRID(endGrid),TRUE);

    gtk_main();
    saveBestResults();

    return 0;
}

