/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoung <myoung@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 05:47:32 by myoung            #+#    #+#             */
/*   Updated: 2017/01/18 05:35:42 by myoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

int		world_map[MAP_WIDTH][MAP_HEIGHT]=
/*{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,-2,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,4,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,5,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,-2,2,2,0,0,0,0,2,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,1,0,0,0,-2,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,-1,-1,-1,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,-1,-1,-1,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,4,0,0,0,0,4,0,0,-1,-1,-1,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
*/
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},	
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int freeze;
int	froze_a;
int	froze_s;
int	froze_d;
int	froze_w;








# define SPRITE_COUNT 2

typedef struct		s_sprite
{
	t_2dp	pos;
	int		texture;
}					t_sprite;

t_sprite	sprite[SPRITE_COUNT];
double		z_buff[WINDOW_WIDTH];

int			sprite_order[SPRITE_COUNT];
double		sprite_dist[SPRITE_COUNT];

void	sprite_init()
{
	sprite[0].pos.x = 10;
	sprite[0].pos.y = 10;
	sprite[0].texture = 7;

	sprite[1].pos.x = 2;
	sprite[1].pos.y = 2;
	sprite[1].texture = 7;
}








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

/* SORTING */

void	ft_swap_int(int *a, int *b)
{
	int temp;
	
	temp = *a;
	*a = *b;
	*b = temp;
}

void	ft_swap_double(double *a, double *b)
{
	int temp;
	
	temp = *a;
	*a = *b;
	*b = temp;
}

void	comb_sort(int *order, double *dist, int amount)
{
	int gap;
	int	swapped;
	int i;

	gap = amount;
	swapped = 0;
	while (gap > 1 || swapped)
	{
		gap = (gap * 10) / 13;
		gap = (gap == 9 || gap == 10) ? 11 : gap;
		gap = gap < 1 ? 1 : gap;
		swapped = 0;
		i = -1;
		while(++i < amount - gap)
		{
			int j = i + gap;
			if (dist[i] < dist[j])
			{
				ft_swap_double(&dist[i], &dist[j]);
				ft_swap_int(&order[i], &order[j]);
				swapped = 1;
			}
		}
	}
}

