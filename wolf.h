/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libfx.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoung <myoung@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/23 03:27:52 by myoung            #+#    #+#             */
/*   Updated: 2017/01/17 06:52:13 by myoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

//REMOVE ME DAWG!
# include <stdio.h>

# include <stdlib.h>
# include <math.h>
# include <mlx.h>

# include <time.h>
# include <mach/clock.h>
# include <mach/mach.h>

# include <keys.h>

# define MAP_WIDTH 24
# define MAP_HEIGHT 24
# define GEN_TEX_COUNT 8
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define WINDOW_WIDTH 960
# define WINDOW_HEIGHT 600

typedef struct	s_2dp
{
	double		x;
	double		y;
}				t_2dp;

typedef struct s_img
{
	int			id;
	void		*ptr;
	char		*pixels;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	int			x_offset;
	int			y_offset;
}				t_img;

typedef struct	s_view
{
	void		*mlx;
	void		*window;
	void		*minimap_window;
	int			**texture;
	int			w;
	int			h;
	int			mouse_x;
	int			mouse_y;
	int			cur_sec;
	int			past;
	int			tex_width;
	int			tex_height;
	double		old_time;
	double		cur_time;
	double		frame_time;
	double		rot_speed;
	double		move_speed;
	t_2dp		pos;
	t_2dp		dir;
	t_2dp		plane;
	t_img		image;
	t_img		minimap_image;
	t_keys		key;
}				t_view;

typedef	struct	s_raycast
{
	t_2dp		camera;
	t_2dp		ray_pos;
	t_2dp		ray_dir;
	int			map_x;
	int			map_y;
	t_2dp		side_dist;
	t_2dp		delta_dist;
	double		perp_wall_dist;
	double		wall_x;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			tex_x;
	int			tex_y;
	int			line_height;
	int			draw_start;
	int			draw_end;
}				t_raycast;

t_view	*create_view(int w, int h, char *title);

void	use_image(t_view *v);
void	create_image(void *mlx, t_img *image, int w, int h);

int		nlen(int n);
char	*itoa(int i);
int		fake_floor(double x);

void	ft_get_time(struct timespec *ts);
void	update_time(t_view *v);

void	texture_init(t_view *v);

int		motion_hook(int x, int y, t_view *v);
int		exit_hook(t_view *v);
void	set_hooks(t_view *v);

void	draw_point_to_img(t_img *img, int x, int y, int color);
void	draw_filled_square(t_view *v, t_2dp p, int size, int color);

void	put_minimap(t_view *v);
void	create_minimap(t_view *v);

void	player_turn(t_view *v, int way, int speed_mod);

int		loop_hook(t_view *v);
int		key_press_hook(int keycode, t_view *v);
int		key_release_hook(int keycode, t_view *v);

void	key_toggle(t_keys *key, int keycode, int toggle);
void	keys_init(t_keys *key);

#endif
