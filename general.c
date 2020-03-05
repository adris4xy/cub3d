/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aortega- <aortega-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 15:51:38 by aortega-          #+#    #+#             */
/*   Updated: 2020/03/05 18:19:56 by aortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_raycasting(t_game *g)
{
	int		x;
	int		y;
	int		textpath;

	x = 0;
	while (x++ < g->mapwidth)
	{
		textpath = set_side(g);
		ft_raygroupaux0(g, x);
		if (g->boolean == 1 && g->selector == 1)
			continue;
		ft_rayaux3(g, textpath);
		g->ray.step = 1.0 * g->tex[textpath].textwidth / g->ray.lineheight;
		g->ray.texpos = (g->ren.drawstart - g->mapheight / 2 +
		g->ray.lineheight / 2) * g->ray.step;
		y = 0;
		while (++y < g->mapheight - 1)
		{
			ft_rayaux4(g, x, y, textpath);
		}
		g->zbuffer[x] = g->ray.perpwalldist;
	}
}

int		deal_key(t_game *g)
{
	key_movementws(g);
	key_movementad(g);
	key_rotation(g);
	return (0);
}

void	ft_isspray(t_game *g, int x, int y)
{
	g->spray[g->n_spray].posx = x + 0.5;
	g->spray[g->n_spray].posy = y + 0.5;
	g->n_spray++;
}
