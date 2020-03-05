/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycastingaux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aortega- <aortega-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 16:44:03 by egarcia-          #+#    #+#             */
/*   Updated: 2020/03/05 16:12:51 by aortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_raygroupaux0(t_game *g, int x)
{
	g->ray.camerax = 2 * x / (double)g->mapwidth - 1;
	g->ray.raydirx = g->ray.dirx + g->ray.plx * g->ray.camerax;
	g->ray.raydiry = g->ray.diry + g->ray.ply * g->ray.camerax;
	g->ray.mapx = (int)g->ray.posx;
	g->ray.mapy = (int)g->ray.posy;
	ft_rayaux1(g);
	ft_rayaux2(g);
}

void	ft_rayaux1(t_game *g)
{
	g->ray.deltadistx = fabs(1 / g->ray.raydirx);
	g->ray.deltadisty = fabs(1 / g->ray.raydiry);
	g->ray.hit = 0;
	if (g->ray.raydirx < 0)
	{
		g->ray.stepx = -1;
		g->ray.sidedistx = (g->ray.posx - g->ray.mapx) * g->ray.deltadistx;
	}
	else
	{
		g->ray.stepx = 1;
		g->ray.sidedistx = (g->ray.mapx + 1.0 - g->ray.posx)
			* g->ray.deltadistx;
	}
	if (g->ray.raydiry < 0)
	{
		g->ray.stepy = -1;
		g->ray.sidedisty = (g->ray.posy - g->ray.mapy) * g->ray.deltadisty;
	}
	else
	{
		g->ray.stepy = 1;
		g->ray.sidedisty = (g->ray.mapy + 1.0 - g->ray.posy)
			* g->ray.deltadisty;
	}
}

void	ft_rayaux2(t_game *g)
{
	while (g->ray.hit == 0)
	{
		if (g->ray.sidedistx < g->ray.sidedisty)
		{
			g->ray.sidedistx += g->ray.deltadistx;
			g->ray.mapx += g->ray.stepx;
			g->ray.side = 0;
		}
		else
		{
			g->ray.sidedisty += g->ray.deltadisty;
			g->ray.mapy += g->ray.stepy;
			g->ray.side = 1;
		}
		if (g->worldmap[g->ray.mapx][g->ray.mapy] == 2 && g->selector == 1)
			g->boolean = 1;
		if (g->worldmap[g->ray.mapx][g->ray.mapy] == 1)
			g->ray.hit = 1;
	}
}

void	ft_rayaux3(t_game *g, int textpath)
{
	if (g->ray.side == 0)
		g->ray.perpwalldist = (g->ray.mapx - g->ray.posx +
			(1 - g->ray.stepx) / 2) / g->ray.raydirx;
	else
		g->ray.perpwalldist = (g->ray.mapy - g->ray.posy +
			(1 - g->ray.stepy) / 2) / g->ray.raydiry;
	g->ray.lineheight = (int)(g->mapheight / g->ray.perpwalldist);
	g->ren.drawstart = -g->ray.lineheight / 2 + g->mapheight / 2;
	if (g->ren.drawstart < 0)
		g->ren.drawstart = 0;
	g->ren.drawend = g->ray.lineheight / 2 + g->mapheight / 2;
	if (g->ren.drawend >= (int)g->mapheight)
		g->ren.drawend = g->mapheight - 1;
	g->ray.texnum = g->worldmap[g->ray.mapx][g->ray.mapy] - 1;
	if (g->ray.side == 0)
		g->ray.wallx = g->ray.posy + g->ray.perpwalldist * g->ray.raydiry;
	else
		g->ray.wallx = g->ray.posx + g->ray.perpwalldist * g->ray.raydirx;
	g->ray.wallx -= floor((g->ray.wallx));
	g->ray.texx = (int)(g->ray.wallx * (double)g->tex[textpath].textwidth);
	if (g->ray.side == 0 && g->ray.raydirx > 0)
		g->ray.texx = g->tex[textpath].textwidth - g->ray.texx - 1;
	if (g->ray.side == 1 && g->ray.raydiry < 0)
		g->ray.texx = g->tex[textpath].textwidth - g->ray.texx - 1;
}

void	ft_rayaux4(t_game *g, int x, int y, int textpath)
{
	if (y < g->ren.drawstart)
		g->buff[(y * g->mapwidth) + x] = g->c_color;
	else if (y >= g->ren.drawstart && y <= g->ren.drawend)
	{
		g->ray.texy = (int)g->ray.texpos & (g->tex[textpath].textheight - 1);
		g->ray.texpos += g->ray.step;
		g->ray.color = g->tex[textpath].texture[g->tex[textpath].textheight
				* g->ray.texy + g->ray.texx];
		if (g->ray.side == 1)
			g->ray.color = (g->ray.color >> 1) & 8355711;
		g->buff[(y * g->mapwidth + x)] = g->ray.color;
	}
	else if (y > g->ren.drawend && g->f.texturefloor == 0)
		g->buff[(y * g->mapwidth) + x] = g->f_color;
}
