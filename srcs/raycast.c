/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoung <myoung@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 23:27:27 by myoung            #+#    #+#             */
/*   Updated: 2017/01/24 20:11:45 by myoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

/* length of ray from one x or y side to the next x or y side */
void	set_delta_dist(t_raycast *cast)
{
		t_2dp		ray_dir_sq;
		ray_dir_sq.x = cast->ray_dir.x * cast->ray_dir.x;
		ray_dir_sq.y = cast->ray_dir.y * cast->ray_dir.y;
		cast->delta_dist.x = sqrt(1 + (ray_dir_sq.y)
				/ (ray_dir_sq.x));
		cast->delta_dist.y = sqrt(1 + (ray_dir_sq.x)
				/ (ray_dir_sq.y));
}

/* calculate step and initial side_dist */
void	set_step_and_side_dist(t_raycast *cast)
{
	if (cast->ray_dir.x < 0)
	{
		cast->step_x = -1;
		cast->side_dist.x = (cast->ray_pos.x - cast->map_x) * cast->delta_dist.x;
	}
	else
	{
		cast->step_x = 1;
		cast->side_dist.x = (cast->map_x + 1.0 - cast->ray_pos.x)
			* cast->delta_dist.x;
	}
	if (cast->ray_dir.y < 0)
	{
		cast->step_y = -1;
		cast->side_dist.y = (cast->ray_pos.y - cast->map_y) * cast->delta_dist.y;
	}
	else
	{
		cast->step_y = 1;
		cast->side_dist.y = (cast->map_y + 1.0 - cast->ray_pos.y)
			* cast->delta_dist.y;
	}
}

void	raycast_init(t_view *v, t_raycast *cast, int x)
{
	cast->camera.x = 2 * x / (double)v->w - 1;
	cast->ray_pos.x = v->pos.x;
	cast->ray_pos.y = v->pos.y;
	cast->ray_dir.x = v->dir.x + v->plane.x * cast->camera.x;
	cast->ray_dir.y = v->dir.y + v->plane.y * cast->camera.x;
	cast->map_x = (int)v->pos.x;
	cast->map_y = (int)v->pos.y;
	cast->tile = TILE_AT(cast->map_x, cast->map_y);
	cast->hit = 0;
}

void	raycast_dda(t_view *v, t_raycast *cast)
{
		while (cast->hit == 0)
		{
			if (cast->side_dist.x < cast->side_dist.y)
			{
				cast->side_dist.x += cast->delta_dist.x;
				cast->map_x += cast->step_x;
				cast->side = 0;
			}
			else
			{
				cast->side_dist.y += cast->delta_dist.y;
				cast->map_y += cast->step_y;
				cast->side = 1;
			}
			cast->tile = TILE_AT(cast->map_x,cast->map_y);
			if (cast->tile > 0)
				cast->hit = 1;
		}
}
