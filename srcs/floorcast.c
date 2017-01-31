/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floorcast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoung <myoung@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 23:30:32 by myoung            #+#    #+#             */
/*   Updated: 2017/01/27 02:01:14 by myoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

static void floorcast_prep(t_view *v, t_raycast *cast, t_2dp *floor_wall)
{
		if (cast->side == 0 && cast->ray_dir.x > 0)
		{
			floor_wall->x = cast->map_x;
			floor_wall->y = cast->map_y + cast->wall_x;
		}
		else if (cast->side == 0 && cast->ray_dir.x < 0)
		{
			floor_wall->x = cast->map_x + 1.0;
			floor_wall->y = cast->map_y + cast->wall_x;
		}
		else if (cast->side == 1 && cast->ray_dir.y > 0)
		{
			floor_wall->x = cast->map_x + cast->wall_x;
			floor_wall->y = cast->map_y;
		}
		else
		{
			floor_wall->x = cast->map_x + cast->wall_x;
			floor_wall->y = cast->map_y + 1.0;
		}

		if (cast->draw_end < 0)
			cast->draw_end = v->h;
}

void	floorcast(t_view *v, t_raycast *cast, int x)
{
	int y;
	t_2dp floor_wall;

	floorcast_prep(v, cast, &floor_wall);
	y = cast->draw_end;
	while (++y < v->h)
	{
		double weight = (v->h / (2.0 * y - v->h)) / cast->perp_wall_dist;

		t_2dp cur_floor;
		cur_floor.x = weight * floor_wall.x + (1.0 - weight) * v->pos.x;
		cur_floor.y = weight * floor_wall.y + (1.0 - weight) * v->pos.y;

		int floor_tex_x;
		int floor_tex_y;
		floor_tex_x = (int)(cur_floor.x * v->tex_width) % v->tex_width;
		floor_tex_y = (int)(cur_floor.y * v->tex_height) % v->tex_height;

		int floor_tex;
		floor_tex = (int)(cur_floor.x) % 2 && (int)(cur_floor.y) % 2 ? 7 : 5;
		floor_tex = (int)cur_floor.y == 10 ? 3 : floor_tex;
		floor_tex = TILE_AT(cur_floor.x, cur_floor.y) == -1 ? 4 : floor_tex;
		floor_tex = TILE_AT(cur_floor.x, cur_floor.y) == -2 ? 1 : floor_tex;

		int color;
		//Floor
		color = v->texture[floor_tex][v->tex_width * floor_tex_y + floor_tex_x];
		draw_point_to_img(&v->image, x, y, color);
		//Ceiling
		color = v->texture[4][v->tex_width * floor_tex_y + floor_tex_x];
		draw_point_to_img(&v->image, x, v->h - y, color);
	}
}
