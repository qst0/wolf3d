/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoung <myoung@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 05:47:32 by myoung            #+#    #+#             */
/*   Updated: 2017/01/17 07:02:50 by myoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

int		world_map[MAP_WIDTH][MAP_HEIGHT]=
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,4,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,5,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,2,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void	*minimap;

/* Left is 1, right is -1, both camera direction and plane must be rotated */
void	player_turn(t_view *v, int way, int speed_mod)
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

int		loop_hook(t_view *v)
{
	int x;
	
	update_time(v);
	create_image(v->mlx, &v->image, v->w, v->h);
	x = 0;
	while (x < v->w)
	{
		t_raycast	cast;

		cast.camera.x = 2 * x / (double)v->w - 1;
		cast.ray_pos.x = v->pos.x;
		cast.ray_pos.y = v->pos.y;
		cast.ray_dir.x = v->dir.x + v->plane.x * cast.camera.x;
		cast.ray_dir.y = v->dir.y + v->plane.y * cast.camera.x;
		cast.map_x = (int)v->pos.x;
		cast.map_y = (int)v->pos.y;
		
		set_delta_dist(&cast);
		cast.hit = 0;
		set_step_and_side_dist(&cast);

		//Preform DDA - Digital Differential Analysis
		while (cast.hit == 0)
		{
			//jump to the next map square in x-dir, or in y-dir
			if (cast.side_dist.x < cast.side_dist.y)
			{
				cast.side_dist.x += cast.delta_dist.x;
				cast.map_x += cast.step_x;
				cast.side = 0;
			}
			else
			{
				cast.side_dist.y += cast.delta_dist.y;
				cast.map_y += cast.step_y;
				cast.side = 1;
			}
			//Check if the ray has hit a wall
			if (world_map[cast.map_x][cast.map_y] > 0)
				cast.hit = 1;
		}

		/* Calculate distance projected on camera direction
		 * (oblique distance will have fisheye effect) */
		if (cast.side == 0) 
			cast.perp_wall_dist = (cast.map_x - cast.ray_pos.x 
					+ (1 - cast.step_x) / 2) / cast.ray_dir.x;
		else
			cast.perp_wall_dist = (cast.map_y - cast.ray_pos.y 
					+ (1 - cast.step_y) / 2) / cast.ray_dir.y;
			
		/* Calculate height of line to draw on screen */
		cast.line_height = (int)(v->h / cast.perp_wall_dist);

		/* Calculate lowest and highest pixel to fill in the current stripe */
		cast.draw_start = -cast.line_height / 2 + v->h / 2;
		if (cast.draw_start < 0)
			cast.draw_start = 0;
		cast.draw_end = cast.line_height / 2 + v->h / 2;
		if (cast.draw_end >= v->h)
			cast.draw_end = v->h - 1;

		/* calculate value of wall_x, where exactly the wall was hit */
		cast.wall_x = cast.side == 0
			? cast.ray_pos.y + cast.perp_wall_dist * cast.ray_dir.y
			: cast.ray_pos.x + cast.perp_wall_dist * cast.ray_dir.x;
		cast.wall_x -= fake_floor(cast.wall_x);

		/* x coord on the texture */
		cast.tex_x = (int)(cast.wall_x * (double)(v->tex_width));
		if (cast.side == 0 && cast.ray_dir.x > 0)
			cast.tex_x = v->tex_width - cast.tex_x - 1;
		if (cast.side == 1 && cast.ray_dir.y < 0)
			cast.tex_x = v->tex_width - cast.tex_x - 1;	

		/* Draw the wall sliver */	
		for (int y = cast.draw_start; y < cast.draw_end; y++)
		{
			int color;
			int d;
			
			d = y * 256 - v->h * 128 + cast.line_height * 128;
			//256 and 128 factors to avoid floats
			cast.tex_y = ((d * v->tex_height) / cast.line_height) / 256;
			color = v->texture[world_map[cast.map_x][cast.map_y] - 1]
				[v->tex_height * cast.tex_y + cast.tex_x];
			if (cast.side == 1)
				color = (color >> 1) & 0x7F7F7F; //8355711;
			draw_point_to_img(&v->image, x, y, color);
		}
		
		/* floor and ceiling hacky glitch look */
		for (int y = cast.draw_end; y < v->h; y++)
		{
			int color;
			int d;
			   
			d = y * 256 - v->h * 128 + cast.line_height * 128;
			cast.tex_y = ((d * v->tex_height) / cast.line_height) / 256;
			color = v->texture[7]
				[v->tex_height * cast.tex_y + cast.tex_x];
			if (cast.side == 1)
				color = (color >> 1) & 0x7F7F7F; //8355711;
			draw_point_to_img(&v->image, x, y, color);
		}

		for (int y = 0; y < cast.draw_start; y++)
		{
			int color;
			int d;
		   
			d = y * 256 - v->h * 128 + cast.line_height * 128;
			cast.tex_y = ((d * v->tex_height) / cast.line_height) / 256;
			color = v->texture[0][v->tex_height * cast.tex_y + cast.tex_x];
			if (cast.side == 1)
				color = (color >> 1) & 0x7F7F7F; //8355711;
			draw_point_to_img(&v->image, x, y, color);
		}

		//move character left / right (straife)
		
		//We are done with cast.
		if (v->key.d)
		{
			if (world_map[(int)(v->pos.x + v->plane.x * v->move_speed)]
					[(int)v->pos.y] == 0)
				v->pos.x += v->plane.x * v->move_speed;
		   	if (world_map[(int)v->pos.x]
					[(int)(v->pos.y + v->plane.y * v->move_speed)] == 0)	
				v->pos.y += v->plane.y * v->move_speed;
		}
		if (v->key.a)
		{
			if (world_map[(int)(v->pos.x - v->plane.x * v->move_speed)]
					[(int)v->pos.y] == 0)
				v->pos.x -= v->plane.x * v->move_speed;
		   	if (world_map[(int)v->pos.x]
					[(int)(v->pos.y - v->plane.y * v->move_speed)] == 0)	
				v->pos.y -= v->plane.y * v->move_speed;
		}
		//move forward if no wall in front of you
		if (v->key.w)
		{
			if(world_map[(int)(v->pos.x + v->dir.x * v->move_speed)]
					[(int)v->pos.y] == 0)
				v->pos.x += v->dir.x * v->move_speed;
		   	if(world_map[(int)v->pos.x]
					[(int)(v->pos.y + v->dir.y * v->move_speed)] == 0)	
				v->pos.y += v->dir.y * v->move_speed;
		}
		if (v->key.s)
		{
			
			if(world_map[(int)(v->pos.x - v->dir.x * v->move_speed)]
					[(int)v->pos.y] == 0)
				v->pos.x -= v->dir.x * v->move_speed;
		   	if(world_map[(int)v->pos.x]
					[(int)(v->pos.y - v->dir.y * v->move_speed)] == 0)	
				v->pos.y -= v->dir.y * v->move_speed;
		}
		//rotate
		if (v->key.e)
			player_turn(v, -1, 1);
		if (v->key.q)
			player_turn(v, 1, 1);
		x++;
	}
	mlx_put_image_to_window(v->mlx, v->window, v->image.ptr,
			v->image.x_offset, v->image.y_offset);
	mlx_destroy_image(v->mlx, v->image.ptr);
	
	
	
	// Now the window is ready for adding stuff on top of the wolf3d map
	mlx_string_put(v->mlx, v->window, 100, 0, 0x00FFFFFF, "Wolf 3D");
	mlx_string_put(v->mlx, v->window, 0, 0, 0x00FFFFFF,
			itoa((int)(1.0 / v->frame_time)));
	mlx_string_put(v->mlx, v->window, 400, 0, 0x00FFFFFF, itoa(v->cur_sec));

	//animate test
	//make a row of blocks one at a time, of each type down row 10 each sec
	world_map[v->cur_sec % 22 + 1][10] = v->cur_sec % GEN_TEX_COUNT;

	put_minimap(v);
	return (0);
}

