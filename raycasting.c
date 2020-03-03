/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egarcia- <emilioggo@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 16:44:03 by egarcia-          #+#    #+#             */
/*   Updated: 2020/03/02 20:56:19 by egarcia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int    set_side(s_game *g)
{
    if (g->ray.posx > (double)g->ray.mapx)
	{
		if (g->ray.side == 1 && g->ray.posy > g->ray.mapy)
			return (2);
		else if (g->ray.side == 1 && g->ray.posy < g->ray.mapy)
			return (3);
		else
			return (0);
	}
	else
	{
		if (g->ray.side == 1 && g->ray.posy > g->ray.mapy)
			return (2);
		else if (g->ray.side == 1 && g->ray.posy < g->ray.mapy)
			return (3);
		else
			return (1);
	}
}

void        get_textures(s_game *g)
{
    if (!(g->texptr = mlx_xpm_file_to_image(g->mlx_ptr, g->n_path, &g->tex[0].textwidth,
            &g->tex[0].textheight)))
        ft_error("ERROR, N_PATH WRONG", g);
	g->tex[0].texture = (int *)mlx_get_data_addr(g->texptr, &g->tex[0].byte_per_pixel, &g->tex[0].size_line, &g->tex[0].endian);
	if (!(g->texptr = mlx_xpm_file_to_image(g->mlx_ptr, g->so_path, &g->tex[1].textwidth,
        &g->tex[1].textheight)))
        ft_error("ERROR, SO_PATH WRONG", g);
	g->tex[1].texture = (int *)mlx_get_data_addr(g->texptr, &g->tex[1].byte_per_pixel, &g->tex[1].size_line, &g->tex[1].endian);
	if (!(g->texptr = mlx_xpm_file_to_image(g->mlx_ptr, g->w_path, &g->tex[2].textwidth, &g->tex[2].textheight)))
        ft_error("ERROR, W_PATH WRONG", g);
	g->tex[2].texture = (int *)mlx_get_data_addr(g->texptr, &g->tex[2].byte_per_pixel, &g->tex[2].size_line, &g->tex[2].endian);
	if (!(g->texptr = mlx_xpm_file_to_image(g->mlx_ptr, g->e_path, &g->tex[3].textwidth, &g->tex[3].textheight)))
         ft_error("ERROR, W_PATH WRONG", g);
	g->tex[3].texture = (int *)mlx_get_data_addr(g->texptr, &g->tex[3].byte_per_pixel, &g->tex[3].size_line, &g->tex[3].endian);
    if (g->f_path != NULL && g->f.texturefloor == 1)
    {
        g->texptr = mlx_xpm_file_to_image(g->mlx_ptr, g->f_path, &g->tex[4].textwidth, &g->tex[4].textheight);
	    g->tex[4].texture = (int *)mlx_get_data_addr(g->texptr, &g->tex[4].byte_per_pixel, &g->tex[4].size_line, &g->tex[4].endian);
    }
    if (g->spray_path != NULL)
    {
        g->texptr = mlx_xpm_file_to_image(g->mlx_ptr, g->spray_path, &g->tex[5].textwidth, &g->tex[5].textheight);
	    g->tex[5].texture = (int *)mlx_get_data_addr(g->texptr, &g->tex[5].byte_per_pixel, &g->tex[5].size_line, &g->tex[5].endian);
    }
}

void        ft_raycasting(s_game *g, int selector)
{
    int x;
    int y;
    s_ray *p;
    int textpath;

    p = &g->ray;
    
    if (g->f.texturefloor == 1 && selector == 0)
	            floor_raycasting(g);
	x = 0;
     
    while (x++ < g->mapwidth)
    {
        textpath = set_side(g);
        p->camerax = 2 * x / (double)g->mapwidth - 1;
        p->raydirx = p->dirx + p->planex * p->camerax;
        p->raydiry = p->diry + p->planey * p->camerax;
        p->mapx = (int)p->posx;
        p->mapy = (int)p->posy;
        p->deltadistx = fabs(1 / p->raydirx);
        p->deltadisty = fabs(1 / p->raydiry);

        //p->deltadistx = sqrt(1 + (p->raydiry * p->raydiry) / (p->raydirx * p->raydirx));
        //p->deltadisty = sqrt(1 + (p->raydirx * p->raydirx) / (p->raydiry * p->raydiry));
        p->hit = 0;
        if (p->raydirx < 0)
        {
            p->stepx = -1;
            p->sidedistx = (p->posx - p->mapx) * p->deltadistx;
        }
        else
        {
            p->stepx = 1;
            p->sidedistx = (p->mapx + 1.0 - p->posx) * p->deltadistx; 
        }
        if (p->raydiry < 0)
        {
            p->stepy = -1;
            p->sidedisty = (p->posy - p->mapy) * p->deltadisty;
        }
        else
        {
            p->stepy = 1;
            p->sidedisty = (p->mapy + 1.0 - p->posy) * p->deltadisty;
        }
        while (p->hit == 0)
        {
            if (p->sidedistx < p->sidedisty)
            {
                p->sidedistx += p->deltadistx;
                p->mapx += p->stepx;
                p->side = 0;
            }
            else
            {
                p->sidedisty += p->deltadisty;
                p->mapy += p->stepy;
                p->side = 1;
            }
            if (g->worldmap[p->mapx][p->mapy] == 2 && selector == 1)
                g->boolean = 1;
            if (g->worldmap[p->mapx][p->mapy] ==  1)
                p->hit = 1;
        }
        if (g->boolean == 1 && selector == 1)
            continue;
        if (p->side == 0)
            p->perpwalldist = (p->mapx - p->posx + (1 - p->stepx) / 2) / p->raydirx;
        else
            p->perpwalldist = (p->mapy - p->posy + (1 - p->stepy) / 2) / p->raydiry;
        p->lineheight = (int)(g->mapheight / p->perpwalldist);
        g->ren.drawstart = -p->lineheight / 2 + g->mapheight / 2;
        if (g->ren.drawstart < 0)
            g->ren.drawstart = 0;
        g->ren.drawend = p->lineheight / 2 + g->mapheight / 2;
        if (g->ren.drawend >= (int)g->mapheight)
            g->ren.drawend = g->mapheight - 1;
        // Calculo de texturas
		p->texnum = g->worldmap[p->mapx][p->mapy] - 1;
		// Calculo del valor Muro X
        if (p->side == 0)
            p->wallx = p->posy + p->perpwalldist * p->raydiry;
        else
            p->wallx = p->posx + p->perpwalldist * p->raydirx;
        p->wallx -= floor((p->wallx));
		
        p->texx = (int)(p->wallx * (double)g->tex[textpath].textwidth);
        if (p->side == 0 && p->raydirx > 0)
            p->texx =g->tex[textpath].textwidth - p->texx - 1;
        if (p->side == 1 && p->raydiry < 0)
            p->texx = g->tex[textpath].textwidth - p->texx - 1;
        p->step = 1.0 * g->tex[textpath].textwidth / p->lineheight;
        p->texpos = (g->ren.drawstart - g->mapheight / 2 + p->lineheight / 2) * p->step;
        y = 0;
		
		while (++y < g->mapheight - 1)
		{
			if (y < g->ren.drawstart)
            {
                if (y % 20 > rand() % g->mapwidth)
                {
                    if (rand() % 100  > 0.1)
				        g->buff[(y * g->mapwidth) + x] = g->c_color;
                else
                   g->buff[(y * g->mapwidth) + x] = 255 * 65536 + 255 * 256 + 255;
                }
                else
                    g->buff[(y * g->mapwidth) + x] = g->c_color;
            }
            else if (y >= g->ren.drawstart && y <= g->ren.drawend)
			{
				p->texy = (int)p->texpos & (g->tex[textpath].textheight - 1);
				p->texpos += p->step;
				p->color = g->tex[textpath].texture[g->tex[textpath].textheight * p->texy + p->texx];
				if (p->side == 1)
					p->color = (p->color >> 1) & 8355711;
				g->buff[(y * g->mapwidth + x)] = p->color;
				
			}
			else if (y > g->ren.drawend && g->f.texturefloor == 0)
				g->buff[(y * g->mapwidth) + x] = g->f_color;	
		}
        g->zbuffer[x] = p->perpwalldist;
    }
    
    if (selector  == 0)
    {
        shortsprites(g);
        spray_raycasting(g);
        ft_raycasting(g, 1);
    }
    
    
} 