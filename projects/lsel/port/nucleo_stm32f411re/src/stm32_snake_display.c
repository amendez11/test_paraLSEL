#include "snake_display.h"

#define _GNU_SOURCE

#include <string.h>
#include <fcntl.h>
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

  /* Copy from linux solution */

  printf("|\r\n");
}


void 
snake_display_render(snake_game_t* p_game)
{
  /* Copy from linux solution */
}

int
snake_display_init(snake_game_t* p_game)
{
  /* Copy from linux solution */
  return 1;
}

void
snake_display_close(snake_game_t* p_game)
{
  /* Copy from linux solution */
}
