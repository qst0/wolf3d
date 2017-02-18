/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floorcast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoung <myoung@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 23:30:32 by myoung            #+#    #+#             */
/*   Updated: 2017/02/09 09:58:54 by myoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

static void		floorcast_prep(t_view *v, t_raycast *cast, t_2dp *floor_wall)
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

void			floorcast(t_view *v, t_raycast *cast, int x)
{
	int			y;
	int			color;
	t_floorcast	fc;

	floorcast_prep(v, cast, &fc.wall);
	y = cast->draw_end;
	while (++y < v->h)
	{
		fc.weight = (v->h / (2.0 * y - v->h)) / cast->perp_wall_dist;
		fc.pos.x = fc.weight * fc.wall.x + (1.0 - fc.weight) * v->pos.x;
		fc.pos.y = fc.weight * fc.wall.y + (1.0 - fc.weight) * v->pos.y;
		fc.tex_x = (int)(fc.pos.x * v->tex_width) % v->tex_width;
		fc.tex_y = (int)(fc.pos.y * v->tex_height) % v->tex_height;
		fc.texture = TILE_AT(fc.pos.x, fc.pos.y) == -1 ? 4 : 3;
		fc.texture = TILE_AT(fc.pos.x, fc.pos.y) == -2 ? 1 : fc.texture;
		color = v->texture[1][v->tex_width * fc.tex_y + fc.tex_x];
		draw_point_to_img(&v->image, x, y, color);
		color = v->texture[4][v->tex_width * fc.tex_y + fc.tex_x];
		draw_point_to_img(&v->image, x, v->h - y, color);
	}
}
