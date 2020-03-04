/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aortega- <aortega-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 13:03:33 by egarcia-          #+#    #+#             */
/*   Updated: 2020/03/04 15:49:57 by aortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int    ft_master(t_game *g)
{
   	deal_key(g);
	g->selector = 0; 
	ft_raycasting(g);
	if (g->selector == 0)
	{
		shortsprites(g);
		spray_raycasting(g);
		g->selector = 1;
		ft_raycasting(g);
	}
	mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, g->ren.dataimg , 0, 0);
	return (1);
}

void	init_data(t_game *g)
{
    g->ray.planex = 0;
    g->key.movespeed = 0.1;
	g->key.rotspeed = 0.05;
    g->f_path = NULL;
    g->f.texturefloor = 0;
    g->n_spray = 0;
    g->boolean = 0;
    g->key.right = 0;
    g->key.left = 0;
	g->key.a = 0;
	g->key.s = 0;
	g->key.d = 0;
	g->key.w = 0;
	g->key.esc = 0;
}

void        ft_check_error(t_game *g)
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

int     main(int argc, char **argv)
{
    t_game g;
    
    init_data(&g);
    if (argc == 2)
    {
        ft_read_map(argv[1], &g);
        g.mlx_ptr = mlx_init();
        g.win_ptr = mlx_new_window(g.mlx_ptr, g.mapwidth, g.mapheight, "cub3d");
        g.ren.dataimg = mlx_new_image(g.mlx_ptr, g.mapwidth, g.mapheight);
        get_textures(&g);
		get_texturesaux(&g);
        g.buff = (int *)mlx_get_data_addr(g.ren.dataimg, &g.ren.bytes_per_pixel, &g.ren.size_line, &g.ren.endian);
        mlx_hook(g.win_ptr, 2, 1, key_pressed, &g.key);
        mlx_hook(g.win_ptr, 3, 1, key_released, &g.key);
        mlx_hook(g.win_ptr, 17, 1, close_game, (void *)&g);
        mlx_loop_hook (g.mlx_ptr, ft_master, &g);
        mlx_loop(g.mlx_ptr);
    }
    else
        ft_error("error invalid arguments\n", &g);
    return (0);
}