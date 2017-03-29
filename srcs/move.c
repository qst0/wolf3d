/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoung <myoung@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 05:57:24 by myoung            #+#    #+#             */
/*   Updated: 2017/03/29 11:40:35 by myoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

void	player_movement_strafe_turn(t_view *v)
{
	t_2dp strafe;

	strafe.x = v->plane.x * v->move_speed;
	strafe.y = v->plane.y * v->move_speed;
	if (v->key.d)
	{
		if (TILE_AT(v->pos.x + strafe.x, v->pos.y) < 1)
			v->pos.x += strafe.x;
		if (TILE_AT(v->pos.x, v->pos.y + strafe.y) < 1)	
			v->pos.y += strafe.y;
	}
	else if (v->key.a)
	{
		if (TILE_AT(v->pos.x - strafe.x, v->pos.y) < 1)
			v->pos.x -= strafe.x;
		if (TILE_AT(v->pos.x, v->pos.y - strafe.y) < 1)	
			v->pos.y -= strafe.y;
	}
	if (v->key.e)
		player_turn(v, -1, 1);
	else if (v->key.q)
		player_turn(v, 1, 1);
}

void	player_movement_forward_backward(t_view *v)
{
		t_2dp move;

		move.x = v->dir.x * v->move_speed;	
		move.y = v->dir.y * v->move_speed;	
		if (v->key.w)
		{
			if (TILE_AT(v->pos.x + move.x, v->pos.y) < 1)
				v->pos.x += move.x;
		   	if (TILE_AT(v->pos.x, v->pos.y + move.y) < 1)	
				v->pos.y += move.y;
		}
		else if (v->key.s)
		{	
			if (TILE_AT(v->pos.x - move.x, v->pos.y) < 1)
				v->pos.x -= move.x;
		   	if (TILE_AT(v->pos.x, v->pos.y - move.y) < 1)	
				v->pos.y -= move.y;
		}
}

/*
** Left is 1, right is -1, both camera direction and plane must be rotated
*/

void	player_turn(t_view *v, int way, double speed_mod)
{
	double old_dir_x = v->dir.x;
	double old_plane_x = v->plane.x;
	
	v->dir.x = v->dir.x * cos(v->rot_speed * way * speed_mod)
		- v->dir.y * sin(v->rot_speed * way * speed_mod);
	v->dir.y = old_dir_x * sin(v->rot_speed * way * speed_mod)
		+ v->dir.y * cos(v->rot_speed * way * speed_mod);
	v->plane.x = v->plane.x * cos(v->rot_speed * way * speed_mod)
		- v->plane.y * sin(v->rot_speed * way * speed_mod);
	v->plane.y = old_plane_x * sin(v->rot_speed * way * speed_mod)
		+ v->plane.y * cos(v->rot_speed * way * speed_mod);
}
