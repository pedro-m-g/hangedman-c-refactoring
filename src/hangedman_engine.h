#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h>
#include "messages.h"

#define PHRASES_LENGTH 4

#define GAME_START_OPTION_EXIT 0
#define GAME_START_OPTION_CONTINUE 1

#define GAME_OVER_EXIT 0
#define GAME_OVER_LOSE 1

#define STATUS_PLAYING 0
#define STATUS_GAME_OVER 1

/* PROTOTYPES */
void go_to_XY(int x, int y);
void text_to_XY(int x, int y, char *Text);
void specialchar_to_XY(int x, int y, int Code);

void draw_title();
void starting_draw();
void draw_gallow(int status);
void draw_head();
void draw_body();
void draw_left_arm();
void draw_right_arm();
void draw_right_leg();
void draw_left_leg();

int prompt_game_start();
void cls();

void show_game_over_screen(int status);
void show_main_screen(int status);

void init_random_seed();
char **load_phrases();
void exit_game();
char *pick_random_phrase();
char *str_to_underscores(char *str);

/////////////////////////////
/////// GO TO'S FUNCTIOS //////////
//////////////////////////////

void go_to_XY(int x, int y)
{
  HANDLE hcon;
  hcon = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD dwPos;
  dwPos.X = x;
  dwPos.Y = y;
  SetConsoleCursorPosition(hcon, dwPos);
}

void text_to_XY(int x, int y, char *Text)
{
  go_to_XY(x, y);
  printf("%s", Text);
}

void specialchar_to_XY(int x, int y, int Code)
{
  go_to_XY(x, y);
  printf("%c", Code);
}

/////////////////////////////
/////// DRAW FUNCTIOS //////////
//////////////////////////////

void draw_title()
{
  specialchar_to_XY(0, 0, 201);
  specialchar_to_XY(151, 0, 187);
  specialchar_to_XY(0, 4, 200);
  specialchar_to_XY(151, 4, 188);

  text_to_XY(60, 2, "E L   A H O R C A D O :   J U E G O");

  for (int i = 0; i < 150; i++)
  {
    specialchar_to_XY(i + 1, 0, 205);
  }

  for (int i = 0; i < 3; i++)
  {
    specialchar_to_XY(0, i + 1, 186);
  }

  for (int i = 0; i < 3; i++)
  {
    specialchar_to_XY(151, i + 1, 186);
  }

  for (int i = 0; i < 150; i++)
  {
    specialchar_to_XY(i + 1, 4, 205);
  }

  printf("\n");
}

void draw_gallow(int status)
{
  switch (status)
  {
  case 0:
    draw_head();
    break;
  case 1:
    draw_head();
    draw_body();
    break;
  case 2:
    draw_head();
    draw_body();
    draw_left_arm();
    break;
  case 3:
    draw_head();
    draw_body();
    draw_left_arm();
    draw_right_arm();
    break;
  case 4:
    draw_head();
    draw_body();
    draw_left_arm();
    draw_right_arm();
    draw_left_leg();
    break;
  case 5:
    draw_head();
    draw_body();
    draw_left_arm();
    draw_right_arm();
    draw_left_leg();
    draw_right_leg();
    break;
  case 6:
    starting_draw();
    break;
  default:
    break;
  }
}

void starting_draw()
{
  // mast
  for (int i = 8; i < 23; i++)
  {
    specialchar_to_XY(108, i + 1, 178);
    specialchar_to_XY(109, i + 1, 178);
  }
  // holder
  for (int i = 107; i < 141; i++)
  {
    specialchar_to_XY(i + 1, 8, 178);
    specialchar_to_XY(i + 1, 9, 178);
  }
  // rope
  for (int i = 9; i < 11; i++)
  {
    specialchar_to_XY(140, i + 1, 178);
    specialchar_to_XY(141, i + 1, 178);
  }
  // base
  for (int i = 90; i < 151; i++)
  {
    specialchar_to_XY(i + 1, 23, 178);
    specialchar_to_XY(i + 1, 24, 178);
  }
}

