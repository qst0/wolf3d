/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoung <myoung@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 23:21:00 by myoung            #+#    #+#             */
/*   Updated: 2017/01/28 22:13:55 by myoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

void raycast_prep(t_view *v, t_raycast *cast)
{
	if (cast->side == 0)
		cast->perp_wall_dist = (cast->map_x - cast->ray_pos.x
				+ (1 - cast->step_x) / 2) / cast->ray_dir.x;
	else
		cast->perp_wall_dist = (cast->map_y - cast->ray_pos.y
				+ (1 - cast->step_y) / 2) / cast->ray_dir.y;
	cast->line_height = (int)(v->h / cast->perp_wall_dist);
	cast->draw_start = -cast->line_height / 2 + v->h / 2;
	if (cast->draw_start < 0)
		cast->draw_start = 0;
	cast->draw_end = cast->line_height / 2 + v->h / 2;
	if (cast->draw_end >= v->h)
		cast->draw_end = v->h - 1;
	cast->wall_x = cast->side == 0
		? cast->ray_pos.y + cast->perp_wall_dist * cast->ray_dir.y
		: cast->ray_pos.x + cast->perp_wall_dist * cast->ray_dir.x;
	cast->wall_x -= fake_floor(cast->wall_x);
	cast->tex_x = (int)(cast->wall_x * (double)(v->tex_width));
	cast->tex_x = v->tex_width - cast->tex_x - 1;
}

void TESTING_ZONE(t_view *v)
{
	if (!v->textures.test.ptr)
	{
		v->textures.test.ptr = mlx_xpm_file_to_image(v->mlx,
				"open24.xpm",
				&(v->textures.test.width),
				&(v->textures.test.height));
		v->textures.test.pixels = mlx_get_data_addr(
				&(v->textures.test.ptr),
				&(v->textures.test.bits_per_pixel),
				&(v->textures.test.size_line),
				&(v->textures.test.endian));
	}
	mlx_put_image_to_window(v->mlx, v->window, v->textures.test.ptr, 600, 400);
	int test;
	test = v->textures.test.pixels[0];

	if (v->key.plus)
		v->plane.y += 0.1;
	if (v->key.minus)
		v->plane.y -= 0.1;
	if (v->key.plus)
		v->plane.y += 0.1;
}

void raycast(t_view *v, int x)
{
	t_raycast	cast;
	int y;

	raycast_init(v, &cast, x);
	set_delta_dist(&cast);
	set_step_and_side_dist(&cast);
	raycast_dda(v, &cast);
	raycast_prep(v, &cast);

	y = cast.draw_start;
	while (y < cast.draw_end)
	{
		int color;
		int d;

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
	v->z_buff[x] = cast.perp_wall_dist;
}

int		loop_hook(t_view *v)
{
	int x;

	create_image(v->mlx, &v->image, v->w, v->h);
	x = -1;
	while (++x < v->w)
	{
		raycast(v, x);
	}
	player_movement_strafe_turn(v);
	player_movement_forward_backward(v);
	sprite_casting(v);
	draw_filled_rect(v, set_rect(0, 0, 440, 20), 0x000000);
	mlx_put_image_to_window(v->mlx, v->window, v->image.ptr,
			v->image.x_offset, v->image.y_offset);
	mlx_destroy_image(v->mlx, v->image.ptr);
	mlx_string_put(v->mlx, v->window, 100, 0, 0x00FFFFFF, "qst0 wolf3d demo");
	mlx_string_put(v->mlx, v->window, 0, 0, 0x00FFFFFF,
			itoa((int)(1.0 / v->frame_time)));
	mlx_string_put(v->mlx, v->window, 400, 0, 0x00FFFFFF, itoa(v->cur_sec));

	TESTING_ZONE(v);
	update_time(v);
	return (0);
}
