/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aortega- <aortega-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 15:53:04 by aortega-          #+#    #+#             */
/*   Updated: 2020/02/24 17:29:37 by aortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_printline(int x, t_game *g)
{
	int y;

	y = 0;
	while (y++ < g->mapheight - 1)
	{
		if (y < g->drawstart)
			g->buff[(y * g->mapwidth) + x] = g->c_color;
		else if (y >= g->drawstart && y <= g->drawend)
		{
			g->texty = (int)g->textpos & (g->textheight - 1);
			g->textpos += g->step;
			g->color = g->texture[set_side(g)]
						[g->textheight * g->texty + g->textx];
			g->buff[(y * g->mapwidth + x)] = g->color;
		}
		else if (y > g->drawend)
			g->buff[(y * g->mapwidth) + x] = g->f_color;
	}
}

void	ft_step_sidedist(t_game *g)
{
	if (g->raydirx < 0)
	{
		g->stepx = -1;
		g->sidedistx = (g->posx - g->mapx) * g->deltadistx;
	}
	else
	{
		g->stepx = 1;
		g->sidedistx = (g->mapx + 1.0 - g->posx) * g->deltadistx;
	}
	if (g->raydiry < 0)
	{
		g->stepy = -1;
		g->sidedisty = (g->posy - g->mapy) * g->deltadisty;
	}
	else
	{
		g->stepy = 1;
		g->sidedisty = (g->mapy + 1.0 - g->posy) * g->deltadisty;
	}
}

void	ft_ddaloop(t_game *g)
{
	while (g->hit == 0)
	{
		if (g->sidedistx < g->sidedisty)
		{
			g->sidedistx += g->deltadistx;
			g->mapx += g->stepx;
			g->side = 0;
		}
		else
		{
			g->sidedisty += g->deltadisty;
			g->mapy += g->stepy;
			g->side = 1;
		}
		if (g->worldmap[g->mapx][g->mapy] > 0)
			g->hit = 1;
	}
	if (g->side == 0)
		g->perpwalldist = (g->mapx - g->posx + (1 - g->stepx) / 2)
						/ g->raydirx;
	else
		g->perpwalldist = (g->mapy - g->posy + (1 - g->stepy) / 2)
						/ g->raydiry;
}

void	ft_calculate_texture(t_game *g)
{
	g->textnum = g->worldmap[g->mapx][g->mapy] - 1;
	if (g->side == 0)
		g->wallx = g->posy + g->perpwalldist * g->raydiry;
	else
		g->wallx = g->posx + g->perpwalldist * g->raydirx;
	g->wallx -= floor(g->wallx);
	g->textx = (int)(g->wallx * (double)g->textwidth);
	if (g->side == 0 && g->raydirx > 0)
		g->textx = g->textwidth - g->textx - 1;
	if (g->side == 1 && g->raydiry < 0)
		g->textx = g->textwidth - g->textx - 1;
	g->step = 1.0 * g->textheight / g->lineheight;
	g->textpos = (g->drawstart - g->mapheight / 2 + g->lineheight / 2)
				* g->step;
}

void	ft_raycasting(t_game *g)
{
	int	x;

	x = 0;
	while (x++ < g->mapwidth)
	{
		g->camerax = 2 * x / (double)g->mapwidth - 1;
		g->raydirx = g->dirx + g->planex * g->camerax;
		g->raydiry = g->diry + g->planey * g->camerax;
		g->mapx = (int)g->posx;
		g->mapy = (int)g->posy;
		g->deltadistx = fabs(1 / g->raydirx);
		g->deltadisty = fabs(1 / g->raydiry);
		g->hit = 0;
		ft_step_sidedist(g);
		ft_ddaloop(g);
		g->lineheight = (int)(g->mapheight / g->perpwalldist);
		g->drawstart = -g->lineheight / 2 + g->mapheight / 2;
		if (g->drawstart < 0)
			g->drawstart = 0;
		g->drawend = g->lineheight / 2 + g->mapheight / 2;
		if (g->drawend >= g->mapheight)
			g->drawend = g->mapheight - 1;
		ft_calculate_texture(g);
		ft_printline(x, g);
	}
}
