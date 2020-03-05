/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aortega- <aortega-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 18:22:08 by egarcia-          #+#    #+#             */
/*   Updated: 2020/03/05 18:56:37 by aortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3d.h"

int		ft_ncol(char *map)
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

void	ft_colosemapaux()
{

}

int		ft_closemap(t_game *g, unsigned int x, unsigned int y)
{
	unsigned int j;
	unsigned int k;

	j = x - 1;
	if (g->worldmap[x][y] == 0)
	{
		if (x == 0 || y == 0 || x == (unsigned int)g->row
		|| y == (unsigned int)g->col)
			ft_error("map invalid border", g);
		while (j < x + 1)
		{
			k = y - 1;
			while (k < y + 1)
			{
				if (g->worldmap[j][k] != 0 && g->worldmap[j][k]
				!= 1 && g->worldmap[j][k] != 2)
					ft_error("map invalid check", g);
				k++;
			}
			j++;
		}
	}
	else if (g->worldmap[x][y] == 3)
	{
		while (j < x + 1)
		{
			k = y - 1;
			while (k < y + 1)
			{
				if (g->worldmap[j][k] == 0)
					ft_error("map invalid", g);
				k++;
			}
			j++;
		}
	}
	return (0);
}

void	ft_map(char *map, t_game *g, int row)
{
	int x;
	int y;

	g->worldmap = (int **)malloc(sizeof(int *) * row);
	g->col = ft_ncol(map);
	g->row = row;
	x = 0;
	while (x < row)
	{
		g->worldmap[x] = (int *)malloc(sizeof(int) * g->col);
		y = 0;
		while (y < g->col)
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
			map++;
			y++;
			if (*map == '\n')
				map++;
		}
		x++;
	}
}

void	ft_screensize(t_game *g, char *line)
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

void	ft_read_map(char *file, t_game *g)
{
	char	*line;
	int		fd;
	int		ret;
	int		i;
	char	*map;
	char	*tmp;
	int		row;

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
		else if (line[0] == 'F' || line[0] == 'C')
			ft_path_color(line, g);
		else if (ft_isdigit(line[0]) || line[0] == ' ')
		{
			tmp = ft_strjoin(map, line);
			free(map);
			map = ft_strjoin(tmp, "\n");
			row++;
			free(tmp);
		}
		free(line);
		line = NULL;
	}
	ft_map(map, g, row);
	ft_check_error(g);
	free(map);
	g->zbuffer = malloc(sizeof(int *) * g->mapwidth);
}
