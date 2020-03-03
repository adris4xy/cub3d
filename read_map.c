/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egarcia- <emilioggo@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 18:22:08 by egarcia-          #+#    #+#             */
/*   Updated: 2020/03/02 21:27:48 by egarcia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void        ft_set_start(int x, int y, char *map, s_game *g)
{
    g->ray.posx = x + 0.5;
    g->ray.posy = y + 0.5;
    if (*map == 'N')
    {
        g->ray.dirx = -1;
        g->ray.planey  = 0.66;
    }
    else if (*map == 'S')
    { 
        g->ray.dirx = 1;
        g->ray.planey  = -0.66;
    }
    else if (*map == 'E')
    { 
        g->ray.dirx = 0;
        g->ray.planey  = 0.66;
    }
    else if (*map == 'W')
    { 
        g->ray.dirx = 0;
        g->ray.planey  = -0.66;
    }
    else
        ft_error("ERROR\n INIT ZONE DOES NOT MATCH", g);
}

int         ft_ncol(char *map)
{
    int col;

    col = 0;
    while (*map != '\n')
    {
        if (ft_isdigit(*map))
            col++;
        map++;
    }
    return (col);
}
void        ft_map(char *map, s_game *g, int row)
{
    int x;
    int col;
    int y;

    g->worldmap = (int **)malloc(sizeof(int *) * row);
    col = ft_ncol(map);
    x = 0;
   
    while (x < row)
    {
        if (*map != '1')
        ft_error("ERROR\n MAP IS NOT CLOSED\n", g);
        g->worldmap[x] = (int *)malloc(sizeof(int) * col);
        y = 0;
        while (y < col)
        {
            if ((x == 0 || x == row)  && *map != '1')
                ft_error("Error\n MAP IS NOT CLOSED\n", g);
            if (ft_isdigit(*map))
            {
                g->worldmap[x][y] = *map - '0';
                if (*map == '2')
                    ft_isspray(g, x, y);
            }
            else
            {
                ft_set_start(x, y, map, g);
                g->worldmap[x][y] = 0;
            }
            map += 2;
            y++;
        }
        x++;
    }
}

void        ft_path_s(char *line, s_game *g)
{
    int  i;

    i = 0;

    if (line[1] == 'O')
    {
        while (line[i] != '.')
            i++;
        g->so_path = ft_strdup (&line[i]);
    }
    else if (line[1] == ' ')
    {
        while (line[i] != '.')
            i++;
        g->spray_path = ft_strdup (&line[i]);
    }
}

void       ft_path_new(char *line, s_game *g)
{
    int i;

    i = 0;
    if (line[0] == 'N')
    {
        while (line[i] != '.')
            i++;
        g->n_path = ft_strdup(&line[i]);
    }
    else if (line[0] == 'W')
    {
        while (line[i] != '.')
            i++;
        g->w_path = ft_strdup(&line[i]);
    }
    else if (line[0] == 'E')
    {
        while (line[i] != '.')
            i++;
        g->e_path = ft_strdup(&line[i]);
    }
    else if (line[0] == 'F' && line[1] == 'T')
    {
        while (line[i] != '.')
            i++;
        g->f_path = ft_strdup(&line[i]);
        g->f.texturefloor = 1;
    }
}

void       ft_path_color(char *line, s_game *g)
{
    int i;
    int r;
    int gr;
    int b;
    i = 0;

    if (line[0] == 'F' && line[1] != 'T')
    {
        i++;
         while (line[i] == ' ')
            i++;
        r = ft_atoi(&line[i]);
        while (ft_isdigit(line[i]))
            i++;
        i++;
        gr = ft_atoi(&line[i]);
        while (ft_isdigit(line[i]))
            i++;
        i++;
        b = ft_atoi(&line[i]);
        g->f_color = r * 65536 + gr * 256 + b;
   }
   else if (line[0] == 'C')
   {
        i++;
         while (line[i] == ' ')
            i++;
        r = ft_atoi(&line[i]);
        while (ft_isdigit(line[i]))
            i++;
        i++;
        gr = ft_atoi(&line[i]);
        while (ft_isdigit(line[i]))
            i++;
        i++;
        b = ft_atoi(&line[i]); 
        g->c_color = r * 65536 + gr * 256 + b;
   }
}
void       ft_screensize(s_game *g,char *line)
{
    int i;

    i = 1;
    while (line[i] == ' ')
        i++;
    g->mapwidth = ft_atoi(&line[i]);
    while (ft_isdigit(line[i]))
        i++;
    g->mapheight = ft_atoi(&line[i]); 
}

void        ft_check_error(s_game *g)
{
    if (g->mapwidth > 1280 || g->mapwidth < 200)
        g->mapwidth = 720;
    if (g->mapheight > 720 || g->mapheight < 200)
        g->mapheight = 480;
    if (!(g->f_color))
        ft_error("Error\nFloor Color not asigned\n", g);
    if (!(g->c_color)&& g->f.texturefloor == 0)
        ft_error("Error\nCeiling Color not asigned\n", g);
}
void       ft_read_map(char *file, s_game *g)
{
    char *line;
    int     fd;
    int     ret;
    int     i;
    char    *map;
    char    *tmp;
    int     row;

    row = 0;
    ret = 1;
    map = ft_strdup("");
    fd = open(file, O_RDONLY);
    while (ret > 0)
    {
        ret = get_next_line(fd, &line);
        i = 0;
        if (line[i] == 'R')
            ft_screensize(g, line);
        else if (line[0] == 'S')
            ft_path_s(line, g);
        else if (line[0] == 'N' || line[0] == 'W' ||
                    line[0] == 'E' || (line[0] == 'F' && line[1] == 'T'))
            ft_path_new(line, g);
        else if (line[0] == 'F' || line [0] == 'C')
            ft_path_color(line, g);
        else if (ft_isdigit(line[0]))
        {
            tmp = ft_strjoin(map, line);
            free(map);
            map = ft_strjoin(tmp, "\n");
            row++;
        }
        free (line);
        line = NULL;   
    }
    ft_map(map, g, row);
    ft_check_error(g);
    free (map);
    g->zbuffer = malloc(sizeof(int *) * g->mapwidth);
}