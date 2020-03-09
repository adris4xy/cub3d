/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aortega- <aortega-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 18:22:08 by egarcia-          #+#    #+#             */
/*   Updated: 2020/03/09 15:20:36 by aortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_closemapaux(t_game *g, unsigned int x, unsigned int y)
{
	if (x == 0 || y == 0 || x == (unsigned int)g->row - 1
	|| y == (unsigned int)g->col - 1)
		ft_error("map invalid border", g);
	while (g->j < x + 1)
	{
		g->k = y - 1;
		while (g->k < y + 1)
		{
			if (g->worldmap[g->j][g->k] != 0 && g->worldmap[g->j][g->k]
			!= 1 && g->worldmap[g->j][g->k] != 2)
				ft_error("map invalid check", g);
			g->k++;
		}
		g->j++;
	}
}

int		ft_closemap(t_game *g, unsigned int x, unsigned int y)
{
	g->j = x - 1;
	if (g->worldmap[x][y] == 0)
	{
		ft_closemapaux(g, x, y);
	}
	else if (g->worldmap[x][y] == 3)
	{
		while (g->j < x + 1)
		{
			g->k = y - 1;
			while (g->k < y + 1)
			{
				if (g->worldmap[g->j][g->k] == 0)
					ft_error("map invalid", g);
				g->k++;
			}
			g->j++;
		}
	}
	return (0);
}

void	ft_read_mapaux1(char *line, int *row, t_game *g)
{
	g->tmp = ft_strjoin(g->map, line);
	free(g->map);
	g->map = ft_strjoin(g->tmp, "\n");
	*row = *row + 1;
	free(g->tmp);
}

void	ft_read_mapaux(t_game *g, int *row, int fd)
{
	int		i;
	int		ret;
	char	*line;

	ret = 1;
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
			ft_read_mapaux1(line, row, g);
		free(line);
		line = NULL;
	}
}

void	ft_read_map(char *file, t_game *g)
{
	int		fd;
	int		row;

	row = 0;
	g->map = ft_strdup("");
	fd = open(file, O_RDONLY);
	ft_read_mapaux(g, &row, fd);
	ft_map(g->map, g, row);
	ft_check_error(g);
	free(g->map);
	g->zbuffer = malloc(sizeof(int *) * g->mapwidth);
}
