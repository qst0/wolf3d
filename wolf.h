/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libfx.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoung <myoung@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/23 03:27:52 by myoung            #+#    #+#             */
/*   Updated: 2017/01/13 00:20:09 by myoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

//REMOVE ME DAWG!
# include <stdio.h>

# include <stdlib.h>
# include <math.h>
# include <mlx.h>

# include "time.h"
# include <mach/clock.h>
# include <mach/mach.h>

# include "keys.h"

/*
# include <keys.h>
# include <libft.h>
*/

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
	int			**texture;
	int			w;
	int			h;
	int			mouse_x;
	int			mouse_y;
	int			cur_sec;
	int			past;
	int			tex_width;
	int			tex_height;
	double		cur_time;
	double		old_time;
	double		rot_speed;
	double		move_speed;
	t_2dp		pos;
	t_2dp		dir;
	t_2dp		plane;
	t_img		image;
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
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
}				t_raycast;

#endif
