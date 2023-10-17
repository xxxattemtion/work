#include "hw7.h"

#include <stdio.h>
#include <string.h>

int clean_stdin() {
  while (getchar() != '\n') {
  }
  return(1);
}

int main() {
  int func = 0;
  char nl = 0;

  while (func != 4) {
    printf("Choose a function to test:\n");
    printf("  1) read_movies()\n");
    printf("  2) link_movies()\n");
    printf("  3) find_longest_movie_chain()\n");
    printf("  4) exit\n");

    scanf("%d%c", &func, &nl);

    if (func == 1) {
      printf("Please enter the file name you wish to open: ");
      char filename[MAX_TITLE_LEN];
      scanf("%[^\n]", filename);

      int output = read_movies(filename);
      printf("The value from your read_movies() function is: %d\n", output);
      printf("The number of movies you read is: %d\n", g_movie_count);
      for (int i = 0; i < g_movie_count; i++) {
        printf("\tAt index %d of g_movie_array,\n", i);
        printf("\t\tthe movie title is %s,\n", g_movie_array[i].movie_title);
        printf("\t\tthe list of sequels include:\n");
        for (int j = 0; j < MAX_SEQUELS; j++) {
            if (strlen(g_movie_array[i].sequels[j]) > 0) {
                printf("\t\t\t%s\n", g_movie_array[i].sequels[j]);
            }
            else {
                printf("\t\t(total of sequel(s): %d)\n", j);
                break;
            }
        }
        switch(g_movie_array[i].movie_genre) {
            case 0:
                printf("\t\tthe genre is ACTION\n");
                break;
            case 1:
                printf("\t\tthe genre is HORROR\n");
                break;
            case 2:
                printf("\t\tthe genre is COMEDY\n");
                break;
            case 3:
                printf("\t\tthe genre is DRAMA\n");
                break;
            default:
                printf("\t\tthe genre is SCIFI\n");
                break;
        }
        printf("\t\tand the movie length in minutes is %d.\n", g_movie_array[i].movie_len_minutes);
      }
    }
    else if (func == 2) {
      link_movies();
      printf("Movies linked\n");
    }
    else if (func == 3) {
      printf("Enter a string of the movie title you want to insert to the function: ");
      char movie_title[MAX_TITLE_LEN];
      scanf("%[^\n]", movie_title);
      movie *the_movie = NULL;
      for (int i = 0; i < g_movie_count; i++) {
        if (strcmp(g_movie_array[i].movie_title, movie_title) == 0) {
          the_movie = &(g_movie_array[i]);
          break;
        }
      }

      if (the_movie != NULL) {
        int output = find_longest_chain(the_movie);
        printf("The value from the result of your find_longest_movie_chain() function is: %d\n", output);
      } else {
        printf("Movie not found in g_movie_array\n");
      }
    }
    else if (func == 4) {
      break;
    }
    else {
      printf("Please select one of the options.\n");
    }
  }
}

