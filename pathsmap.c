/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathsmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aortega- <aortega-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 12:15:05 by aortega-          #+#    #+#             */
/*   Updated: 2020/03/05 16:14:52 by aortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_set_start(int x, int y, char *map, t_game *g)
{
	g->ray.posx = x + 0.5;
	g->ray.posy = y + 0.5;
	if (*map == 'N')
	{
		g->ray.dirx = -1;
		g->ray.ply = 0.66;
	}
	else if (*map == 'S')
	{
		g->ray.dirx = 1;
		g->ray.ply = -0.66;
	}
	else if (*map == 'E')
	{
		g->ray.dirx = 0;
		g->ray.ply = 0.66;
	}
	else if (*map == 'W')
	{
		g->ray.dirx = 0;
		g->ray.ply = -0.66;
	}
	else
		ft_error("ERROR\n INIT ZONE DOES NOT MATCH", g);
}

void	ft_path_s(char *line, t_game *g)
{
	int	i;

	i = 0;
	if (line[1] == 'O')
	{
		while (line[i] != '.')
			i++;
		g->so_path = ft_strdup(&line[i]);
	}
	else if (line[1] == ' ')
	{
		while (line[i] != '.')
			i++;
		g->spray_path = ft_strdup(&line[i]);
	}
}

void	ft_path_new(char *line, t_game *g)
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
}

void	ft_path_coloraux(char *line, int i, t_game *g)
{
	while (line[i] == ' ')
		i++;
	g->r = ft_atoi(&line[i]);
	while (ft_isdigit(line[i]))
		i++;
	i++;
	g->gr = ft_atoi(&line[i]);
	while (ft_isdigit(line[i]))
		i++;
	i++;
	g->b = ft_atoi(&line[i]);
}

void	ft_path_color(char *line, t_game *g)
{
	int i;

	i = 0;
	if (line[0] == 'F')
	{
		i++;
		ft_path_coloraux(line, i, g);
		g->f_color = g->r * 65536 + g->gr * 256 + g->b;
	}
	else if (line[0] == 'C')
	{
		i++;
		ft_path_coloraux(line, i, g);
		g->c_color = g->r * 65536 + g->gr * 256 + g->b;
	}
}
