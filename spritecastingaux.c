/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spritecastingaux.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aortega- <aortega-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 18:30:14 by aortega-          #+#    #+#             */
/*   Updated: 2020/03/05 16:13:21 by aortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void        shortsprites(t_game *g)
{
    int i;
    int j;
    t_spray tmp;

    i = 0;
    j = 0;
    while (i < g->n_spray)
    {
        g->spray[i].spritedistance = (g->ray.posx - g->spray[i].posx) * (g->ray.posx - g->spray[i].posx)
        + (g->ray.posy - g->spray[i].posy) *  (g->ray.posy - g->spray[i].posy);
        i++;
    }
    i = 0;
    while (i < g->n_spray)
    {
        j = 0;
        while (j < g->n_spray - i - 1)
        {
            if (g->spray[j].spritedistance < g->spray[j + 1].spritedistance)
            {
                tmp = g->spray[j];
                g->spray[j] = g->spray[j + 1];
                g->spray[j + 1] = tmp;
            }
            j++;
        }
        i++;
    }

}

void       spray_raycasting(t_game *g)
{
    int i;
    int stripe;
    int y;
    int d;
    int color;
	
    i = 0;
    while (i < g->n_spray)
    {
        g->spray[i].sprayx = g->spray[i].posx - g->ray.posx;
        g->spray[i].sprayy = g->spray[i].posy - g->ray.posy;
        g->spray[i].invdet = 1.0 / (g->ray.plx * g->ray.diry - g->ray.dirx * g->ray.ply);
        
        g->spray[i].transformx = g->spray[i].invdet * (g->ray.diry *  g->spray[i].sprayx - g->ray.dirx * g->spray[i].sprayy);
        g->spray[i].transformy = g->spray[i].invdet * (-g->ray.ply *  g->spray[i].sprayx + g->ray.plx * g->spray[i].sprayy);
        g->spray[i].spritescreenx = ((int)(g->mapwidth / 2)) * (1 +  g->spray[i].transformx / g->spray[i].transformy);
        g->spray[i].spriteheight = abs((int)(g->mapheight / g->spray[i].transformy));
        g->spray[i].drawstarty = -g->spray[i].spriteheight / 2 + g->mapheight / 2;
        if (g->spray[i].drawstarty < 0)
            g->spray[i].drawstarty = 0;
        g->spray[i].drawendy = g->spray[i].spriteheight / 2 + g->mapheight / 2;
        if (g->spray[i].drawendy >=  g->mapheight)
            g->spray[i].drawendy = g->mapheight - 1;
        g->spray[i].spritewidth = abs((int)(g->mapheight / g->spray[i].transformy));
        g->spray[i].drawstartx = -g->spray[i].spritewidth / 2 + g->spray[i].spritescreenx;
        if (g->spray[i].drawstartx < 0)
            g->spray[i].drawstartx = 0;
        g->spray[i].drawendx = g->spray[i].spritewidth / 2 + g->spray[i].spritescreenx;
        if (g->spray[i].drawendx >= g->mapwidth)
            g->spray[i].drawendx = g->mapwidth - 1;
        stripe = g->spray[i].drawstartx;
            while (stripe < g->spray[i].drawendx)
            {
                
                 g->spray[i].texx = (int)((256 * (stripe - (-g->spray[i].spritewidth / 2 + g->spray[i].spritescreenx)) * g->tex[5].textwidth / g->spray[i].spritewidth) / 256);
                 y = g->spray[i].drawstarty;
                 if (g->spray[i].transformy > 0 && stripe > 0 && stripe < g->mapwidth  && g->spray[i].transformy < g->zbuffer[stripe])
                {   
                    while (y < g->spray[i].drawendy)
                    {
                        d = y * 256 - g->mapheight  * 128 + g->spray[i].spriteheight * 128;
                        g->spray[i].texy = ((d * g->tex[5].textheight) / g->spray[i].spriteheight) / 256;
                        color = g->tex[5].texture[g->tex[5].textwidth * g->spray[i].texy + g->spray[i].texx];
                    if (color != 0)
                            g->buff[(y * g->mapwidth + stripe)] = color;
                        y++;
                    }
                }
                stripe++;
            }
        i++;
    }
}

void        ft_isspray(t_game *g, int x, int y)
{
    g->spray[g->n_spray].posx = x + 0.5;
    g->spray[g->n_spray].posy = y + 0.5;
    g->n_spray++;
}