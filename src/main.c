#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "hangedman_engine.h"

/* MAIN PRINCIPAL */
int main()
{
  init_random_seed();

  // variables
  int j = 0, k = 0, match = 0;
  int real_leng = 0, leng = 0;
  char phrase[30];
  char correct_phrase[30];
  char letter;
  int game_start_option;
  char username[50];
  int lifes = 6;
  int points = 0;

  draw_title();
  game_start_option = prompt_game_start();

  if (game_start_option == GAME_START_OPTION_EXIT)
  {
    exit_game();
    return 0;
  }

  show_main_screen(STATUS_PLAYING);
  printf(ENTER_USERNAME_MESSAGE);
  scanf(INPUT_STRING, &username);

  show_main_screen(STATUS_PLAYING);

  strcpy(phrase, pick_random_phrase());

  leng = strlen(phrase);

  // underscore
  for (int i = 0; i < leng; i++)
  {
    if (phrase[i] != WHITE_SPACE && phrase[i] != END_OF_STRING)
    {
      correct_phrase[i] = UNDERSCORE;
      real_leng++;
    }
    else
    {
      correct_phrase[i] = WHITE_SPACE;
    }
  }

  correct_phrase[leng] = END_OF_STRING;
  go_to_XY(114, 21);

  for (int i = 0; i < leng; i++)
  {
    printf(OUTPUT_CHARACTER, correct_phrase[i]);
  }

  // heart game

  while (lifes > 0 && k < real_leng)
  {

    match = 0;

    go_to_XY(10, 10);
    printf(ENTER_NEXT_LETTER_MESSAGE, username);
    scanf(INPUT_CHARACTER, &letter);

    // checking for matches

    go_to_XY(114, 21);

    for (int i = 0; i < leng; i++)
    {
      if ((phrase[i] == letter || phrase[i] == toupper(letter)) && correct_phrase[i] == UNDERSCORE)
      {
        correct_phrase[i] = phrase[i];
        points += 100;
        k++; // to manage matches
        match = 1;
      }
    }

    go_to_XY(114, 21);
    for (int i = 0; i < leng; i++)
    {
      printf(OUTPUT_CHARACTER, correct_phrase[i]);
    }

    if (!match)
    {
      if (points > 0)
      {
        points = points - 50;
      }

      int match_already = 0;
      for (int i = 0; i < leng; i++)
      {
        if (correct_phrase[i] == letter)
        {
          match_already = 1;
          break;
        }
      }

      if (!match_already)
      {
        lifes--;
        draw_gallow(j);
        j++;

        go_to_XY(90, 27);
        printf(NOT_FOUND_STATUS_MESSAGE, points, lifes);
      }
    }
    else
    {
      // show match msg
      go_to_XY(90, 27);
      printf(FOUND_STATUS_MESSAGE, points, lifes);
    }
  }

  if (lifes == 0)
  {
    show_game_over_screen(GAME_OVER_LOSE);
  }

  show_main_screen(STATUS_GAME_OVER);
  printf(GAME_OVER_STATUS_MESSAGE, username, points, (real_leng * 100));

  return 0;
}
