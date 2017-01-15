/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoung <myoung@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 10:11:53 by myoung            #+#    #+#             */
/*   Updated: 2017/01/14 18:13:14 by myoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

#define MAP_WIDTH 24
#define MAP_HEIGHT 24

void	put_minimap(t_view *v);

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

/*
 * posX, posY = x and y start postition
 * dirX, dirY = initial direction vector
 * planeX, planeY = the 2d raycater version of camera plane
 * time, oldtime = time of the current and previous frame
 */

int		nlen(int n)
{
	int len = 0;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*itoa(int i)
{
	char *result;
	int len;

	len = nlen(i);
	result = (char*)malloc(len + 1);
	result[len--] = '\0';
	while (i)
	{
		result[len--] = i % 10 + '0';
		i /= 10;
	}
	return (result);
}

void	ft_get_time(struct timespec *ts)
{
	clock_serv_t		cclock;
	mach_timespec_t		mts;

	host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
	clock_get_time(cclock, &mts);
	mach_port_deallocate(mach_task_self(), cclock);
	ts->tv_sec = mts.tv_sec;
	ts->tv_nsec = mts.tv_nsec;
}

int		fake_floor(double x)
{
	return (int)(x + 100000) - 100000;
}

void	texture_init(t_view *v)
{
	v->texture = malloc(sizeof(int*) * 8);
	v->tex_width = 64;
	v->tex_height = 64;
	for(int i = 0; i < 8; i++)
	{
		v->texture[i] = malloc(sizeof(int) * v->tex_width * v->tex_height);
	}
	//generate some textures
	for(int x = 0; x < v->tex_width; x++)
		for(int y = 0; y < v->tex_height; y++)
		{
			int xorcolor = (x * 256 / v->tex_width) ^ (y * 256 / v->tex_height);
			//int xcolor = x * 256 / tex_width;
			int ycolor = y * 256 / v->tex_height;
			int xycolor = y * 128 / v->tex_height + x * 128 / v->tex_width;
			v->texture[0][v->tex_width * y + x] =
			   	65536 * 254 * (x != y && x != v->tex_width - y);
			//flat red texture with black cross
			v->texture[1][v->tex_width * y + x] =
			   	xycolor + 256 * xycolor + 65536 * xycolor;//sloped greyscale
			v->texture[2][v->tex_width * y + x] =
			   	256 * xycolor + 65536 * xycolor;//sloped yellow gradient
			v->texture[3][v->tex_width * y + x] =
			   	xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
			v->texture[4][v->tex_width * y + x] = 256 * xorcolor; //xor green
			v->texture[5][v->tex_width * y + x] = 65536 * 192 * (x % 16 && y % 16);
		   	//red bricks
			v->texture[6][v->tex_width * y + x] = 65536 * ycolor; //red gradient
			v->texture[7][v->tex_width * y + x] = 128 + 256 * 128 + 65536 * 128;
		   	//flat grey texture
		}
}

void	use_image(t_view *v)
{
	mlx_put_image_to_window(v->mlx, v->window, v->image.ptr,
		   	v->image.x_offset, v->image.y_offset);
	mlx_destroy_image(v->mlx, v->image.ptr);
}

void	create_image(t_view *v)
{
	v->image.ptr = mlx_new_image(v->mlx, v->w, v->h);
	v->image.pixels = mlx_get_data_addr(v->image.ptr,
			&v->image.bits_per_pixel,
			&v->image.size_line,
			&v->image.endian);
}

void	draw_point_to_img(t_img *img, int x, int y, int color)
{
	int i;

	i = (x * (img->bits_per_pixel / 8)) + (y * img->size_line); 
	img->pixels[i] = color;
	img->pixels[++i] = color >> 8;
	img->pixels[++i] = color >> 16;
}

void	player_turn(t_view *v, int way, int speed_mod)
{
	double old_dir_x = v->dir.x;
	double old_plane_x = v->plane.x;
	// Turn the character
	// Left is 1
	// Right is -1
	// Both camera direction and camera plane must be rotated
	
	v->dir.x = v->dir.x * cos(v->rot_speed * way * speed_mod)
		- v->dir.y * sin(v->rot_speed * way * speed_mod);
	v->dir.y = old_dir_x * sin(v->rot_speed * way * speed_mod)
		+ v->dir.y * cos(v->rot_speed * way * speed_mod);
	v->plane.x = v->plane.x * cos(v->rot_speed * way * speed_mod)
		- v->plane.y * sin(v->rot_speed * way * speed_mod);
	v->plane.y = old_plane_x * sin(v->rot_speed * way * speed_mod)
		+ v->plane.y * cos(v->rot_speed * way * speed_mod);
}

int		loop_hook(t_view *v)
{
	int x;
	double frame_time;
	struct timespec	ts;
	int moment = (int)(v->cur_time / 100000000);

	x = 0;
	ft_get_time(&ts);
	//hack to count the time passed in seconds	
	if (!v->past && moment == 9)
	{
		v->cur_sec++;
		v->past = 1;
	}
	if (v->past && moment == 0)
		v->past = 0;

	//timeing for input and FPS counter
	v->old_time = v->cur_time;
	v->cur_time = ts.tv_nsec;
	frame_time = (double)(v->cur_time - v->old_time) / 1000000000.0;
	if (frame_time > 0)
	{
		//constant value in squares/second
		v->move_speed = (frame_time * 3.7) / 1000;
		//constant value in radians/second	
		v->rot_speed = ((double)M_PI * frame_time / 1.25) / 1000;
	}
	create_image(v);

	while (x < v->w)
	{
		t_raycast	cast;

		cast.camera.x = 2 * x / (double)v->w - 1;
		cast.ray_pos.x = v->pos.x;
		cast.ray_pos.y = v->pos.y;
		cast.ray_dir.x = v->dir.x + v->plane.x * cast.camera.x;
		cast.ray_dir.y = v->dir.y + v->plane.y * cast.camera.x;

		//Which box of the map we're in
		cast.map_x = (int)v->pos.x;
		cast.map_y = (int)v->pos.y;
		
		//length of ray from one x or y side to the next x or y side
		cast.delta_dist.x = sqrt(1 + (cast.ray_dir.y * cast.ray_dir.y)
				/ (cast.ray_dir.x * cast.ray_dir.x));
		cast.delta_dist.y = sqrt(1 + (cast.ray_dir.x * cast.ray_dir.x)
				/ (cast.ray_dir.y * cast.ray_dir.y));

		cast.hit = 0;

		//calculate step and initial sideDist
		if (cast.ray_dir.x < 0)
		{
			cast.step_x = -1;
			cast.side_dist.x = (cast.ray_pos.x - cast.map_x) * cast.delta_dist.x;
		}
		else
		{
			cast.step_x = 1;
			cast.side_dist.x = (cast.map_x + 1.0 - cast.ray_pos.x)
				* cast.delta_dist.x;
		}
		if (cast.ray_dir.y < 0)
		{
			cast.step_y = -1;
			cast.side_dist.y = (cast.ray_pos.y - cast.map_y) * cast.delta_dist.y;
		}
		else
		{
			cast.step_y = 1;
			cast.side_dist.y = (cast.map_y + 1.0 - cast.ray_pos.y)
				* cast.delta_dist.y;
		}

		//PREFORM DDA
		while (cast.hit == 0)
		{
			//jump to the next map square, OR in x-dir, or in y-dir
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

		//Calculate distance projected on camera direction
		//(oblique distance will have fisheye effect)
		if (cast.side == 0) 
			cast.perp_wall_dist = (cast.map_x - cast.ray_pos.x 
					+ (1 - cast.step_x) / 2) / cast.ray_dir.x;
		else
			cast.perp_wall_dist = (cast.map_y - cast.ray_pos.y 
					+ (1 - cast.step_y) / 2) / cast.ray_dir.y;
			
		//Calculate height of line to draw on screen
		int lineHeight = (int)(v->h / cast.perp_wall_dist);

		//Calculate lowest and highest pixel to fill in the current stripe
		int drawStart = -lineHeight / 2 + v->h / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + v->h / 2;
		if (drawEnd >= v->h)
			drawEnd = v->h - 1;

		//texturing calculations
		int texNum = world_map[cast.map_x][cast.map_y] - 1;

		//calculate value of wallX, where exactly the wall was hit.
		double wallX;
		wallX = cast.side == 0
			? cast.ray_pos.y + cast.perp_wall_dist * cast.ray_dir.y
			: cast.ray_pos.x + cast.perp_wall_dist * cast.ray_dir.x;
		wallX -= fake_floor(wallX);

		//x coord on the texture
		int texX = (int)(wallX * (double)(v->tex_width));
		if (cast.side == 0 && cast.ray_dir.x > 0)
			texX = v->tex_width - texX - 1;
		if (cast.side == 1 && cast.ray_dir.y < 0)
			texX = v->tex_width - texX - 1;	
		
		for (int y = drawStart; y < drawEnd; y++)
		{
			int color;
			int d = y * 256 - v->h * 128 + lineHeight * 128;
			//256 and 128 factors to avoid floats
			int texY = ((d * v->tex_height) / lineHeight) / 256;
			color = v->texture[texNum][v->tex_height * texY + texX];
			//make color darker for y-sides:
			// R, G and B byte each divided through two with
			// a "shift" and an "and"
			if (cast.side == 1)
				color = (color >> 1) & 8355711;
			draw_point_to_img(&v->image, x, y, color);
		}
		
		/* floor and ceiling hacky glitch look */
/*
		for (int i = drawEnd; i < v->h; i++)
		{
			int color;
			int d = i * 256 - v->h * 128 + lineHeight * 128;
			int texY = ((d * v->tex_height) / lineHeight) / 256;
			color = v->texture[7][v->tex_height * texY + texX];
			draw_point_to_img(&v->image, x, i, color);
		}

		for (int i = 0; i < drawStart; i++)
		{
			int color;
			int d = i * 256 - h * 128 + lineHeight * 128;
			int texY = ((d * tex_height) / lineHeight) / 256;
			color = texture[7][tex_height * texY + texX];
			draw_point_to_img(&v->image, x, i, color);
		}
*/		
		//move character left / right (straife)	
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

	put_minimap(v);
	mlx_string_put(v->mlx, v->window, 100, 0, 0x00FFFFFF, "Wolf 3D");
	mlx_string_put(v->mlx, v->window, 0, 0, 0x00FFFFFF,
			itoa((int)(1.0 / frame_time)));
	mlx_string_put(v->mlx, v->window, 400, 0, 0x00FFFFFF, itoa(v->cur_sec));

	//animate test
	//make a row of blocks one at a time, of each type down row 10 each sec
	world_map[v->cur_sec % 22 + 1][10] = v->cur_sec % 7;

	return (0);
}


int		key_press_hook(int keycode, t_view *v)
{
	if (keycode == 12)
		v->key.q = 1;
	if (keycode == 14)
		v->key.e = 1;
	if (keycode == 0)
		v->key.a = 1;
	if (keycode == 1)
		v->key.s = 1;
	if (keycode == 2)
		v->key.d = 1;
	if (keycode == 13)
		v->key.w = 1;
	if (keycode == 53)
		exit(0);
	return (0);
}

int		key_release_hook(int keycode, t_view *v)
{
	if (keycode == 12)
		v->key.q = 0;
	if (keycode == 14)
		v->key.e = 0;
	if (keycode == 0)
		v->key.a = 0;
	if (keycode == 1)
		v->key.s = 0;
	if (keycode == 2)
		v->key.d = 0;
	if (keycode == 13)
		v->key.w = 0;
	return (0);
}

int		exit_hook(t_view *v)
{
	(void) v;
	exit(0);
}

int		motion_hook(int x, int y, t_view *v)
{
	if (v->mouse_x < x)
		player_turn(v, -1, 500);
	else if (v->mouse_x > x)
		player_turn(v, 1, 500);
	v->mouse_x = x;
	v->mouse_y = y;
	return (0);
}

void	set_hooks(t_view *v)
{
	mlx_do_key_autorepeatoff(v->mlx);
	mlx_hook(v->window, 2, 0, key_press_hook, v);
	mlx_hook(v->window, 3, 0, key_release_hook, v);
	//mlx_hook(v->window, 4, 0, mouse_press_hook, v);
	//mlx_hook(v->window, 5, 0, mouse_release_hook, v);
	mlx_hook(v->window, 6, 0, motion_hook, v);
	//mlx_hook(v->window, 12, 0, expose_hook, v);
	mlx_hook(v->window, 17, 0, exit_hook, v);
}

void *minimap;

void	draw_filled_square(t_view *v, t_2dp p, int size, int color)
{
	int y;
	int x;

	y = 0;
	x = 0;
	while (y < size)
	{
		while (x < size)
		{
			mlx_pixel_put(v->mlx, minimap, x + p.x, y + p.y, color);
			x++;
		}
		x = 0;
		y++;
	}
}

void	put_minimap(t_view *v)
{
	int y;
	int x;
	t_2dp	p;

	x = 0,
	y = 0;

	mlx_clear_window(v->mlx, minimap);
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
}

void	create_minimap(t_view *v)
{
	minimap = mlx_new_window(v->mlx, 240, 240, "Minimap");
	put_minimap(v);
}

t_view	*create_view(int w, int h, char *title)
{
	t_view *view;

	view = (t_view*)malloc(sizeof(t_view));
	view->mlx = mlx_init();
	//make sure all keys are zero'd?
	view->w = w;
	view->h = h;
	view->pos.x = 22;
	view->pos.y = 12;
	view->dir.x = -1;
	view->dir.y = 0;
	view->plane.x = 0;
	view->plane.y = .66;
	view->cur_time = 0;
	view->old_time = 0;
	view->cur_sec = 0;
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

void	wolf(void)
{
	void *view;

	view = create_view(960, 600, "Wolf3d");	
}

int main(int argc, char **argv)
{
	if (argc != 1 && argv)
		exit(1);
	wolf();
	return (0);
}
