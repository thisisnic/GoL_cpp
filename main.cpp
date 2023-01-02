#include <ncurses.h>
#include <string>
#include <unistd.h>               // for sleep on linux

using namespace std;

int main(int argc, char ** argv){
  initscr();

  int grid_size = 20;
  int max_iterations = 20;
  
  bool aliveNow[grid_size][grid_size];
  bool aliveNext[grid_size][grid_size];
  
  // initialise alive grids to false
  for(int i = 0; i < grid_size; i++){
    for (int j = 0; j < grid_size; j++){
      aliveNow[i][j] = false; 
      aliveNext[i][j] = false;  
    }
  }
  
  // manually set some aliveNow values to true  
  aliveNow[1][3]=true;
  aliveNow[2][1]=true;
  aliveNow[2][3]=true;
  aliveNow[3][2]=true;
  aliveNow[1][3]=true;
  aliveNow[3][3]=true;
  aliveNow[3][4]=true;
  aliveNow[4][6]=true;
  
  aliveNow[5][5]=true;
  aliveNow[5][6]=true;
  
  aliveNow[7][6]=true;
  
  aliveNow[6][7]=true;
  aliveNow[7][10]=true;
  aliveNow[8][8]=true;
  aliveNow[8][9]=true;
  aliveNow[8][10]=true;
  aliveNow[9][10]=true;
  
  aliveNow[12][12]=true;
  aliveNow[12][13]=true;
  
  aliveNow[12][1]=true;
  aliveNow[12][2]=true;
  aliveNow[12][3]=true;
  aliveNow[13][3]=true;
  aliveNow[13][4]=true;

  aliveNow[13][15]=true;
  aliveNow[13][16]=true;
  aliveNow[14][17]=true;
  aliveNow[15][15]=true;
  aliveNow[15][16]=true;
  aliveNow[15][17]=true;

  
  
  for(int iteration = 0; iteration < max_iterations; iteration++){
    erase();
    // cycle through each cell
    for(int i = 0; i < grid_size; i++){
      for (int j = 0; j < grid_size; j++){
      
        int living_neighbours = 0;
          for(int x = -1; x<=1; x++){
            for(int y = -1; y<=1; y++){
              int row_to_check = i + x;
              int col_to_check = j + y;
              
              // if values are within acceptable range
              if(row_to_check >= 0 && col_to_check >=0 && row_to_check < grid_size && col_to_check < grid_size){
              
                // if cell to check is alive, increment living_neighbours by 1
                if(aliveNow[row_to_check][col_to_check] == true){
                  living_neighbours ++;
                }
              
              }             
            }
          }
        

        // if cell is alive this time
        if(aliveNow[i][j] == true){
          // move cursor to that location
          move(i,j);
          // print on screen
          printw("*");
          
          // if it has 2 or 3 living neighbours, next time it'll be alive, else it'll be dead
          if(living_neighbours == 2 | living_neighbours == 3){
            aliveNext[i][j] = true;
          } else {
            aliveNext[i][j] = false;
          }
          // if cell is dead this time...
        } else {
                   
          // if it's got 3 living neighbours, next time it'll be alive, else it'll be dead
          if(living_neighbours == 3){
            aliveNext[i][j] = true;
          } else {
            aliveNext[i][j] = false;
          }
        }
      }
    }
    
    
    // swap aliveNext values with aliveNow values
    for(int r = 0; r < grid_size; r++){
      for (int c = 0; c < grid_size; c++){
      	aliveNow[r][c] = aliveNext[r][c];
        aliveNext[r][c] = false;
      }
    }
    
    refresh();
    // pause  
    usleep(500000);
  }
    
  endwin();
  
  return 0;
}

