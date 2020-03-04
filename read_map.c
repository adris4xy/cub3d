/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aortega- <aortega-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 18:22:08 by egarcia-          #+#    #+#             */
/*   Updated: 2020/03/04 19:28:57 by aortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3d.h"

int         ft_ncol(char *map)
{
    int col;

    col = 0;
    while (*map != '\n')
    {
        col++;
        map++;
    }
    return (col);
}

void	ft_midisclose(t_game *g , int x)
{
	int start;
	int end;

	start = 0;
	end = g->col;
	while (start < g->col && g->worldmap[x][start] != 0)
	{
		if (g->worldmap[x][start] == 1)
			break;
		start++;
	}
	while (end > 0 && g->worldmap[x][end] != 0)
	{
		if (g->worldmap[x][end] == 1)
			break;
		end--;
	}
	if (end == start || start == g->col)
		ft_error("error mid is not close" , g);
}
int		ft_checknumber(t_game *g , int x)
{
	int y;
	int border;

	border = 0;
	y = 0;
	while(y < g->col - 1)
	{
		if (g->worldmap[x][y] == 1 || g->worldmap[x][y] == 3)
		{
			y++;
			if (g->worldmap[x][y] == 1)
				border = 1;
		}
		else
			break;
	}
	if (y == g->col - 1 && border == 1)
		return (1);
	return (0);

}

void		ft_checktop(t_game *g, int x)
{
	int y;
	int z;

	y = 0;
	while (y < g->col)
	{
		if (g->worldmap[x][y] == 3)
		{
			
			z = x;
			while (g->worldmap[z][y] == 3 && z < g->row - 1)
				z++;
			if (g->worldmap[z][y] == 0 || g->worldmap[z][y] == 2)
				ft_error("Error map not closed", g);
		}
		y++;
	}
}

void		ft_checkbot(t_game *g, int x)
{
	int y;
	int z;

	y = 0;
	
	while (y < g->col - 1)
	{
		printf("%d ", g->worldmap[z][y]);
		if (g->worldmap[x][y] == 3)
		{
			
			z = x;
			while (g->worldmap[z][y] == 3 && z > 0)
				z--;
			if (g->worldmap[z][y] == 0 || g->worldmap[z][y] == 2)
				ft_error("Error map not closed", g);
		}
		y++;
	}
}
void		ft_checkerror(t_game *g)
{
	int x;
	int y;
	int first;
	int last;

	first = 0;
	last = 0;
	x = 0;
	y = 0;
	while (x < g->row - 1)
	{
		
			//printf("entro aqui");
		if (first == 0  && ft_checknumber(g , x))
		{	
			ft_checktop(g , x);
			first = 1;
		}
		else if (first == 1)
			ft_midisclose(g, x);
		
		//printf("%d", x);
		if (first == 1 && ft_checknumber(g , x))
		{
			ft_checkbot(g, x);
			last = 1;
		}
		x++;
	}
	//printf("\n%d", first);
	if (first == 0 || last == 0)
	  ft_error("Las puertas estna abiertas!!!!",g);
}

void        ft_map(char *map, t_game *g, int row)
{
    int x;
    int col;
    int y;

    g->worldmap = (int **)malloc(sizeof(int *) * row);
    g->col = ft_ncol(map);
	col = g->col;
	g->row = row;
    x = 0;
	printf("N COL:%d\n", col);
    while (x < row)
    {
        //if (*map != '1')
        //ft_error("ERROR\n MAP IS NOT CLOSED\n", g);
        g->worldmap[x] = (int *)malloc(sizeof(int) * col);
        y = 0;
        while (y < col)
        {
            
            if (ft_isdigit(*map))
            {
                g->worldmap[x][y] = *map - '0';
                if (*map == '2')
                    ft_isspray(g, x, y);
            }
			else if (*map == ' ')
				g->worldmap[x][y] = 3;
            else if (*map == 'W' || *map == 'N' || *map == 'S' || *map == 'E')
            {
                ft_set_start(x, y, map, g);
                g->worldmap[x][y] = 0;
            }
			printf("%d ", g->worldmap[x][y]);
            map++;
            y++;
        }
		if (*map == '\n')
			map++;
		printf("\n");
        x++;
    }
	ft_checkerror(g);
}

void       ft_screensize(t_game *g,char *line)
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

void       ft_read_map(char *file, t_game *g)
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
        else if (ft_isdigit(line[0]) || line[0] == ' ')
        {
            tmp = ft_strjoin(map, line);
            free(map);
            map = ft_strjoin(tmp, "\n");
            row++;
			free(tmp);
        }
        free (line);
        line = NULL;   
    }
    ft_map(map, g, row);
    ft_check_error(g);
    free (map);
    g->zbuffer = malloc(sizeof(int *) * g->mapwidth);
}