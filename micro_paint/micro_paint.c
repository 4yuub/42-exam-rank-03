#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#define ARGS_ERROR "Error: argument\n"
#define FILE_ERROR "Error: Operation file corrupted\n"
int  w;
int  h;
char c;
FILE *file;
char **zone;

void putstr(char *s) {
    while (*s)
        write(1, s++, 1);
}

int file_err(void) {
    putstr(FILE_ERROR);
    return 1;
}

int ft_round(float n)
{
    return n + (n - (int) n != 0);
}

int draw(char type, float s_x, float s_y, int x, int y, char ch) {
    if ((type != 'R' && type != 'r') || (s_x + x > w || s_y + y > h))
        return -1;
    if (type == 'r') {
        // draw border
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                if (((j == ft_round(s_x) || j == (int)s_x + x) && (i < s_y + y && i > s_y))
                    || ((i == ft_round(s_y) || i == (int)s_y + y) && (j < s_x + x && j > s_x)))
                    zone[i][j] = ch;
            }
        }
        return 0;
    }
    // draw filled
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (i > s_y && i < s_y + y && j > s_x && j < s_x + x)
                zone[i][j] = ch;
        }
    }
    return 0;
}

int main(int ac, char **av) {
    if (ac != 2) {
        putstr(ARGS_ERROR);
        return 1;
    }
    int ret;
    file = fopen(av[1], "r");
    if (!file)
        return file_err();
    ret = fscanf(file, "%d %d %c\n", &w, &h, &c);
    if (ret != 3 || w > 300 || h > 300 || w <= 0 || h <= 0)
        return file_err();
    zone = calloc(h, sizeof(char *));
    for (int i = 0; i < h; i++) {
        zone[i] = calloc(w + 1, 1);
        memset(zone[i], c, w);
    }
    float s_x, s_y;
    int   x, y;
    char  type, ch;
    while ((ret = fscanf(file, "%c %f %f %d %d %c\n", &type, &s_x, &s_y, &x, &y, &ch)) != -1) {
        if (ret != 6)
            return file_err();
        if (draw(type, s_x, s_y, x, y, ch) == -1)
            return file_err();
    }
    // print:
    for (int i = 0; i < h; i++) {
        putstr(zone[i]);
        putstr("\n");
    }
    fclose(file);
}