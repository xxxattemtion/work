#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_TITLE_LEN 100
#define MAX_BUFFER_LEN (MAX_TITLE_LEN * 2)
#define MAX_SEQUELS 5
#define MAX_MOVIES 50

enum genre {
    ACTION,
    ADVENTURE,
    SCI_FI
};

struct s_movie {
    char movie_title[MAX_TITLE_LEN];
    char sequels[MAX_SEQUELS][MAX_TITLE_LEN];
    enum genre movie_genre;
    int movie_len_minutes;
    struct s_movie *sequel_ptrs[MAX_SEQUELS];
};

typedef struct s_movie movie;

#define FILE_ERROR -1
#define BAD_MOVIE -2
#define TOO_MUCH_DATA -3

movie g_movie[MAX_MOVIES];
int g_movie_count = 0;

int read_movies(char *filename) {
    assert(filename != NULL);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return FILE_ERROR;
    }

    int movie_count = 0;
    char buffer[MAX_BUFFER_LEN];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        if (movie_count >= MAX_MOVIES) {
            fclose(file);
            return TOO_MUCH_DATA;
        }

        if (strlen(buffer) > MAX_BUFFER_LEN) {
            fclose(file);
            return BAD_MOVIE;
        }

        buffer[strcspn(buffer, "\n")] = '\0';

        strncpy(g_movie[movie_count].movie_title, buffer, MAX_TITLE_LEN);
        for (int i = 0; i < MAX_SEQUELS; i++) {
            g_movie[movie_count].sequels[i][0] = '\0';
        }

        g_movie[movie_count].sequel_ptrs[0] = NULL;
        movie_count++;
    }

    fclose(file);
    g_movie_count = movie_count;
    return movie_count;
}

void link_movies() {
    for (int i = 0; i < g_movie_count; i++) {
        for (int j = 0; j < MAX_SEQUELS; j++) {
            for (int k = 0; k < g_movie_count; k++) {
                if (strcmp(g_movie[i].sequels[j], g_movie[k].movie_title) == 0) {
                    g_movie[i].sequel_ptrs[j] = &g_movie[k];
                    break;
                }
            }
        }
    }
}

int find_longest_movie_chain(movie *the_movie) {
    if (the_movie == NULL) {
        return 0;
    }

    int max_minutes = the_movie->movie_len_minutes;

    for (int i = 0; i < MAX_SEQUELS; i++) {
        if (the_movie->sequel_ptrs[i] != NULL) {
            int chain_minutes = the_movie->movie_len_minutes + find_longest_movie_chain(the_movie->sequel_ptrs[i]);
            if (chain_minutes > max_minutes) {
                max_minutes = chain_minutes;
            }
        }
    }

    return max_minutes;
}

int main() {
    int result;
    
    result = read_movies("bad_movie_MAX_BUFFER_LEN_1.txt");
    switch (result) {
        case BAD_MOVIE:
            printf("Error: BAD_MOVIE\n");
            break;
        case TOO_MUCH_DATA:
            printf("Error: TOO_MUCH_DATA\n");
            break;
        default:
            printf("Read %d movies successfully\n", result);
            break;
    }
    
    result = read_movies("bad_movie_MAX_MOVIES_1.txt");
    switch (result) {
        case BAD_MOVIE:
            printf("Error: BAD_MOVIE\n");
            break;
        case TOO_MUCH_DATA:
            printf("Error: TOO_MUCH_DATA\n");
            break;
        default:
            printf("Read %d movies successfully\n", result);
            break;
    }

    result = read_movies("good_1.txt");
    switch (result) {
        case BAD_MOVIE:
            printf("Error: BAD_MOVIE\n");
            break;
        case TOO_MUCH_DATA:
            printf("Error: TOO_MUCH_DATA\n");
            break;
        default:
            printf("Read %d movies successfully\n", result);
            break;
    }

    link_movies();

    int longest_chain = find_longest_movie_chain(&g_movie[0]);
    printf("\nLongest movie chain: %d minutes\n", longest_chain);

    return 0;
}

