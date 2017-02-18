/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoung <myoung@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 22:59:07 by myoung            #+#    #+#             */
/*   Updated: 2017/02/09 10:00:24 by myoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

typedef struct		s_sprite
{
	t_2dp	pos;
	int		texture;
}					t_sprite;

#define SPRITE_COUNT 42
t_sprite	sprite[SPRITE_COUNT];
int			sprite_order[SPRITE_COUNT];
double		sprite_dist[SPRITE_COUNT];

void	set_sprite(int index, double x, double y, int texture)
{
	sprite[index].pos.x = x;
	sprite[index].pos.y = y;
	sprite[index].texture = texture;
}

void	sprite_init(t_view *v)
{
	int i;

	i = -1;
	while(++i < SPRITE_COUNT)
		set_sprite(i, rand() % v->map.height + 1, rand() % v->map.width + 1, rand() % 8);
}

void	sprite_casting(t_view *v)
{
	int i = -1;
	while(++i < SPRITE_COUNT)
	{
		sprite_order[i] = i;
		sprite_dist[i] = ((v->pos.x - sprite[i].pos.x) * (v->pos.x - sprite[i].pos.x) +
				(v->pos.y - sprite[i].pos.y) * (v->pos.y - sprite[i].pos.y));
	}
	comb_sort(sprite_order, sprite_dist, SPRITE_COUNT);

	i = -1;
	while(++i < SPRITE_COUNT)
	{
		t_2dp sprite_pos;
		t_2dp transform;
		double inv_det;
		int sprite_shrink;
		int sprite_move;
		int sprite_height;
		int sprite_screen_x;
		int sprite_width;
		int draw_start_y;
		int draw_end_y;
		int draw_start_x;
		int draw_end_x;


		inv_det = 1.0 / (v->plane.x * v->dir.y - v->dir.x * v->plane.y);
		sprite_pos.x = sprite[sprite_order[i]].pos.x - v->pos.x;
		sprite_pos.y = sprite[sprite_order[i]].pos.y - v->pos.y;
		transform.x = inv_det * (v->dir.y * sprite_pos.x - v->dir.x * sprite_pos.y);
		transform.y = inv_det * (-v->plane.y * sprite_pos.x + v->plane.x * sprite_pos.y);
		sprite_shrink = 2;
		sprite_height = ABS((int)(v->h / transform.y)) / sprite_shrink;
		sprite_width = ABS((int)(v->h / transform.y)) / sprite_shrink;
		sprite_move = sprite_height;
		sprite_move = (int)(sprite_move / transform.y);


		draw_start_y = -sprite_height / 2 + v->h / 2 + sprite_move;
		draw_end_y = sprite_height / 2 + v->h / 2 + sprite_move;
		sprite_screen_x = (int)((v->w / 2) * (1 + transform.x / transform.y));
		draw_start_x = -sprite_width / 2 + sprite_screen_x;
		draw_end_x = sprite_width / 2 + sprite_screen_x;

		if (draw_start_y < 0)
			draw_start_y = 0;
		if (draw_start_x < 0)
			draw_start_x = 0;
		if (draw_end_y >= v->h)
			draw_end_y = v->h - 1;
		if (draw_end_x >= v->w)
			draw_end_x = v->w - 1;

		int col;
		col = draw_start_x - 1;
		if (sprite_screen_x > 0 && transform.y > 0 && draw_end_x > sprite_screen_x
				&& sprite_screen_x < v->w && draw_start_y < draw_end_y)
		{
			while (++col < draw_end_x)
			{
				int tex_x = (int)((col - (-sprite_width / 2 + sprite_screen_x)) * v->tex_width / sprite_width);
				if (col > 0 && col < v->w && transform.y < v->z_buff[col])
				{
					int y = draw_start_y - 1;
					while (++y < draw_end_y)
					{
						int d = (y - sprite_move) * 256 - v->h * 128 + sprite_height * 128;
						int tex_y = ((d * v->tex_height) / sprite_height) / 256;
						int color = v->texture[sprite[sprite_order[i]].texture][v->tex_width * tex_y + tex_x];
						draw_point_to_img(&v->image, col, y, color);
					}
				}
			}
		}

	}
}
