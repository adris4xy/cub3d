/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aortega- <aortega-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 18:32:29 by aortega-          #+#    #+#             */
/*   Updated: 2020/03/09 15:50:16 by aortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int		set_side(t_game *g)
{
	if (g->ray.posx > (double)g->ray.mapx)
	{
		if (g->ray.side == 1 && g->ray.posy > g->ray.mapy)
			return (2);
		else if (g->ray.side == 1 && g->ray.posy < g->ray.mapy)
			return (3);
		else
			return (0);
	}
	else
	{
		if (g->ray.side == 1 && g->ray.posy > g->ray.mapy)
			return (2);
		else if (g->ray.side == 1 && g->ray.posy < g->ray.mapy)
			return (3);
		else
			return (1);
	}
}

void	get_textures(t_game *g)
{
	if (!(g->texptr = mlx_xpm_file_to_image(g->mlx_ptr, g->n_path,
			&g->tex[0].textwidth, &g->tex[0].textheight)))
		ft_error("ERROR, N_PATH WRONG", g);
	g->tex[0].texture = (int *)mlx_get_data_addr(g->texptr,
			&g->tex[0].byte_per_pixel, &g->tex[0].size_line, &g->tex[0].endian);
	if (!(g->texptr = mlx_xpm_file_to_image(g->mlx_ptr, g->so_path,
			&g->tex[1].textwidth, &g->tex[1].textheight)))
		ft_error("ERROR, SO_PATH WRONG", g);
	g->tex[1].texture = (int *)mlx_get_data_addr(g->texptr,
			&g->tex[1].byte_per_pixel, &g->tex[1].size_line, &g->tex[1].endian);
	if (!(g->texptr = mlx_xpm_file_to_image(g->mlx_ptr, g->w_path,
			&g->tex[2].textwidth, &g->tex[2].textheight)))
		ft_error("ERROR, W_PATH WRONG", g);
	g->tex[2].texture = (int *)mlx_get_data_addr(g->texptr,
			&g->tex[2].byte_per_pixel, &g->tex[2].size_line, &g->tex[2].endian);
	if (!(g->texptr = mlx_xpm_file_to_image(g->mlx_ptr, g->e_path,
			&g->tex[3].textwidth, &g->tex[3].textheight)))
		ft_error("ERROR, EA_PATH WRONG", g);
	g->tex[3].texture = (int *)mlx_get_data_addr(g->texptr,
			&g->tex[3].byte_per_pixel, &g->tex[3].size_line, &g->tex[3].endian);
}

void	get_texturesaux(t_game *g)
{
	if (!(g->texptr = mlx_xpm_file_to_image(g->mlx_ptr, g->spray_path,
			&g->tex[5].textwidth, &g->tex[5].textheight)))
		ft_error("ERROR, SPRITE WRONG", g);
	g->tex[5].texture = (int *)mlx_get_data_addr(g->texptr,
		&g->tex[5].byte_per_pixel, &g->tex[5].size_line, &g->tex[5].endian);
}

void	ft_error(char *s, t_game *g)
{
	write(2, "\033[1;31m", 8);
	write(2, s, ft_strlen(s));
	g->buff = 0;
	exit(-1);
}

int		close_game(t_game *g)
{
	g->buff = 0;
	system("leaks cub3d");
	exit(0);
	return (0);
}
