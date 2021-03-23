#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

typedef struct s_zone
{
    int width;
    int height;
    char background;
} t_zone;

typedef struct s_list
{
    char type;
    float x;
    float y;
    float width;
    float height;
    char color;
} t_list;

int ft_strlen(char *str)
{
    int i = 0;
    while(str[i])
        i++;
    return i;
}

int error(char *str)
{
    write(1, str, ft_strlen(str));
    return 1;
}

int free_all(FILE *fd, char *draw)
{
    fclose(fd);
    if(draw)
        free(draw);
    return 1;
}

int main(int argc, char **argv)
{
    FILE *fd;
    char *draw;
    t_zone zone;

    if(argc != 2)
        return(error("Error: argument\n"));
    if(!(fd = fopen(argv[1], "r")))
        return (error("Error: Operation file corrupted\n"));
    if(!(draw = get_zone(fd, &zone)))
        return (free_all(fd, NULL) && error("Error: Operation File Corrupted"));
    if(!(drawing(fd, &draw, &zone)))
        return (free_all(fd, draw) && error("Error: Operation File Corrupted"));
    print_draw(draw, &zone);
    free_all(fd, draw);
    return 0;
}