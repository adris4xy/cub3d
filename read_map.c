/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aortega- <aortega-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 17:35:04 by aortega-          #+#    #+#             */
/*   Updated: 2020/02/26 11:23:18 by aortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "cub3d.h"

void	ft_set_start(int x, int y, char *map, t_game *g)
{
	g->posx = x;
	g->posy = y;
	if (*map == 'N')
	{
		g->dirx = -1;
		g->planey = 0.66;
	}
	else if (*map == 'S')
	{
		g->dirx = 1;
		g->planey = -0.66;
	}
	else if (*map == 'E')
	{
		g->diry = 1;
		g->planex = 0.66;
	}
	else if (*map == 'W')
	{
		g->diry = -1;
		g->planex = -0.66;
	}
}

void	ft_mapaux(t_game *g, int size, t_readmap *struc, int j)
{
	int i;

	i = 0;
	while (i < struc->row)
	{
		g->worldmap[i] = (int *)malloc(sizeof(int) * size);
		j = 0;
		while (j < size)
		{
			if (ft_isdigit(*struc->map))
				g->worldmap[i][j] = *struc->map - '0';
			else
			{
				ft_set_start(i, j, struc->map, g);
				g->worldmap[i][j] = 0;
			}
			struc->map += 2;
			j++;
		}
		g->worldmap[i][j] = 0;
		i++;
	}
}

void	ft_map(char *map, t_game *g, t_readmap *struc)
{
	int	i;
	int	size;
	int	j;

	j = 0;
	size = 0;
	i = 0;
	g->worldmap = (int **)malloc(sizeof(int *) * struc->row);
	while (map[i] != '\n')
	{
		if (ft_isdigit(map[i]))
			size++;
		i++;
	}
	ft_mapaux(g, size, struc, j);
}

void	ft_read_mapaux(t_readmap *struc, t_game *g)
{
	struc->i = 0;
	if (struc->line[struc->i] == 'R')
	{
		struc->i++;
		g->mapwidth = ft_atoi(&struc->line[2]);
		while (struc->line[struc->i] == ' ')
			struc->i++;
		while (ft_isdigit(struc->line[struc->i]))
			struc->i++;
		g->mapheight = ft_atoi(&struc->line[struc->i]);
	}
	else if (struc->line[0] == 'S')
		ft_path_s(struc->line, g);
	else if (struc->line[0] == 'N' ||
			struc->line[0] == 'W' || struc->line[0] == 'E')
		ft_path_new(struc->line, g);
	else if (struc->line[0] == 'F' || struc->line[0] == 'C')
		ft_path_color(struc->line, g, struc);
	else if (ft_isdigit(struc->line[0]))
	{
		struc->tmp = ft_strjoin(struc->map, struc->line);
		free(struc->map);
		struc->map = ft_strjoin(struc->tmp, "\n");
		struc->row++;
	}
}

void	ft_read_map(char *file, t_game *g)
{
	t_readmap	struc;
	int			fd;

	struc.row = 0;
	struc.ret = 1;
	struc.map = ft_strdup("");
	fd = open(file, O_RDONLY);
	while (struc.ret > 0)
	{
		struc.ret = get_next_line(fd, &struc.line);
		ft_read_mapaux(&struc, g);
		free(struc.line);
		struc.line = NULL;
	}
	ft_map(struc.map, g, &struc);
}
