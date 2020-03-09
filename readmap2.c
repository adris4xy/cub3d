/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readmap2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aortega- <aortega-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 11:07:36 by aortega-          #+#    #+#             */
/*   Updated: 2020/03/09 15:00:14 by aortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	ft_mapaux(char *map, int x, int y, t_game *g)
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
			ft_mapaux(map, x, y, g);
			map++;
			y++;
			if (*map == '\n')
				map++;
		}
		x++;
	}
	if (g->ray.posx == 0)
		ft_error("error, position invalid", g);
}
