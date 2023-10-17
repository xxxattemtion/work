#ifndef HW7_H
#define HW7_H

/* Included Libraries */

#include <assert.h>
#include <stdio.h>

/* Constant Definitions */

#define MAX_TITLE_LEN     (16)
#define MAX_BUFFER_LEN    (32)
#define MAX_SEQUELS       (3)
#define MAX_MOVIES        (10)

enum genre {
  ACTION,
  HORROR,
  COMEDY,
  DRAMA,
  SCIFI,
  BAD_GENRE
};

struct s_movie {
  char movie_title[MAX_TITLE_LEN];
  char sequels[MAX_SEQUELS][MAX_TITLE_LEN];
  enum genre movie_genre;
  int movie_len_minutes;

  struct s_movie * sequel_ptrs[MAX_SEQUELS];
};

typedef struct s_movie movie;

/* Error Codes */
#define BAD_MOVIE     (-1)
#define TOO_MUCH_DATA (-2)
#define NOT_FOUND     (-3)
#define NO_MOVIES     (-4)
#define NOT_IMPLEMENTED_ERR (-240)


/* Function Prototypes */

int read_movies(char *);
void link_movies();
int find_longest_chain(movie *);

/* Global Variables */
extern movie g_movie_array[MAX_MOVIES];
extern int g_movie_count;

#endif // HW7_H