void	use_image(t_view *v)
{
	mlx_put_image_to_window(v->mlx, v->window, v->image.ptr,
		   	v->image.x_offset, v->image.y_offset);
	mlx_destroy_image(v->mlx, v->image.ptr);
}

void	create_image(void	*mlx, t_img *image, int w, int h)
{
	image->ptr = mlx_new_image(mlx, w, h);
	image->pixels = mlx_get_data_addr(image->ptr,
			&image->bits_per_pixel,
			&image->size_line,
			&image->endian);
}

void	draw_point_to_img(t_img *img, int x, int y, int color)
{
	int i;

	i = (x * (img->bits_per_pixel / 8)) + (y * img->size_line); 
	img->pixels[i] = color;
	img->pixels[++i] = color >> 8;
	img->pixels[++i] = color >> 16;
}

void	draw_filled_square(t_view *v, t_2dp p, int size, int color)
{
	int y;
	int x;

	y = -1;
	x = -1;
	while (++y < size)
	{
		while (++x < size)
			draw_point_to_img(&v->minimap_image, x + p.x, y + p.y, color);
		x = -1;
	}
}

void	put_minimap(t_view *v)
{
	int y;
	int x;
	t_2dp	p;

	x = 0,
	y = 0;

	create_image(v->mlx, &v->minimap_image, 240, 240);
	while (y < 24)
	{
		while (x < 24)
		{
			p.x = x * 10;
			p.y = y * 10;
 			draw_filled_square(v, p, 10, world_map[y][x] >= 1 ? 0xFF : 0xFFFFFF);
			x++;
		}
		x = 0;
		y++;
	}
	//backwards?
	p.x = v->pos.y * 10;
	p.y = v->pos.x * 10;
	draw_filled_square(v, p, 2, 0xFF0000);
	mlx_put_image_to_window(v->mlx, v->minimap_window,
		   	v->minimap_image.ptr, 0, 0);
	mlx_destroy_image(v->mlx, v->minimap_image.ptr);
}

void	create_minimap(t_view *v)
{
	v->minimap_window = mlx_new_window(v->mlx, 240, 240, "Minimap");
	put_minimap(v);
}

t_view	*create_view(int w, int h, char *title)
{
	t_view *view;

	view = (t_view*)malloc(sizeof(t_view));
	view->mlx = mlx_init();
	keys_init(&view->key);
	view->w = w;
	view->h = h;
	view->pos.x = 22;
	view->pos.y = 12;
	view->dir.x = -1;
	view->dir.y = 0;
	view->plane.x = 0;
	view->plane.y = .66;
	view->cur_sec = 0;
	view->cur_time = 0;
	view->old_time = 0;
	view->past = 0;
	view->mouse_x = 0;
	view->mouse_y = 0;
	view->rot_speed = 0.00016666;
	view->move_speed = 0.00016666;
	view->window = mlx_new_window(view->mlx, w, h, title);	
	texture_init(view);
	create_minimap(view);
	set_hooks(view);
	mlx_loop_hook(view->mlx, loop_hook, view);
	mlx_loop(view->mlx);
	return (view);
}
