
#include "cub3d.h"

void        floor_raycasting(s_game *g)
{
    int i;
    int x;
    int color;

    i = 0;

    while (i < g->mapheight)
    {
        g->f.raydirx0 = g->ray.dirx - g->ray.planex;
        g->f.raydiry0 = g->ray.diry - g->ray.planey;
        g->f.raydirx1 = g->ray.dirx + g->ray.planex;
        g->f.raydiry1 = g->ray.diry + g->ray.planey;
        g->f.posz = 0.5  * g->mapheight;
        g->f.p = i - g->mapheight / 2;
        g->f.rowdistance = g->f.posz / g->f.p;
        g->f.floorstepx = g->f.rowdistance * (g->f.raydirx1 - g->f.raydirx0) / g->mapwidth;
        g->f.floorstepy = g->f.rowdistance * (g->f.raydiry1 - g->f.raydiry0) / g->mapwidth;
        g->f.floorx = g->ray.posx + g->f.rowdistance * g->f.raydirx0;
        g->f.floory = g->ray.posy + g->f.rowdistance * g->f.raydiry0;

        x = 0;
        while (x < g->mapwidth)
        {
            g->f.cellx = (int)g->f.floorx;
            g->f.celly = (int)g->f.floory;
            g->f.tx = (int)(g->tex[4].textwidth * (g->f.floorx - g->f.cellx)) & (g->tex[4].textwidth - 1);
            g->f.ty = (int)(g->tex[4].textheight * (g->f.floory - g->f.celly)) & (g->tex[4].textheight - 1);
            g->f.floorx += g->f.floorstepx;
            g->f.floory += g->f.floorstepy;
            color = g->tex[4].texture[g->tex[4].textwidth * g->f.ty + g->f.tx];
            g->buff[(i * g->mapwidth + x)] = color;
            x++;
        }
        i++;
    }
}
void        shortsprites(s_game *g)
{
    int i;
    int j;
    s_spray tmp;

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

void       spray_raycasting(s_game *g)
{
    int i;
    int stripe;
    int y;
    int d;
    int color;
    i = 0;
    //shortsprites(g);
    while (i < g->n_spray)
    {
        g->spray[i].sprayx = g->spray[i].posx - g->ray.posx;
        g->spray[i].sprayy = g->spray[i].posy - g->ray.posy;
        g->spray[i].invdet = 1.0 / (g->ray.planex * g->ray.diry - g->ray.dirx * g->ray.planey);
        
        g->spray[i].transformx = g->spray[i].invdet * (g->ray.diry *  g->spray[i].sprayx - g->ray.dirx * g->spray[i].sprayy);
        g->spray[i].transformy = g->spray[i].invdet * (-g->ray.planey *  g->spray[i].sprayx + g->ray.planex * g->spray[i].sprayy);
        g->spray[i].spritescreenx = ((int)(g->mapwidth / 2)) * (1 +  g->spray[i].transformx / g->spray[i].transformy);
               // draw y start
        g->spray[i].spriteheight = abs((int)(g->mapheight / g->spray[i].transformy));
        g->spray[i].drawstarty = -g->spray[i].spriteheight / 2 + g->mapheight / 2;
        if (g->spray[i].drawstarty < 0)
            g->spray[i].drawstarty = 0;
        g->spray[i].drawendy = g->spray[i].spriteheight / 2 + g->mapheight / 2;
        if (g->spray[i].drawendy >=  g->mapheight)
            g->spray[i].drawendy = g->mapheight - 1;
        // calculate width
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
                    //g->buff[(stripe * g->mapwidth + y)] = color;
                    if (color != 0)
                            g->buff[(y * g->mapwidth + stripe)] = color;
                        y++;
                    }
                }
                stripe++;
            }
        i++;
        //printf("%f // %f\n", g->spray[i].transformy, g->zbuffer[stripe]);
    }
}