void draw_head()
{
  for (int i = 138; i < 142; i++)
  {
    specialchar_to_XY(i + 1, 10, 219);
    specialchar_to_XY(i + 1, 11, 219);
  }

  specialchar_to_XY(140, 12, 177);
  specialchar_to_XY(141, 12, 177);
}

void draw_body()
{

  for (int i = 138; i < 142; i++)
  {
    specialchar_to_XY(i + 1, 13, 177);
  }

  for (int i = 138; i < 142; i++)
  {
    specialchar_to_XY(i + 1, 14, 177);
  }
}

void draw_left_arm()
{
  for (int i = 133; i < 138; i++)
  {
    specialchar_to_XY(i + 1, 13, 219);
  }
}

void draw_right_arm()
{
  for (int i = 142; i < 147; i++)
  {
    specialchar_to_XY(i + 1, 13, 219);
  }
}

void draw_left_leg()
{
  for (int i = 14; i < 16; i++)
  {
    specialchar_to_XY(139, i + 1, 219);
    specialchar_to_XY(138, i + 1, 219);
  }
}

void draw_right_leg()
{

  for (int i = 14; i < 16; i++)
  {
    specialchar_to_XY(142, i + 1, 219);
    specialchar_to_XY(143, i + 1, 219);
  }
}

/////////////////////////////
/////// MAIN FUNCTIOS //////////
//////////////////////////////

int prompt_game_start()
{
  int op;
  printf("   \nM  E   N   U \n");
  printf("SELECCIONA UNA OPCION: \n");
  printf("1.- COMENZAR \n");
  printf("0.- SALIR  \n");
  scanf("%d", &op);
  return op;
}

void cls()
{
  system("cls");
}

/////////////////////////////
/////// GAME FUNCTIOS //////////
//////////////////////////////

void show_game_over_screen(int status)
{
  switch (status)
  {
  case GAME_OVER_EXIT:
    cls();
    draw_title();
    printf("\n\n GAME OVER \n\n");
    break;
  case GAME_OVER_LOSE:
    cls();
    draw_title();
    printf("\n\n GAME OVER: Perdiste todas tus vidas! \n\n");
    break;

  default:
    break;
  }
}

void show_main_screen(int status)
{
  switch (status)
  {
  case STATUS_PLAYING:
    cls();
    draw_title();
    draw_gallow(6);
    break;
  case STATUS_GAME_OVER:
    cls();
    draw_title();
    break;
  default:
    break;
  }
}

void init_random_seed()
{
  srand(time(NULL));
}

char **load_phrases()
{
  char **phrases = (char **)malloc(PHRASES_LENGTH * sizeof(char *));
  phrases[0] = "COMPUTADORA";
  phrases[1] = "OTORRINOLARINGOLOGO";
  phrases[2] = "VISUAL STUDIO CODE";
  phrases[3] = "LENGUAJE C";
  return phrases;
}

void exit_game()
{
  cls();
  draw_title();
  show_game_over_screen(GAME_OVER_EXIT);
}

char *pick_random_phrase()
{
  char **phrases = load_phrases();
  int index = rand() % PHRASES_LENGTH;
  return phrases[index];
}

char *str_to_underscores(char *str)
{
  int length = strlen(str);
  char *underscores = (char *)malloc(length * sizeof(char));
  for (int i = 0; i < length; i++)
  {
    if (str[i] != WHITE_SPACE && str[i] != END_OF_STRING)
    {
      underscores[i] = UNDERSCORE;
    }
    else
    {
      underscores[i] = WHITE_SPACE;
    }
  }
  return underscores;
}

int underscores_length(char *underscores_str)
{
  int original_length = strlen(underscores_str);
  int output_length = 0;
  for (int i = 0; i < original_length; i++)
  {
    if (str[i] == UNDERSCORE)
    {
      output_length++;
    }
  }
  return output_length;
}
