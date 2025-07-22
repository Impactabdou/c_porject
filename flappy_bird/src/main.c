#include "../include/game_manager.h"
#include <pthread.h> // Multithreading
#include <stdio.h>
#include <stdlib.h>  // for atexit()
#include <termios.h> // For changing terminal mode
#include <unistd.h>  // For changing terminal mode

struct termios original; // A struct to save the original state of terminal
int spaceON = 0;         // For thread communication
int gameEnd = 0;

void disableRAWMode();
void enableRAWMode();
void *asciRead();
void *print(game *gm);

int main() {

  srand((unsigned)time(NULL));

  unsigned int map_width = 150;
  unsigned int map_height = 40;
  unsigned int max_num_walls = 5;
  unsigned int left_limitation = 20;
  unsigned int number_of_walls_at_start = 3;
  unsigned int count = 0;

  point init_pos_bird = {5, map_height / 2};

  bird *b = create_bird(init_pos_bird);

  map *m = create_map(map_width, map_height, b, max_num_walls);

  game *gm = create_game_manager(m, left_limitation, EASY_MODE);

  add_walls_in_game(gm, number_of_walls_at_start);

  /*empty map*/
  update_frames(m);
  print_map(*m);
  count++;

  pthread_t id_read, id_print;
  pthread_create(&id_print, NULL, (void *(*)(void *))print, gm);
  pthread_create(&id_read, NULL, asciRead, NULL);

  pthread_join(id_print, NULL);
  pthread_join(id_read, NULL);
  return 0;
}

/// Reads keyboard input
void *asciRead() {
  enableRAWMode(); // local function: Enable Raw Mode
  char ch;
  while (1) {
    usleep(10000);
    if (gameEnd) {
      break;
    }
    if ((ch = getchar()) == 32 && spaceON == 0) {
      spaceON = 1;
      printf("Bird jump!\n");
    }
  }
}

void *print(game *gm) {
  unsigned int bird_speed = 1;
  int end;
  while (1) { // When ESC is not pressed
    if (spaceON) {
      end = move_bird_in_game(gm, bird_speed, UP);
      spaceON = 0;
    } else {
      end = move_bird_in_game(gm, bird_speed, DOWN);
    }
    if (!end) {
      break;
    }
  }
  gameEnd = 1;
  printf("END : press ENTER to exit\n");
  exit(1);
}

/// This function enables RAW mode for terminal.
void enableRAWMode() {
  struct termios raw;
  tcgetattr(STDIN_FILENO, &raw); // Save the state of the terminal to struct raw
                                 // STDIN_FILENO is from <stdlib.h>
                                 // tcgetattr() from <termios.h>
  tcgetattr(STDIN_FILENO, &original);
  atexit(&disableRAWMode); // Revert to canonical mode when exiting the program
                           // atext() from <stdlib.h>
  raw.c_lflag &=
      ~(ECHO | ICANON); // Turn off canonical mode
                        // Turn off ECHO mode so that keyboard is not
                        // printing to terminal
                        // ICANON and ECHO is bitflag. ~ is binary NOT operator

  tcsetattr(STDIN_FILENO, TCSAFLUSH,
            &raw); // Set the terminal to be in raw mode
                   // tcsetattr() from <termios.h>
}

void disableRAWMode() {
  tcsetattr(STDIN_FILENO, TCSAFLUSH,
            &original); // Set terminal to original state
}
