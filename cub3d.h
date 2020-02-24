/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aortega- <aortega-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 12:09:14 by egarcia-          #+#    #+#             */
/*   Updated: 2020/02/24 19:02:16 by aortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "minilibx/mlx.h"
# include "libft/libft.h"
# include <unistd.h>
# include <math.h>

typedef	struct	s_readmap
{
	char		*line;
	int			ret;
	char		*map;
	char		*tmp;
	int			row;
	int			i;
}				t_readmap;

typedef	struct	s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*dataimg;
	int			*buff;
	int			w;
	int			a;
	int			s;
	int			d;
	int			left;
	int			right;
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
	double		planex;
	double		planey;
	double		camerax;
	double		raydirx;
	double		raydiry;
	int			mapx;
	int			mapy;
	double		deltadistx;
	double		deltadisty;
	double		sidedistx;
	double		sidedisty;
	int			stepx;
	int			stepy;
	double		perpwalldist;
	int			hit;
	int			side;
	int			lineheight;
	int			drawstart;
	int			drawend;
	int			color;
	int			bytes_per_pixel;
	int			size_line;
	int			endian;
	double		frametime;
	double		movespeed;
	double		rotspeed;
	double		old_dir;
	double		old_plane;
	int			mapwidth;
	int			mapheight;
	char		*spray_path;
	char		*n_path;
	char		*e_path;
	char		*w_path;
	char		*so_path;
	int			f_color;
	int			c_color;
	int			**worldmap;
	char		*texptr;
	int			textnum;
	double		wallx;
	int			textx;
	int			texty;
	int			textwidth;
	int			textheight;
	double		step;
	double		textpos;
	int			*texture[5];
}				t_game;

//cub3d.c
void	init_data(t_game *g);
int		ft_master(t_game *g);
void	get_textures(t_game *g);
int		set_side(t_game *g);
//keys.c
int		key_released(int key, t_game *g);
int		key_pressed(int key, t_game *g);
int		dealws_key(t_game *g);
int		dealad_key(t_game *g);
int		dealrl_key(t_game *g);
//raycasting.c
void	ft_raycasting(t_game *g);
void	ft_calculate_texture(t_game *g);
void	ft_ddaloop(t_game *g);
void	ft_step_sidedist(t_game *g);
void	ft_printline(int x, t_game *g);
//read_map.c
void	ft_read_map(char *file, t_game *g);
void	ft_mapaux(t_game *g, int size, t_readmap *struc, int j);
void	ft_map(char *map, t_game *g, t_readmap *struc);
void	ft_set_start(int x, int y, char *map, t_game *g);
//paths.c
void	ft_pathcoloraux(int i, t_game *g, t_readmap *struc);
void	ft_path_color(char *line, t_game *g, t_readmap *struc);
void	ft_path_new(char *line, t_game *g);
void	ft_path_s(char *line, t_game *g);
#endif
