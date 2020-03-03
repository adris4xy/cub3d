#include <cub3d.h>

void    ft_error(char *s, s_game *g)
{
    write(2, "\033[1;31m", 8);
    write(2, s, ft_strlen(s));
    g->buff = 0;
    exit(-1);
}

int    close_game(s_game *g)
{
    g->buff = 0;
    exit (-1);
    return (0);
}