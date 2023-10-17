#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MAX_TITLE_LEN 100
#define MAX_SEQUELS 5
#define MAX_MOVIES 100
#define MAX_BUFFER_LEN (MAX_TITLE_LEN * 2)

enum ErrorCodes {
    SUCCESS,         // 成功
    BAD_MOVIE,       // 无效的电影标题
    TOO_MUCH_DATA,   // 文件中的电影太多
    FILE_ERROR       // 文件错误
};

typedef struct s_movie {
    char movie_title[MAX_TITLE_LEN];        // 电影标题
    char sequels[MAX_SEQUELS][MAX_TITLE_LEN];  // 相关电影标题
    enum genre movie_genre;                // 电影类型
    int movie_len_minutes;                 // 电影时长（分钟）
    struct s_movie *sequel_ptrs[MAX_SEQUELS];  // 相关电影指针
} movie;

movie g_movie[MAX_MOVIES];  // 存储电影的数组
int g_movie_count = 0;      // 电影数量

// 读取电影信息
int read_movies(char *filename) {
    assert(filename != NULL);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return FILE_ERROR;
    }

    int read_count = 0; // 读取的电影数量
    char buffer[MAX_BUFFER_LEN];

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        if (g_movie_count >= MAX_MOVIES) {
            fclose(file);
            return TOO_MUCH_DATA;
        }

        // 移除换行字符
        buffer[strcspn(buffer, "\n")] = '\0';

        if (strlen(buffer) > MAX_TITLE_LEN) {
            // 如果标题太长，则截断
            strncpy(g_movie[g_movie_count].movie_title, buffer, MAX_TITLE_LEN);
            g_movie[g_movie_count].movie_title[MAX_TITLE_LEN] = '\0';
            fclose(file);
            return BAD_MOVIE;
        } else {
            strcpy(g_movie[g_movie_count].movie_title, buffer);
            g_movie_count++;
            read_count++;
        }
    }

    fclose(file);

    if (read_count > 0) {
        return read_count; // 返回成功读取的电影数量
    } else {
        return 0; // 没有电影被读取
    }
}


