/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aortega- <aortega-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 15:58:33 by aortega-          #+#    #+#             */
/*   Updated: 2020/02/24 16:39:28 by aortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		dealws_key(t_game *g)
{
	if (g->w)
	{
		if (g->worldmap[(int)(g->posx + g->dirx
			* g->movespeed)][(int)g->posy] == 0)
			g->posx += g->dirx * g->movespeed;
		if (g->worldmap[(int)g->posx][(int)(g->posy + g->diry
			* g->movespeed)] == 0)
			g->posy += g->diry * g->movespeed;
	}
	if (g->s)
	{
		if (g->worldmap[(int)(g->posx - g->dirx
			* g->movespeed)][(int)g->posy] == 0)
			g->posx -= g->dirx * g->movespeed;
		if (g->worldmap[(int)g->posx][(int)(g->posy - g->diry
			* g->movespeed)] == 0)
			g->posy -= g->diry * g->movespeed;
	}
	return (0);
}

int		dealad_key(t_game *g)
{
	if (g->a)
	{
		if (g->worldmap[(int)(g->posx - g->diry
			* g->movespeed)][(int)g->posy] == 0)
			g->posx -= g->diry * g->movespeed;
		if (g->worldmap[(int)g->posx][(int)(g->posy + g->dirx
			* g->movespeed)] == 0)
			g->posy += g->dirx * g->movespeed;
	}
	if (g->d)
	{
		if (g->worldmap[(int)(g->posx + g->diry
			* g->movespeed)][(int)g->posy] == 0)
			g->posx += g->diry * g->movespeed;
		if (g->worldmap[(int)g->posx][(int)(g->posy - g->dirx
			* g->movespeed)] == 0)
			g->posy -= g->dirx * g->movespeed;
	}
	return (0);
}

int		dealrl_key(t_game *g)
{
	if (g->right)
	{
		g->old_dir = g->dirx;
		g->dirx = g->dirx * cos(-g->rotspeed)
					- g->diry * sin(-g->rotspeed);
		g->diry = g->old_dir * sin(-g->rotspeed)
					+ g->diry * cos(-g->rotspeed);
		g->old_plane = g->planex;
		g->planex = g->planex * cos(-g->rotspeed)
					- g->planey * sin(-g->rotspeed);
		g->planey = g->old_plane * sin(-g->rotspeed)
					+ g->planey * cos(-g->rotspeed);
	}
	if (g->left)
	{
		g->old_dir = g->dirx;
		g->dirx = g->dirx * cos(g->rotspeed) - g->diry * sin(g->rotspeed);
		g->diry = g->old_dir * sin(g->rotspeed)
					+ g->diry * cos(g->rotspeed);
		g->old_plane = g->planex;
		g->planex = g->planex * cos(g->rotspeed) - g->planey * sin(g->rotspeed);
		g->planey = g->old_plane * sin(g->rotspeed)
					+ g->planey * cos(g->rotspeed);
	}
	return (0);
}

int		key_pressed(int key, t_game *g)
{
	if (key == 0)
		g->a = 1;
	else if (key == 1)
		g->s = 1;
	else if (key == 2)
		g->d = 1;
	else if (key == 13)
		g->w = 1;
	else if (key == 123)
		g->left = 1;
	else if (key == 124)
		g->right = 1;
	return (0);
}

int		key_released(int key, t_game *g)
{
	if (key == 0)
		g->a = 0;
	else if (key == 1)
		g->s = 0;
	else if (key == 2)
		g->d = 0;
	else if (key == 13)
		g->w = 0;
	else if (key == 123)
		g->left = 0;
	else if (key == 124)
		g->right = 0;
	return (0);
}
