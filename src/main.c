#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "hangedman_engine.h"

/* MAIN PRINCIPAL */
int main()
{
  init_random_seed();

  char **phrases = load_phrases();

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
    cls();
    draw_title();
    end_game(0);
    return 0;
  }

  start_game(0);
  printf("\nIngresa tu usuario\n");
  scanf("%s", &username);

  start_game(0);

  strcpy(phrase, phrases[rand() % PHRASES_LENGTH]);

  leng = strlen(phrase);

  // underscore
  for (int i = 0; i < leng; i++)
  {
    if (phrase[i] != ' ' && phrase[i] != '\0')
    {
      correct_phrase[i] = '_';
      real_leng++;
    }
    else
    {
      correct_phrase[i] = ' ';
    }
  }

  correct_phrase[leng] = '\0';
  go_to_XY(114, 21);

  for (int i = 0; i < leng; i++)
  {
    printf("%c ", correct_phrase[i]);
  }

  // heart game

  while (lifes > 0 && k < real_leng)
  {

    match = 0;

    go_to_XY(10, 10);
    printf("%s!, Ingresa una LETRA\n", username);
    scanf(" %c", &letter);

    // checking for matches

    go_to_XY(114, 21);

    for (int i = 0; i < leng; i++)
    {
      if ((phrase[i] == letter || phrase[i] == toupper(letter)) && correct_phrase[i] == '_')
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
      printf("%c ", correct_phrase[i]);
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
        printf("\n NO ENCONTRADA! -- PUNTOS: %d VIDAS: %d\n", points, lifes);
      }
    }
    else
    {

      // show match msg
      go_to_XY(90, 27);
      printf("\n ENCONTRADA! -- PUNTOS: %d VIDAS: %d\n", points, lifes);
    }
  }

  if (lifes == 0)
  {
    end_game(1);
  }

  start_game(1);
  printf("\n\n--- Jugador: %s Puntos obtenidos: %d de: %d disponibles. --- \n\n", username, points, (real_leng * 100));

  return 0;
}
