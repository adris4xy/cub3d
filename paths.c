/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aortega- <aortega-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 18:31:41 by aortega-          #+#    #+#             */
/*   Updated: 2020/02/24 19:00:38 by aortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	ft_pathcoloraux(int i, t_game *g, t_readmap *struc)
{
	int r;
	int gr;
	int b;

	while (struc->line[i] == ' ')
		i++;
	r = ft_atoi(&struc->line[i]);
	while (ft_isdigit(struc->line[i]))
		i++;
	i++;
	gr = ft_atoi(&struc->line[i]);
	while (ft_isdigit(struc->line[i]))
		i++;
	i++;
	b = ft_atoi(&struc->line[i]);
	if (*struc->line == 'F')
		g->f_color = r * 65536 + gr * 256 + b;
	else
		g->c_color = r * 65536 + gr * 256 + b;
}

void	ft_path_color(char *line, t_game *g, t_readmap *struc)
{
	int i;

	i = 0;
	if (line[0] == 'F')
	{
		i++;
		ft_pathcoloraux(i, g, struc);
	}
	else if (line[0] == 'C')
	{
		i++;
		ft_pathcoloraux(i, g, struc);
	}
}
