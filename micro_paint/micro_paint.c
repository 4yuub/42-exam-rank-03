#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define ARGS_ERR "Error: argument"
#define FILE_ERR "Error: Operation file corrupted"
char **zone;
int w, h, ret;
char c, type;
float x_s, y_s, x_w, y_h;
FILE *file;

void putstr(char *s) {
    while (*s)
        write(1, s++, 1);
    write(1, "\n", 1);
}

int draw(void) {
    if ((type != 'r' && type != 'R') || x_w <= 0 || y_h <= 0)
        return -1;
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            bool cond1 = !(x < x_s || y < y_s || y > (y_s + y_h) || x > (x_s + x_w));
            bool cond2 = x - x_s < 1 || y - y_s < 1 || (y_s + y_h) - y < 1 || (x_s + x_w) - x < 1;
            if ((cond1) && ((cond2 && type == 'r')||type == 'R'))
                    zone[y][x] = c;
        }
    }
    return 0;
}

int main(int ac, char **av) {
    if (ac != 2)
        return (putstr(ARGS_ERR), 1);
    file = fopen(av[1], "r");
    if (!file)
        return (putstr(FILE_ERR), 1);
    ret = fscanf(file, "%d %d %c\n", &w, &h, &c);
    if (ret != 3 || w <= 0 || h <= 0 || w > 300 || h > 300)
        return ( putstr(FILE_ERR), 1);
    zone = calloc(h, sizeof(char *));
    for (int i = 0; i < h; i++) {
        zone[i] = calloc(w + 1, 1);
        memset(zone[i], c, w);
    }
    while ((ret = fscanf(file, "%c %f %f %f %f %c\n", &type, &x_s, &y_s, &x_w, &y_h, &c)) != -1)
        if (ret != 6 || draw() == -1)
            return (putstr(FILE_ERR), 1);
    for (int i = 0; i < h; i++)
        putstr(zone[i]);
}
