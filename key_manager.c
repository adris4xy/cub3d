/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egarcia- <egarcia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 13:33:28 by egarcia-          #+#    #+#             */
/*   Updated: 2020/02/28 19:34:40 by egarcia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int    key_pressed(int key, s_keys *k)
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
	else if (key == 257)
		k->run = 1;
	else if (key == 53)
		k->esc = 1;
	return (0);
}

int    key_released(int key, s_keys *k)
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
		k->esc = 0;
	return (0);
}

void	key_movement(s_game *g)
{
	if (g->key.w)
	{
		if (g->worldmap[(int)(g->ray.posx + g->ray.dirx * g->key.movespeed)][(int)g->ray.posy] == 0)
			g->ray.posx += g->ray.dirx * g->key.movespeed;
		if (g->worldmap[(int)g->ray.posx][(int)(g->ray.posy + g->ray.diry * g->key.movespeed)] == 0)
			g->ray.posy += g->ray.diry * g->key.movespeed; 
	}
	if (g->key.s)
	{
		if (g->worldmap[(int)(g->ray.posx - g->ray.dirx * g->key.movespeed)][(int)g->ray.posy] == 0)
			g->ray.posx -= g->ray.dirx * g->key.movespeed;
		if (g->worldmap[(int)g->ray.posx][(int)(g->ray.posy - g->ray.diry * g->key.movespeed)] == 0)
			g->ray.posy -= g->ray.diry * g->key.movespeed; 
	}
	if (g->key.a)
	{
		if (g->worldmap[(int)(g->ray.posx - g->ray.diry * g->key.movespeed)][(int)g->ray.posy] == 0)
			g->ray.posx -= g->ray.diry * g->key.movespeed;
		if (g->worldmap[(int)g->ray.posx][(int)(g->ray.posy + g->ray.dirx * g->key.movespeed)] == 0)
			g->ray.posy += g->ray.dirx * g->key.movespeed; 
	}
	if (g->key.d)
	{
		if (g->worldmap[(int)(g->ray.posx + g->ray.diry * g->key.movespeed)][(int)g->ray.posy] == 0)
			g->ray.posx += g->ray.diry * g->key.movespeed;
		if (g->worldmap[(int)g->ray.posx][(int)(g->ray.posy - g->ray.dirx * g->key.movespeed)] == 0)
			g->ray.posy -= g->ray.dirx * g->key.movespeed; 
	}	
}

void	key_rotation(s_game *g)
{
	if (g->key.right)
	{
		g->ray.old_dir = g->ray.dirx;
		g->ray.dirx = g->ray.dirx * cos(-g->key.rotspeed) - g->ray.diry * sin(-g->key.rotspeed);
		g->ray.diry = g->ray.old_dir * sin(-g->key.rotspeed) + g->ray.diry * cos(-g->key.rotspeed);
		g->ray.old_plane = g->ray.planex;
		g->ray.planex = g->ray.planex * cos(-g->key.rotspeed) - g->ray.planey * sin(-g->key.rotspeed);
		g->ray.planey = g->ray.old_plane * sin(-g->key.rotspeed) + g->ray.planey * cos(-g->key.rotspeed);
	}
	if (g->key.left)
	{
		g->ray.old_dir = g->ray.dirx;
		g->ray.dirx = g->ray.dirx * cos(g->key.rotspeed) - g->ray.diry * sin(g->key.rotspeed);
		g->ray.diry = g->ray.old_dir * sin(g->key.rotspeed) + g->ray.diry * cos(g->key.rotspeed);
		g->ray.old_plane = g->ray.planex;
		g->ray.planex = g->ray.planex * cos(g->key.rotspeed) - g->ray.planey * sin(g->key.rotspeed);
		g->ray.planey = g->ray.old_plane * sin(g->key.rotspeed) + g->ray.planey * cos(g->key.rotspeed);
	}
}

void 	key_bonus(s_game *g)
{
	if (g->key.run)
		g->key.movespeed = 0.1;
	else if (!(g->key.run))
		g->key.movespeed = 0.06;
	if (g->key.esc)
		exit(-1);

}
int     deal_key(s_game *g)
{
	key_movement(g);
	key_rotation(g);
	key_bonus(g);
	return (0);
}