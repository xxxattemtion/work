/*
 * CS 240 - Fall 2023 - Suresh Jagannathan
 * Please type your name in place of <YOUR NAME HERE> to verify that you will
 * not cheat on this homework.
 *
 * Academic Honesty Pledge:
 * I certify that this code is of my own original work, and not that of other
 * students. online services, or other dishonesty. If I need help on homework,
 * I will ask a TA or the professor.
 *
 * Signed, Jianjie Chen
 */

#include "hw7.h"

/*
 * Read in a list of movies from the specified filename, store the movies in
 * the global array g_movie_array. Return the number of movies
 */

int read_movies(char *filename){
    assert(filename != NULL);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return NOT_FOUND;
    }

    fseek(file, 0, SEEK_END);
    unsigned long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (file_size == 0) {
        fclose(file);
        return NO_MOVIES;
    }
    g_movie_count = 0;
    char line_buffer[MAX_BUFFER_LEN];
    char tmp_buffer[MAX_BUFFER_LEN];
    while (fgets(line_buffer, MAX_BUFFER_LEN, file) != NULL) {

        line_buffer[strcspn(line_buffer, "\n")] = '\0';
        strcpy(tmp_buffer, line_buffer);

        char *token = strtok(line_buffer, ":");

        if (strlen(token) > MAX_BUFFER_LEN)
            return BAD_MOVIE;
        strcpy(g_movie_array[g_movie_count].movie_title, token);
        g_movie_array[g_movie_count].movie_title[MAX_TITLE_LEN - 1] = '\0';

        token = strtok(NULL, ":");
        if (token[0] == '+') {
            int seq_count = 0;
            char *sequel_token = strtok(token + 1, "+");
            while (sequel_token != NULL) {
                strcpy(g_movie_array[g_movie_count].sequels[seq_count], sequel_token);
                seq_count++;
                if (seq_count >= MAX_SEQUELS)
                    return TOO_MUCH_DATA;
                sequel_token = strtok(NULL, "+");
            }
            sequel_token = strtok(tmp_buffer, ":");
            sequel_token = strtok(NULL, ":");
            sequel_token = strtok(NULL, ":");
            sequel_token = strtok(sequel_token, "|");
            g_movie_array[g_movie_count].movie_genre = (enum genre) atoi(sequel_token);
            sequel_token = strtok(NULL, "|");
            g_movie_array[g_movie_count].movie_len_minutes = (int) atoi(sequel_token);
        } else {
            if (token != NULL) {
                token = strtok(token, "|");
                g_movie_array[g_movie_count].movie_genre = (enum genre) atoi(token);
                token = strtok(NULL, "|");
                g_movie_array[g_movie_count].movie_len_minutes = (int) atoi(token);
            }
        }
        ++g_movie_count;
        if (g_movie_count >= MAX_MOVIES)
            return TOO_MUCH_DATA;
    }
    fclose(file);
    return g_movie_count;
} /* read_movies() */


/*
 * Search through all the sequels of a given movie
 * Return the longest movie in the given genre.
 */

int find_sequels(char * title, enum genre movie_genre) {
    assert(title != NULL);
    if (!g_movie_count) {
        return NO_MOVIES;
    }
    if (movie_genre < ACTION || movie_genre > SCIFI) {
        return BAD_MOVIE;
    }
    int longest_len = -1;
    int isFound = 0;
    char longest_movie[MAX_TITLE_LEN];

    for (int i = 0; i < g_movie_count; i++) {
        if ((!strcmp(g_movie_array[i].movie_title, title))
            && (g_movie_array[i].movie_genre == movie_genre)
            && (g_movie_array[i].movie_len_minutes > longest_len)) {
            longest_len = g_movie_array[i].movie_len_minutes;
            strcpy(longest_movie, g_movie_array[i].movie_title);
            isFound = 1;
        }
    }

    if (longest_len == -1) {
        return NOT_FOUND;
    }
    if (!isFound) {
        return 0;
    }
    return longest_len;
} /* find_sequels() */

