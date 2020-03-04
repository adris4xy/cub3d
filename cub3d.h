/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aortega- <aortega-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 13:03:55 by egarcia-          #+#    #+#             */
/*   Updated: 2020/03/04 18:37:35 by aortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "minilibx/mlx.h"
# include "libft/libft.h"
# include <unistd.h>
# include <math.h>

typedef struct		s_keys
{
	int				w;
	int 			a;
	int 			s;
	int 			d;
	int 			left;
	int 			right;
	int 			run;
	int 			esc;
	double  		movespeed;
	double			rotspeed;
}   				t_keys;

typedef struct		s_ray
{
	double			posx;
	double			posy;
	double			dirx;
	double			diry;
	double			planex;
	double			planey;
	double			camerax;
	double			raydirx;
	double			raydiry;
	int				mapx;
	int				mapy;
	double			deltadistx;
	double			deltadisty;
	double			sidedistx;
	double			sidedisty;
	int				stepx;
	int				stepy;
	double			perpwalldist;
	int				hit;
	int				side;
	int				lineheight;
	int				texnum;
	int				texx;
	int				texy;
	double			wallx;
	double			step;
	unsigned int	color;
	double			texpos;
	double			old_dir;
	double			old_plane;
}   				t_ray;

typedef struct		s_texture
{
	int				*texture;
	int				textwidth;
	int				textheight;
	int				byte_per_pixel;
	int				endian;
	int				size_line;
}	   				t_texture;

typedef struct		s_render
{
	int				drawstart;
	int				drawend;
	int				floor;
	int				sky;
	int				bytes_per_pixel;
	int				size_line;
	int				endian;
	void			*dataimg;
}   				t_render;

typedef struct		s_floor
{
	float       	raydirx0;
	float       	raydiry0;
	float       	raydirx1;
	float       	raydiry1;
	int         	p;
	float       	posz;
	float       	rowdistance;
	float       	floorstepx;
	float       	floorstepy;
	float       	floorx;
	float       	floory;
	int         	cellx;
	int         	celly;
	int         	tx;
	int         	ty;
	int         	texturefloor;
}   				t_floor;


typedef struct 		s_spray
{
	float			posx;
	float			posy;
	double      	sprayx;
	double      	sprayy;
	double      	invdet;
	double      	transformx;
	double      	transformy;
	int				spritescreenx;
	int				spriteheight;
	int				drawstarty;
	int				drawendy;
	int				spritewidth;
	int				drawstartx;
	int				drawendx;
	int				texx;
	int				texy;
	double      	spritedistance;
}               	t_spray;

typedef struct		s_game
{
	void        	*mlx_ptr;
	void        	*win_ptr;
	int	        	*buff; 
	t_keys			key;
	t_render    	ren;
	t_ray       	ray;
	t_texture   	tex[6];
	t_floor     	f;
	t_spray     	spray[30];
	int         	mapwidth;
	int         	mapheight;
	char        	*spray_path;
	char        	*n_path;
	char        	*e_path;
	char        	*w_path;
	char        	*so_path;
	char        	*f_path;
	int         	f_color;
	int         	c_color;
	int				**worldmap;
	char			*texptr;
	double       	*zbuffer;
	int				n_spray;
	int				boolean;
	int				selector;
	int 			r;
	int 			gr;
	int 			b;
	int				col;
	int				row;
}             		t_game;

//cub3d.c
int		ft_master(t_game *g);
void	init_data(t_game *g);
void	ft_check_error(t_game *g);
//keys.c
int    	key_pressed(int key, t_keys *k);
int		key_released(int key, t_keys *k, t_game *g);
void	key_movement(t_game *g);
void	key_rotation(t_game *g);
int     deal_key(t_game *g);
//raycasting.c norme ok
void	ft_rayaux1(t_game *g);
void	ft_rayaux2(t_game *g);
void	ft_rayaux3(t_game *g, int textpath);
void	ft_rayaux4(t_game *g, int x, int y, int textpath);
void	ft_raygroupaux0(t_game *g, int x);
//spritecasting.c
void	shortsprites(t_game *g);
void	spray_raycasting(t_game *g);
void	ft_isspray(t_game *g, int x, int y);
//readmap.c
int		ft_ncol(char *map);
void	ft_map(char *map, t_game *g, int row);
void	ft_screensize(t_game *g,char *line);
void	ft_check_error(t_game *g);
void	ft_read_map(char *file, t_game *g);
//pathsmap.c
void	ft_set_start(int x, int y, char *map, t_game *g);
void	ft_path_s(char *line, t_game *g);
void	ft_path_new(char *line, t_game *g);
void	ft_path_color(char *line, t_game *g);
void	ft_path_coloraux(char *line, int i, t_game *g);
//utils.c
void	ft_error(char *s, t_game *g);
int		close_game(t_game *g);
void	get_textures(t_game *g);
void	get_texturesaux(t_game *g);
int		set_side(t_game *g);
//generalcasting.c
void	ft_raycasting(t_game *g);
#endif