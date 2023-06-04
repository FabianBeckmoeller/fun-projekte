 /* Any live cell with fewer than two live neighbours dies, as if by underpopulation.
    Any live cell with two or three live neighbours lives on to the next generation.
    Any live cell with more than three live neighbours dies, as if by overpopulation.
    Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

    Nachbarn < 3  = dead
    2/3 Nachbarn = Stays
    Nachbarn >3 = dies
    Nachbarn = 3 = alive
*/
#include <ncurses.h>
#include <iostream>


using namespace std;


bool field[50][50]; // [y][x]
bool buff[50][50];

void next_gen(){   // Function for the next generation
   
    int neighbours = 0;    // Variable to count all the neigbours of a cell
    for (int y = 0; y < 50; y++){    // Counts the neigbours of every single cell

    for (int x = 0; x < 50; x++){    // Counts the neighbours from every direction
        if(field[y+1][x+1]== true){
        neighbours++;}
        if(field[y+1][x]== true){
        neighbours++;}
        if(field[y+1][x-1]== true){
        neighbours++;}
        if(field[y][x-1]== true){
        neighbours++;}
        if(field[y][x+1]== true){
        neighbours++;}
        if(field[y-1][x+1]== true){
        neighbours++;}
        if(field[y-1][x]== true){
        neighbours++;}
        if(field[y-1][x-1]== true){
        neighbours++;}

                                    // Determines whic state the cell will occupie in the next generation and is loaded in the buffer
        if(neighbours == 3){          // Reproduction
            buff[y][x] = true;
        } else if(neighbours > 3 ){   // Overpop
            buff[y][x] = false;
        } else if(neighbours < 2){   // Underpop
            buff[y][x] = false;
        }  else if (field[y][x] == true) { // No change
           buff[y][x]= true;}
           
            neighbours = 0;           // Resets the number of neighbours for the next cell
    
    } 
    
    }
  
    for (int y = 0; y < 50; y++){      // Loads the Buffer into the array field
    for (int x = 0; x < 50; x++){
    if(buff[y][x] == true){
    field[y][x] = true;
    } else {
        field[y][x] = false;
    }}}

    for (int y = 0; y < 50; y++){   // Clears the buffer
    for (int x = 0; x < 50; x++){
    buff[y][x] = false;}  } 
}


void print(){  // Function for printing the image without the cursor(When the game is running)
    clear();   // Deletes the currently displayed image
     for (int y = 0; y < 50; y++){  // Goes through every single element in the field[] array and displays it

    for (int x = 0; x < 50; x++){
        move(y, x*2);             // Moves the cursor to the correct point (x*2 because each element/cell is two characters wide)
     if(field[y][x] == true) {
        attron(COLOR_PAIR(2));    // If the cell is alive > green
        printw("# ");
    } else {
        attron(COLOR_PAIR(1));    // If the cell is dead > black
    printw("# ");
    }
   
  
    }
}
refresh();  // Refreshes the displayed image
}


void print_paint(int cursor_y, int cursor_x){  // Function for printing the Image with the cursor enabled
clear();                                // Deletes the currently displayed image

 for (int y = 0; y < 50; y++){          // Goes through every single element in the field[] array and displays it

    for (int x = 0; x < 50; x++){
        move(y, x*2);                    // Moves the cursor to the correct point (x*2 because each element/cell is two characters wide)
    if( y == cursor_y && x == cursor_x){ // If the Cursor is on that point > blue
    attron(COLOR_PAIR(3));
    printw("# ");
    } else if(field[y][x] == true) {     // If the cell is alive > green
        attron(COLOR_PAIR(2));
        printw("# ");
    } else {
        attron(COLOR_PAIR(1));           // If the cell is dead > black
    printw("# ");
    }
    }
    
}
refresh(); // Refreshes the displayed image
}

int main(){
    for (int y = 0; y < 50; y++){   // Turns all of the elements in the field off, just to be sure

    for (int x = 0; x < 50; x++){
    field[y][x] = false;}  } 

    int cursor_x = 25; // Variables for the position of the cursor
    int cursor_y = 25;
    initscr();      // Initializes the window
    noecho();       // Turns echo off
    cbreak();
    keypad(stdscr, TRUE); // Enables inpot via keypad

    start_color();  // Initializes the color-display
    init_pair(1, COLOR_BLACK, COLOR_BLACK); // Color-set for dead cells
    init_pair(2, COLOR_GREEN, COLOR_GREEN); // Color-set for alive cells
    init_pair(3, COLOR_BLUE,  COLOR_BLUE);  // Color-set for the cursor
    
      int ch = 0;
  while (ch != 32) {  // Exits "Edit-Mode" with SPACE
    ch = getch();     // Input is loaded in the variable
    switch (ch) {     // Switch case for UP, DOWN, LEFT, RIGHT and ENTER to place/ remove cells
      case KEY_UP:    
        if(cursor_y > 0){
        cursor_y--;}
        break;
      case KEY_DOWN:
     if(cursor_y < 49){
        cursor_y++;}
        break;
      case KEY_LEFT:
      if(cursor_x > 0){
        cursor_x--;}        
        break;
      case KEY_RIGHT:
      if(cursor_x < 49){
        cursor_x++;}
        break;
        case 10:      // 10 is ENTER key
        if(field[cursor_y][cursor_x]== true){   // Switching the state of a cell
            field[cursor_y][cursor_x] = false;
        } else {
            field[cursor_y][cursor_x] = true;
        }
        break;
    }
    print_paint(cursor_y,cursor_x); // Function for printing the Image with the cursor enabled
  }

  print();            // Prints the image without the cursor
  while(ch != 27){    // As long as ESC is not pressed
    ch = getch();
    if(ch == 32){     // If SPACE is pressed
        next_gen();   // The next generation is generated
        print();      // The next generation is displayed
    } 
  }
  echo();   // Turns echo back on and ends curses
  endwin(); 
}