/* LOOP HOOK */

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
			color = v->texture[world_map[cast.map_x % 24][cast.map_y % 24] - 1]
				[v->tex_height * cast.tex_y + cast.tex_x];
			if (cast.side == 1)
				color = (color >> 1) & 0x7F7F7F; //8355711;
			draw_point_to_img(&v->image, x, y, color);
		}

		// Set the z_buff for the sprite casting
		z_buff[x] = cast.perp_wall_dist;

		/* Floor Casting */
		t_2dp floor_wall;

		if (cast.side == 0 && cast.ray_dir.x > 0) 
		{
			floor_wall.x = cast.map_x;
			floor_wall.y = cast.map_y + cast.wall_x;
		}
		else if (cast.side == 0 && cast.ray_dir.x < 0)
		{
			floor_wall.x = cast.map_x + 1.0;
			floor_wall.y = cast.map_y + cast.wall_x;
		}
		else if (cast.side == 1 && cast.ray_dir.y > 0)
		{
			floor_wall.x = cast.map_x + cast.wall_x;
			floor_wall.y = cast.map_y;
		}
		else
		{
			floor_wall.x = cast.map_x + cast.wall_x;
			floor_wall.y = cast.map_y + 1.0;
		}

		double dist_wall;
		double dist_player;
		double cur_dist;

		dist_wall = cast.perp_wall_dist;
		dist_player = 0.0;

		if (cast.draw_end < 0)
			cast.draw_end = v->h;

		int y;

		y = cast.draw_end;
		while (++y < v->h)
		{
			cur_dist = v->h / (2.0 * y - v->h);

			double weight = (cur_dist - dist_player) / (dist_wall - dist_player);

			t_2dp cur_floor;
			cur_floor.x = weight * floor_wall.x + (1.0 - weight) * v->pos.x;
			cur_floor.y = weight * floor_wall.y + (1.0 - weight) * v->pos.y;

			int floor_tex_x;
			int floor_tex_y;
			floor_tex_x = (int)(cur_floor.x * v->tex_width) % v->tex_width;
			floor_tex_y = (int)(cur_floor.y * v->tex_height) % v->tex_height;

			int floor_tex;

			floor_tex = (int)(cur_floor.x) % 2 ? 7 : 5;
			floor_tex = (int)cur_floor.y == 10 ? 3 : floor_tex;
			floor_tex = world_map[(int)cur_floor.x][(int)cur_floor.y] == -1 ? 4 : floor_tex;
			floor_tex = world_map[(int)cur_floor.x][(int)cur_floor.y] == -2 ? 1 : floor_tex;

			int color;

			color = v->texture[floor_tex][v->tex_width * floor_tex_y + floor_tex_x];
			draw_point_to_img(&v->image, x, y, color);
			color = v->texture[6][v->tex_width * floor_tex_y + floor_tex_x];
			draw_point_to_img(&v->image, x, v->h - y, color);
		}	















		//SPRITE CASTING
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
			sprite_pos.x = sprite[sprite_order[i]].pos.x - v->pos.x;
			sprite_pos.y = sprite[sprite_order[i]].pos.y - v->pos.y;

			double inv_det = 1.0 / (v->plane.x * v->dir.y - v->dir.x * v->plane.y);

			t_2dp transform;
			transform.x = inv_det * (v->dir.y * sprite_pos.x - v->dir.x * sprite_pos.y);
			transform.y = inv_det * (-v->plane.y * sprite_pos.x + v->plane.x * sprite_pos.y); // Depth inside the screen

			int sprite_screen_x = (int)((v->w / 2) * (1 + transform.x / transform.y));

			int sprite_height = (int)(v->h / transform.y);
			sprite_height = sprite_height < 0 ? -sprite_height : sprite_height; //ABS

			int draw_start_y = -sprite_height / 2 + v->h / 2;
			if (draw_start_y < 0)
				draw_start_y = 0;
			int draw_end_y = sprite_height / 2 + v->h / 2;
			if (draw_end_y >= v->h)
				draw_end_y = v->h - 1;

			int sprite_width = (int)(v->h / transform.y);
			sprite_width = sprite_width < 0 ? -sprite_width : sprite_width; //ABS
			int draw_start_x = -sprite_width / 2 + sprite_screen_x;
			if (draw_start_x < 0)
				draw_start_x = 0;
			int draw_end_x = sprite_width / 2 + sprite_screen_x;
			if (draw_end_x >= v->w)
				draw_end_x = v->w - 1;

			int j = draw_start_x - 1;
			while (++j < draw_end_x)
			{
				int tex_x = (int)(256 * (j - (-sprite_width / 2 + sprite_screen_x)) * v->tex_width / sprite_width / 256);
				if (transform.y > 0 && j > 0 && j < v->w && transform.y < z_buff[j])
				{
					int y = draw_start_y - 1;
					while (++y < draw_end_y)
					{
						int d = y * 256 - v->h * 128 + sprite_height * 128;
						int tex_y = ((d * v->tex_height) / sprite_height) / 256;
						int color = v->texture[sprite[sprite_order[i]].texture][v->tex_width * tex_y + tex_x];
						if (color != 0xFF)
							draw_point_to_img(&v->image, j, y, color);
					}
				}
			}	
		}




















		/* floor and ceiling hacky glitch look */
		/*
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
		*/


		//We are done with cast.
		//move character left / right (straife)	
		
		int cur_tex = world_map[(int)v->pos.x][(int)v->pos.y];
		
		if ((freeze && froze_d) || v->key.d)
		{
			if (world_map[(int)(v->pos.x + v->plane.x * v->move_speed)]
					[(int)v->pos.y] < 1)
				v->pos.x += v->plane.x * v->move_speed;
		   	if (world_map[(int)v->pos.x]
					[(int)(v->pos.y + v->plane.y * v->move_speed)] < 1)	
				v->pos.y += v->plane.y * v->move_speed;
		}
		if ((freeze && froze_a) || v->key.a)
		{
			if (world_map[(int)(v->pos.x - v->plane.x * v->move_speed)]
					[(int)v->pos.y] < 1)
				v->pos.x -= v->plane.x * v->move_speed;
		   	if (world_map[(int)v->pos.x]
					[(int)(v->pos.y - v->plane.y * v->move_speed)] < 1)	
				v->pos.y -= v->plane.y * v->move_speed;
		}
		//move forward if no wall in front of you
		if ((freeze && froze_w) || v->key.w)
		{
			if(world_map[(int)(v->pos.x + v->dir.x * v->move_speed)]
					[(int)v->pos.y] < 1)
				v->pos.x += v->dir.x * v->move_speed;
		   	if(world_map[(int)v->pos.x]
					[(int)(v->pos.y + v->dir.y * v->move_speed)] < 1)	
				v->pos.y += v->dir.y * v->move_speed;
		}
		if ((freeze && froze_s) || v->key.s)
		{
			
			if(world_map[(int)(v->pos.x - v->dir.x * v->move_speed)]
					[(int)v->pos.y] < 1)
				v->pos.x -= v->dir.x * v->move_speed;
		   	if(world_map[(int)v->pos.x]
					[(int)(v->pos.y - v->dir.y * v->move_speed)] < 1)	
				v->pos.y -= v->dir.y * v->move_speed;
		}

		//rotate
		if (v->key.e)
			player_turn(v, -1, 1);
		if (v->key.q)
			player_turn(v, 1, 1);
		x++;

		//Slide on ice
		if(cur_tex == -1 && !freeze)
		{
			freeze = 1;
			froze_a = v->key.a;
			froze_d = v->key.d;
			froze_w = v->key.w;
			froze_s = v->key.s;
		}
		else if (cur_tex != -1 && freeze)
			freeze = 0;
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
	//world_map[v->cur_sec % 22 + 1][10] = v->cur_sec % GEN_TEX_COUNT;

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
	draw_filled_square(v, p, 5, 0xFF0000);
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
	sprite_init();
	view->w = w;
	view->h = h;
	freeze = 0;
	froze_a = 0;
	froze_d = 0;
	froze_s = 0;
	froze_w = 0;
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
