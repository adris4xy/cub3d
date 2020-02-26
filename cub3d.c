/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aortega- <aortega-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 15:55:09 by aortega-          #+#    #+#             */
/*   Updated: 2020/02/26 11:22:40 by aortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		set_side(t_game *g)
{
	if (g->posx > (double)g->mapx)
	{
		if (g->side == 1 && g->posy > g->mapy)
			return (2);
		else if (g->side == 1 && g->posy < g->mapy)
			return (3);
		else
			return (0);
	}
	else
	{
		if (g->side == 1 && g->posy > g->mapy)
			return (2);
		else if (g->side == 1 && g->posy < g->mapy)
			return (3);
		else
			return (1);
	}
}

void	get_textures(t_game *g)
{
	g->texptr = mlx_xpm_file_to_image(g->mlx_ptr, g->n_path,
				&g->textwidth, &g->textheight);
	g->texture[0] = (int *)mlx_get_data_addr(g->texptr,
				&g->bytes_per_pixel, &g->size_line, &g->endian);
	g->texptr = mlx_xpm_file_to_image(g->mlx_ptr, g->so_path,
				&g->textwidth, &g->textheight);
	g->texture[1] = (int *)mlx_get_data_addr(g->texptr,
				&g->bytes_per_pixel, &g->size_line, &g->endian);
	g->texptr = mlx_xpm_file_to_image(g->mlx_ptr, g->e_path,
				&g->textwidth, &g->textheight);
	g->texture[2] = (int *)mlx_get_data_addr(g->texptr,
				&g->bytes_per_pixel, &g->size_line, &g->endian);
	g->texptr = mlx_xpm_file_to_image(g->mlx_ptr, g->w_path,
				&g->textwidth, &g->textheight);
	g->texture[3] = (int *)mlx_get_data_addr(g->texptr,
				&g->bytes_per_pixel, &g->size_line, &g->endian);
}

int		ft_master(t_game *g)
{
	g->movespeed = 0.05;
	g->rotspeed = 0.05;
	dealws_key(g);
	dealad_key(g);
	dealrl_key(g);
	ft_raycasting(g);
	mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, g->dataimg, 0, 0);
	return (1);
}

void	init_data(t_game *g)
{
	g->posx = 5;
	g->posy = 5;
	//g->planey = 0.66;
	g->w = 0;
	g->s = 0;
	g->a = 0;
	g->d = 0;
}

int		main(int argc, char **argv)
{
	t_game	g;

	if (argc != 2)
		return (0);
	init_data(&g);
	ft_read_map(argv[1], &g);
	g.mlx_ptr = mlx_init();
	g.win_ptr = mlx_new_window(g.mlx_ptr, g.mapwidth, g.mapheight, "cub3d");
	g.dataimg = mlx_new_image(g.mlx_ptr, g.mapwidth, g.mapheight);
	g.buff = (int *)mlx_get_data_addr(g.dataimg,
			&g.bytes_per_pixel, &g.size_line, &g.endian);
	get_textures(&g);
	mlx_hook(g.win_ptr, 2, 1, key_pressed, &g);
	mlx_hook(g.win_ptr, 3, 1, key_released, &g);
	mlx_loop_hook(g.mlx_ptr, ft_master, &g);
	mlx_hook(g.win_ptr, 17, 0, ft_exit, &g);
	mlx_loop(g.mlx_ptr);
	return (0);
}
