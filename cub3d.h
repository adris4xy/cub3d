/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egarcia- <emilioggo@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 13:03:55 by egarcia-          #+#    #+#             */
/*   Updated: 2020/03/02 19:49:19 by egarcia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H
#endif

#include "minilibx/mlx.h"
//#include "mlx.h"
#include "libft/libft.h"
#include <unistd.h>
//#include <time.h>
#include <math.h>
#include <stdio.h>
#define TEXTWIDTH 64
#define TEXTHEIGHT 64
#define mapWidth 24
#define mapHeight 24

/*int worldMap[mapWidth][mapHeight]=
{
  {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
  {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
  {4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
  {4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
  {4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
  {4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
  {4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
  {4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
  {4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
  {4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
  {4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
  {4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
  {6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
  {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
  {6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
  {4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
  {4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
  {4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
  {4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
  {4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
};
*/
typedef struct t_keys
{
    int w;
    int a;
    int s;
    int d;
    int left;
    int right;
    int run;
    int esc;
    double  movespeed;
	double	rotspeed;
}   s_keys;

typedef struct t_ray
{
    double  posx;
    double  posy;
    double  dirx;
    double  diry;
    double  planex;
    double  planey;
    double  camerax;
    double  raydirx;
    double  raydiry;
    int     mapx;
    int     mapy;
    double  deltadistx;
    double  deltadisty;
    double  sidedistx;
    double  sidedisty;
    int     stepx;
    int     stepy;
    double  perpwalldist;
    int     hit;
    int     side;
    int     lineheight;
    int     texnum;
    int     texx;
    int     texy;
    double  wallx;
    double  step;
    unsigned int color;
    double  texpos;
	double  old_dir;
	double  old_plane;
}   s_ray;
typedef struct t_texture
{
    int *texture;
    int textwidth;
    int textheight;
    int byte_per_pixel;
    int endian;
    int size_line;
}       s_texture;

typedef struct t_render
{
    int drawstart;
    int drawend;
    int floor;
    int sky;
	int	bytes_per_pixel;
	int	size_line;
	int	endian;
    void *dataimg;
}   s_render;

typedef struct t_floor
{
    float       raydirx0;
    float       raydiry0;
    float       raydirx1;
    float       raydiry1;
    int         p;
    float       posz;
    float       rowdistance;
    float       floorstepx;
    float       floorstepy;
    float       floorx;
    float       floory;
    int         cellx;
    int         celly;
    int         tx;
    int         ty;
    int         texturefloor;
}   s_floor;

typedef struct t_save
{
    int     height;
    int     width;
    int     pad;
    int     fd;
    unsigned int *file_header;
    unsigned int *img_header;
}   s_save;

typedef struct t_spray
{
    float       posx;
    float         posy;
    double      sprayx;
    double      sprayy;
    double      invdet;
    double      transformx;
    double      transformy;
    int         spritescreenx;
    int         spriteheight;
    int         drawstarty;
    int         drawendy;
    int         spritewidth;
    int         drawstartx;
    int         drawendx;
    int         texx;
    int         texy;
    double      spritedistance;
}               s_spray;

typedef struct t_game
{
    void        *mlx_ptr;
    void        *win_ptr;
	int	        *buff; 
    s_keys      key;
    s_render    ren;
    s_ray       ray;
    s_texture   tex[6];
    s_floor     f;
    s_spray     spray[30];
    int         mapwidth;
    int         mapheight;
    char        *spray_path;
    char        *n_path;
    char        *e_path;
    char        *w_path;
    char        *so_path;
    char        *f_path;
    int         f_color;
    int         c_color;
    int        **worldmap;
	char		*texptr;
    double       *zbuffer;
    int         n_spray;
    int         boolean;
}               s_game;


// MANAGER && MASTER

int    ft_master(s_game *game);
void	init_data(s_game *g);
int    close_game(s_game *g);
// KEY MANAGER
int     deal_key(s_game *game);
int     key_released(int key, s_keys *k);
int     key_pressed(int key, s_keys *k);
void    init_keys(s_keys *k);
void    ft_read_map(char *file, s_game *g);
void    ft_raycasting(s_game *g, int selector);
void    get_textures(s_game *g);
void    floor_raycasting(s_game *g);
void    spray_raycasting(s_game *g);
void    shortsprites(s_game *g);
void    check_screenshot(s_game *g, char *argv);
void    ft_error(char *s, s_game *g);

// read map 2

void        ft_isspray(s_game *g, int x, int y);