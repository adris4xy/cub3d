/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aortega- <aortega-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 13:33:28 by egarcia-          #+#    #+#             */
/*   Updated: 2020/03/05 17:29:39 by aortega-         ###   ########.fr       */
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

void	key_movementws(t_game *g)
{
	t_ray	*p;
	t_keys	*k;

	k = &g->key;
	p = &g->ray;
	if (k->w)
	{
		if (g->worldmap[(int)(p->posx + p->dirx *
			k->movespeed)][(int)p->posy] == 0)
			p->posx += p->dirx * k->movespeed;
		if (g->worldmap[(int)p->posx][(int)(p->posy +
			p->diry * k->movespeed)] == 0)
			p->posy += p->diry * k->movespeed;
	}
	if (k->s)
	{
		if (g->worldmap[(int)(p->posx - p->dirx *
			k->movespeed)][(int)p->posy] == 0)
			p->posx -= p->dirx * k->movespeed;
		if (g->worldmap[(int)p->posx][(int)(p->posy -
			p->diry * k->movespeed)] == 0)
			p->posy -= p->diry * k->movespeed;
	}
}

void	key_movementad(t_game *g)
{
	t_ray	*p;
	t_keys	*k;

	k = &g->key;
	p = &g->ray;
	if (k->a)
	{
		if (g->worldmap[(int)(p->posx - p->diry *
			k->movespeed)][(int)p->posy] == 0)
			p->posx -= p->diry * k->movespeed;
		if (g->worldmap[(int)p->posx][(int)(p->posy +
			p->dirx * k->movespeed)] == 0)
			p->posy += p->dirx * k->movespeed;
	}
	if (k->d)
	{
		if (g->worldmap[(int)(p->posx + p->diry *
			k->movespeed)][(int)p->posy] == 0)
			p->posx += p->diry * k->movespeed;
		if (g->worldmap[(int)p->posx][(int)(p->posy -
			p->dirx * k->movespeed)] == 0)
			p->posy -= p->dirx * k->movespeed;
	}
}

void	key_rotation(t_game *g)
{
	t_ray	*p;
	t_keys	*k;

	k = &g->key;
	p = &g->ray;
	if (k->right)
	{
		p->old_dir = p->dirx;
		p->dirx = p->dirx * cos(-k->rtspd) - p->diry * sin(-k->rtspd);
		p->diry = p->old_dir * sin(-k->rtspd) + p->diry * cos(-k->rtspd);
		p->old_plane = p->plx;
		p->plx = p->plx * cos(-k->rtspd) - p->ply * sin(-k->rtspd);
		p->ply = p->old_plane * sin(-k->rtspd) + p->ply * cos(-k->rtspd);
	}
	if (k->left)
	{
		p->old_dir = p->dirx;
		p->dirx = p->dirx * cos(k->rtspd) - p->diry * sin(k->rtspd);
		p->diry = p->old_dir * sin(k->rtspd) + p->diry * cos(k->rtspd);
		p->old_plane = p->plx;
		p->plx = p->plx * cos(k->rtspd) - p->ply * sin(k->rtspd);
		p->ply = p->old_plane * sin(k->rtspd) + p->ply * cos(k->rtspd);
	}
}
