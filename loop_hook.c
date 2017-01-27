/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoung <myoung@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 23:21:00 by myoung            #+#    #+#             */
/*   Updated: 2017/01/24 22:49:16 by myoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

int		loop_hook(t_view *v)
{
	int x;
	
	update_time(v);
	create_image(v->mlx, &v->image, v->w, v->h);
	x = -1;
	while (++x < v->w)
	{
		t_raycast	cast;

		raycast_init(v, &cast, x);
		set_delta_dist(&cast);
		set_step_and_side_dist(&cast);
		raycast_dda(v, &cast);
		if (cast.side == 0) 
			cast.perp_wall_dist = (cast.map_x - cast.ray_pos.x 
					+ (1 - cast.step_x) / 2) / cast.ray_dir.x;
		else
			cast.perp_wall_dist = (cast.map_y - cast.ray_pos.y 
					+ (1 - cast.step_y) / 2) / cast.ray_dir.y;
		cast.line_height = (int)(v->h / cast.perp_wall_dist);
		cast.draw_start = -cast.line_height / 2 + v->h / 2;
		if (cast.draw_start < 0)
			cast.draw_start = 0;
		cast.draw_end = cast.line_height / 2 + v->h / 2;
		if (cast.draw_end >= v->h)
			cast.draw_end = v->h - 1;
		cast.wall_x = cast.side == 0
			? cast.ray_pos.y + cast.perp_wall_dist * cast.ray_dir.y
			: cast.ray_pos.x + cast.perp_wall_dist * cast.ray_dir.x;
		cast.wall_x -= fake_floor(cast.wall_x);
		cast.tex_x = (int)(cast.wall_x * (double)(v->tex_width));
		cast.tex_x = v->tex_width - cast.tex_x - 1;
		int y;

		y = cast.draw_start;
		while (y < cast.draw_end)
		{
			int color;
			int d;
			
			//256 and 128 factors to avoid floats
			d = y * 256 - v->h * 128 + cast.line_height * 128;
			cast.tex_y = ((d * v->tex_height) / cast.line_height) / 256;
			color = v->texture[cast.tile - 1]
				[v->tex_height * cast.tex_y + cast.tex_x];
			
			if (cast.side == 1)
				color = (color >> 1) & 0x7F7F7F;
			draw_point_to_img(&v->image, x, y, color);
			y++;
		}

		floorcast(v, &cast, x);

		// Set the z_buff for the sprite casting
		//v->z_buff[x] = cast.perp_wall_dist;
		//sprite_casting(v);
	}
	
	player_movement_strafe_turn(v); 
	player_movement_forward_backward(v);

	draw_filled_rect(v, set_rect(0, 0, 420, 20), 0x000000);

	mlx_put_image_to_window(v->mlx, v->window, v->image.ptr,
			v->image.x_offset, v->image.y_offset);
	mlx_destroy_image(v->mlx, v->image.ptr);
		
	// Now the window is ready for adding stuff on top of the wolf3d map
	mlx_string_put(v->mlx, v->window, 100, 0, 0x00FFFFFF, "Wolf 3D");
	mlx_string_put(v->mlx, v->window, 0, 0, 0x00FFFFFF,
			itoa((int)(1.0 / v->frame_time)));
	mlx_string_put(v->mlx, v->window, 400, 0, 0x00FFFFFF, itoa(v->cur_sec));
	
	if (v->key.plus)
		v->plane.y += 0.1;
	if (v->key.minus)
		v->plane.y -= 0.1;

	//put_minimap(v);
	return (0);
}
