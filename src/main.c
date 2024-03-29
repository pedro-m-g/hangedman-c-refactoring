#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "hangedman_engine.h"

/* MAIN PRINCIPAL */
int main()
{
  init_random_seed();

  // variables
  int hangedman_status = 0;
  int guessed_letters_quantity = 0;
  bool phrase_contains_input_character = 0;

  int phrase_length_without_spaces = 0;
  int full_phrase_length = 0;

  char phrase_to_guess[30];
  char guessed_phrase[30];
  char input_character;
  int game_start_option;
  char username[50];
  int lives_left = 6;
  int score = 0;

  cls();
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

  strcpy(phrase_to_guess, pick_random_phrase());

  full_phrase_length = strlen(phrase_to_guess);

  strcpy(guessed_phrase, str_to_underscores(phrase_to_guess));
  phrase_length_without_spaces = underscores_length(guessed_phrase);

  guessed_phrase[full_phrase_length] = END_OF_STRING;
  go_to_XY(114, 21);

  print_phrase(guessed_phrase);

  // heart game
  while (lives_left > 0 && guessed_letters_quantity < phrase_length_without_spaces)
  {
    phrase_contains_input_character = false;

    go_to_XY(10, 10);
    printf(ENTER_NEXT_LETTER_MESSAGE, username);
    scanf(INPUT_CHARACTER, &input_character);

    // checking for matches
    go_to_XY(114, 21);

    char *phrase_without_spaces = str_excluding_spaces(phrase_to_guess);
    int letter_index = str_index_ignoring_case(phrase_without_spaces, input_character);
    phrase_contains_input_character = letter_index == INDEX_NOT_FOUND;

    if (phrase_contains_input_character)
    {
      guessed_phrase[letter_index] = phrase_to_guess[letter_index];
      score += 100;
      guessed_letters_quantity++; // to manage matches
    }

    go_to_XY(114, 21);
    print_phrase(guessed_phrase);

    if (!phrase_contains_input_character)
    {
      if (score > 0)
      {
        score = score - 50;
      }

      bool was_guessed_previously = false;
      for (int i = 0; i < full_phrase_length; i++)
      {
        if (guessed_phrase[i] == input_character)
        {
          was_guessed_previously = true;
          break;
        }
      }

      if (!was_guessed_previously)
      {
        lives_left--;
        draw_gallow(hangedman_status);
        hangedman_status++;

        go_to_XY(90, 27);
        printf(NOT_FOUND_STATUS_MESSAGE, score, lives_left);
      }
    }
    else
    {
      // show match msg
      go_to_XY(90, 27);
      printf(FOUND_STATUS_MESSAGE, score, lives_left);
    }
  }

  if (lives_left == 0)
  {
    show_game_over_screen(GAME_OVER_LOSE);
  }

  show_main_screen(STATUS_GAME_OVER);
  printf(GAME_OVER_STATUS_MESSAGE, username, score, (phrase_length_without_spaces * 100));

  return 0;
}
