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

int draw(char type, float x_o, float y_o, float r, char ch) {
    if (type != 'c' && type != 'C')
        return -1;
    if (type == 'c') {
        // draw border
        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                if (sqrtf((x - x_o) * (x - x_o) + (y - y_o) * (y - y_o)) <= r
                    && r - sqrtf((x - x_o) * (x - x_o) + (y - y_o) * (y - y_o)) < 1)
                    zone[y][x] = ch;
            }
        }
        return 0;
    }
    // draw filled
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            if (sqrtf((x - x_o) * (x - x_o) + (y - y_o) * (y - y_o)) <= r)
                zone[y][x] = ch;
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
    float x_o, y_o, r;
    char  type, ch;
    while ((ret = fscanf(file, "%c %f %f %f %c\n", &type, &x_o, &y_o, &r, &ch)) != -1) {
        if (ret != 5)
            return file_err();
        if (draw(type, x_o, y_o, r, ch) == -1)
            return file_err();
    }
    // print:
    for (int i = 0; i < h; i++) {
        putstr(zone[i]);
        putstr("\n");
    }
    fclose(file);
}