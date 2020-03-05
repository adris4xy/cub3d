/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aortega- <aortega-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 13:33:28 by egarcia-          #+#    #+#             */
/*   Updated: 2020/03/05 16:19:56 by aortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		key_pressed(int key, t_keys *k)
{
	if (key == 0)
		k->a = 1;
	else if (key == 1)
		k->s = 1;
	else if (key == 2)
		k->d = 1;
	else if (key == 13)
		k->w = 1;
	else if (key == 123)
		k->left = 1;
	else if (key == 124)
		k->right = 1;
	return (0);
}

int		key_released(int key, t_keys *k, t_game *g)
{
	if (key == 0)
		k->a = 0;
	else if (key == 1)
		k->s = 0;
	else if (key == 2)
		k->d = 0;
	else if (key == 13)
		k->w = 0;
	else if (key == 123)
		k->left = 0;
	else if (key == 124)
		k->right = 0;
	else if (key == 257)
		k->run = 0;
	else if (key == 53)
		return (close_game(g));
	return (0);
}

void	key_movement(t_game *g)
{
	if (g->key.w)
	{
		if (g->worldmap[(int)(g->ray.posx + g->ray.dirx *
			g->key.movespeed)][(int)g->ray.posy] == 0)
			g->ray.posx += g->ray.dirx * g->key.movespeed;
		if (g->worldmap[(int)g->ray.posx][(int)(g->ray.posy +
			g->ray.diry * g->key.movespeed)] == 0)
			g->ray.posy += g->ray.diry * g->key.movespeed;
	}
	if (g->key.s)
	{
		if (g->worldmap[(int)(g->ray.posx - g->ray.dirx *
			g->key.movespeed)][(int)g->ray.posy] == 0)
			g->ray.posx -= g->ray.dirx * g->key.movespeed;
		if (g->worldmap[(int)g->ray.posx][(int)(g->ray.posy -
			g->ray.diry * g->key.movespeed)] == 0)
			g->ray.posy -= g->ray.diry * g->key.movespeed;
	}
	if (g->key.a)
	{
		if (g->worldmap[(int)(g->ray.posx - g->ray.diry *
			g->key.movespeed)][(int)g->ray.posy] == 0)
			g->ray.posx -= g->ray.diry * g->key.movespeed;
		if (g->worldmap[(int)g->ray.posx][(int)(g->ray.posy +
			g->ray.dirx * g->key.movespeed)] == 0)
			g->ray.posy += g->ray.dirx * g->key.movespeed;
	}
	if (g->key.d)
	{
		if (g->worldmap[(int)(g->ray.posx + g->ray.diry *
			g->key.movespeed)][(int)g->ray.posy] == 0)
			g->ray.posx += g->ray.diry * g->key.movespeed;
		if (g->worldmap[(int)g->ray.posx][(int)(g->ray.posy -
			g->ray.dirx * g->key.movespeed)] == 0)
			g->ray.posy -= g->ray.dirx * g->key.movespeed;
	}
}

void	key_rotation(t_game *g)
{
	t_ray	*p;

	p = &g->ray;
	if (g->key.right)
	{
		g->ray.old_dir = g->ray.dirx;
		g->ray.dirx = g->ray.dirx * cos(-g->key.rtspd) - g->ray.diry * sin(-g->key.rtspd);
		g->ray.diry = g->ray.old_dir * sin(-g->key.rtspd) + g->ray.diry * cos(-g->key.rtspd);
		g->ray.old_plane = g->ray.plx;
		g->ray.plx = g->ray.plx * cos(-g->key.rtspd) - g->ray.ply * sin(-g->key.rtspd);
		g->ray.ply = g->ray.old_plane * sin(-g->key.rtspd) + g->ray.ply * cos(-g->key.rtspd);
	}
	if (g->key.left)
	{
		g->ray.old_dir = g->ray.dirx;
		g->ray.dirx = g->ray.dirx * cos(g->key.rtspd) - g->ray.diry * sin(g->key.rtspd);
		g->ray.diry = g->ray.old_dir * sin(g->key.rtspd) + g->ray.diry * cos(g->key.rtspd);
		g->ray.old_plane = g->ray.plx;
		g->ray.plx = g->ray.plx * cos(g->key.rtspd) - g->ray.ply * sin(g->key.rtspd);
		g->ray.ply = g->ray.old_plane * sin(g->key.rtspd) + g->ray.ply * cos(g->key.rtspd);
	}
}

int		deal_key(t_game *g)
{
	key_movement(g);
	key_rotation(g);
	return (0);
}
