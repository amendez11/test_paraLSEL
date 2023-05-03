#include "snake_display.h"

#define _GNU_SOURCE

#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_X 16
#define MAX_Y 16

struct fb_t {
  char pixel[MAX_Y][MAX_X];
};
static struct fb_t fb_s;
static struct fb_t* fb = &fb_s;

static void
clear_screen()
{
  printf("\e[1;1H\e[2J");
  fsync(1);
}

static void
print_hlimit(snake_game_t* p_game)
{
  printf("+");
  for (int i = 0; i < p_game->limits.x; i++) {
    printf("-");
  }
  printf("+\r\n");
}


static void
print_row(snake_game_t* p_game, int y)
{
  printf("|");

  /* TODO print row of game from fb struct */

  printf("|\r\n");
}


void 
snake_display_render(snake_game_t* p_game)
{
  /* Change: Each element is a char */
  /* - Apple is '*' */
  /* - Snake head is '@' */
  /* - Snake body 'o' */
  /* - Empty pixels are ' ' */
  struct segment_t *seg_i;

  /* Set Blank */
  memset(fb, ' ', sizeof(struct fb_t));

  /* TODO Set Apple */

  /* TODO Set snake body */

  /* TODO Set snake head */

  fb->pixel[seg_i->y][seg_i->x]='@';
  
  clear_screen();
  print_hlimit(p_game); 

  /* TODO Print every row with print_row */

  print_hlimit(p_game); 
}

int
snake_display_init(snake_game_t* p_game)
{
  /* TODO Set limits */

  return 1;
}

void
snake_display_close(snake_game_t* p_game)
{
}
