#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MAX_TITLE_LEN 100
#define MAX_SEQUELS 10
#define MAX_BUFFER_LEN (2 * MAX_TITLE_LEN)

enum genre {
    ACTION,
    COMEDY,
    DRAMA,
   
};

struct s_movie {
    char movie_title[MAX_TITLE_LEN];
    char sequels[MAX_SEQUELS][MAX_TITLE_LEN];
    enum genre movie_genre;
    int movie_len_minutes;
};

typedef struct s_movie movie;

#define FILE_ERROR -1
#define TOO_MUCH_DATA -2
#define BAD_MOVIE -3
#define NOT_FOUND -4

// Define your global variables
movie g_movie[MAX_BUFFER_LEN];
int g_movie_count = 0;

int read_movies(char *filename) {
    assert(filename != NULL);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return FILE_ERROR;
    }

    int movie_index = 0;
    char buffer[MAX_BUFFER_LEN];

    while (fgets(buffer, sizeof(buffer), file)) {
        if (movie_index >= MAX_BUFFER_LEN) {
            fclose(file);
            return TOO_MUCH_DATA;
        }

        if (sscanf(buffer, "%[^:]:%[^|]|%d", g_movie[movie_index].movie_title,
            g_movie[movie_index].sequels[0], (int *)&g_movie[movie_index].movie_genre,
            &g_movie[movie_index].movie_len_minutes) != 4) {
            fclose(file);
            return BAD_MOVIE;
        }

        
        g_movie[movie_index].movie_title[MAX_TITLE_LEN - 1] = '\0';

        int sequels_index = 1;
        char sequel_title[MAX_TITLE_LEN];

        while (sscanf(buffer, "+%[^+]", sequel_title) == 1) {
            strcpy(g_movie[movie_index].sequels[sequels_index], sequel_title);
            sequels_index++;
        }

        
        for (int i = sequels_index; i < MAX_SEQUELS; i++) {
            g_movie[movie_index].sequels[i][0] = '\0';
        }

        movie_index++;
    }

    fclose(file);
    g_movie_count = movie_index;
    return g_movie_count;
}

int find_sequels(char *title, enum genre genre) {
    assert(title != NULL);

    int max_duration = 0;
    int found = 0;

    for (int i = 0; i < g_movie_count; i++) {
        if (strstr(g_movie[i].movie_title, title) != NULL && g_movie[i].movie_genre == genre) {
            if (g_movie[i].movie_len_minutes > max_duration) {
                max_duration = g_movie[i].movie_len_minutes;
                found = 1;
            }
        }
    }

    if (found) {
        return max_duration;
    }

    return NOT_FOUND;
}

int main() {
    
    char filename[] = "movie_list.txt";

    int read_result = read_movies(filename);

    if (read_result < 0) {
        printf("Error while reading movies: %d\n", read_result);
        return 1;
    }

    
    char title_prefix[] = "Movie";
    enum genre genre_to_find = ACTION;

    int longest_sequel_duration = find_sequels(title_prefix, genre_to_find);

    if (longest_sequel_duration == NOT_FOUND) {
        printf("No sequels found for %s with genre %d.\n", title_prefix, genre_to_find);
    } else {
        printf("Longest sequel duration for %s with genre %d: %d minutes\n", title_prefix, genre_to_find, longest_sequel_duration);
    }

    return 0;
}
