/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoung <myoung@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 10:11:53 by myoung            #+#    #+#             */
/*   Updated: 2017/01/12 15:20:02 by myoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <mlx.h>

#include "time.h"
#include <mach/clock.h>
#include <mach/mach.h>

#define MAP_WIDTH 24
#define MAP_HEIGHT 24

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

void		*mlx;
void		*window;
double		posX = 22;
double		posY = 12;
double		dirX = -1;
double		dirY = 0;
double		planeX = 0;
double		planeY = .66;

double		curTime = 0;
double		oldTime = 0;
int			cur_sec = 0;
int			past = 0;

int			w = 640;
int			h = 480;
int			mouse_x;
int			mouse_y;

double		rotSpeed = 0.00016666;
double		moveSpeed = 0.00016666;

void		*img;
char		*pixels;
int			bits_per_pixel;
int			size_line;
int			endian;

int			texWidth = 64;
int			texHeight = 64;
int			**texture;
//int			texture[8][texWidth * texHeight];


typedef	struct	s_img
{
	int		id;
	void	*ptr;
	char	*pixels;
	int		bit_per_pixel;
	int		line_size;
	int		endian;
	int		width;
	int		height;
	int		x_offset;
	int		y_offset;
}				t_img;

struct s_key
{
	int w:1;
	int a:1;
	int s:1;
	int d:1;
	int e:1;
	int q:1;
	int space:1;
	int one:1;
	//TODO this for all the keys, put it in libgfx.
};

struct s_key *key;

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

void	texture_init()
{
	texture = malloc(sizeof(int*) * 8);
	for(int i = 0; i < 8; i++)
	{
		texture[i] = malloc(sizeof(int) * texWidth * texHeight);
	}
	//generate some textures
	for(int x = 0; x < texWidth; x++)
		for(int y = 0; y < texHeight; y++)
		{
			int xorcolor = (x * 256 / texWidth) ^ (y * 256 / texHeight);
			//int xcolor = x * 256 / texWidth;
			int ycolor = y * 256 / texHeight;
			int xycolor = y * 128 / texHeight + x * 128 / texWidth;
			texture[0][texWidth * y + x] =
			   	65536 * 254 * (x != y && x != texWidth - y);
			//flat red texture with black cross
			texture[1][texWidth * y + x] =
			   	xycolor + 256 * xycolor + 65536 * xycolor;//sloped greyscale
			texture[2][texWidth * y + x] =
			   	256 * xycolor + 65536 * xycolor;//sloped yellow gradient
			texture[3][texWidth * y + x] =
			   	xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
			texture[4][texWidth * y + x] = 256 * xorcolor; //xor green
			texture[5][texWidth * y + x] = 65536 * 192 * (x % 16 && y % 16);
		   	//red bricks
			texture[6][texWidth * y + x] = 65536 * ycolor; //red gradient
			texture[7][texWidth * y + x] = 128 + 256 * 128 + 65536 * 128;
		   	//flat grey texture
		}
}

void	use_image(void)
{
	mlx_put_image_to_window(mlx, window, img, 0, 0);
	mlx_destroy_image(mlx, img);
}

void	create_image(void)
{
	img = mlx_new_image(mlx, w, h);
	pixels = mlx_get_data_addr(img, &bits_per_pixel, &size_line, &endian);
}

void	draw_point_to_img(int x, int y, int color)
{
	int i;

	i = (x * (bits_per_pixel / 8)) + (y * size_line); 
	pixels[i] = color;
	pixels[++i] = color >> 8;
	pixels[++i] = color >> 16;
}

void	player_turn(int way, int speed_mod)
{
	double oldDirX = dirX;
	double oldPlaneX = planeX;
	// Turn the character
	// Left is 1
	// Right is -1
	// Both camera direction and camera plane must be rotated
	
	dirX = dirX * cos(rotSpeed * way * speed_mod)
		- dirY * sin(rotSpeed * way * speed_mod);
	dirY = oldDirX * sin(rotSpeed * way * speed_mod)
		+ dirY * cos(rotSpeed * way * speed_mod);
	planeX = planeX * cos(rotSpeed * way * speed_mod)
		- planeY * sin(rotSpeed * way * speed_mod);
	planeY = oldPlaneX * sin(rotSpeed * way * speed_mod)
		+ planeY * cos(rotSpeed * way * speed_mod);
}

int		loop_hook(void *nothing_right_now)
{
	int x;
	double frame_time;
	struct timespec	ts;
	x = 0;

	ft_get_time(&ts);

	//hack to count the time passed in seconds	
	printf("curTime: %f\n", curTime / 100000000);
	int moment = (int)(curTime / 100000000);
	if (!past && moment == 9)
	{
		cur_sec++;
		past = 1;
	}
	if (past && moment == 0)
		past = 0;

	//timeing for input and FPS counter
	oldTime = curTime;
	curTime = ts.tv_nsec;
	frame_time = (double)(curTime - oldTime) / 1000000000.0;
	if (frame_time > 0)
	{
		moveSpeed = (frame_time * 3.7) / 1000; //constant value in squares/second
		rotSpeed = ((double)M_PI * frame_time / 1.25) / 1000; //constant value in radians/second
	}

	create_image();
	while (x < w)
	{
		//calculate ray postion and directions
		double cameraX = 2 * x / (double)w - 1; //x-coordinate in camera space
		double rayPosX = posX;
		double rayPosY = posY;
		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY * cameraX;
		
		//Which box of the map we're in
		int mapX = (int) rayPosX;
		int mapY = (int) rayPosY;
		//length of ray from current position to next x or y side
		double sideDistX;
		double sideDistY;
		//length of ray from one x or y side to the next x or y side
		double deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
		double deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
		double perpWallDist;
		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //Was there a wall hit?
		int side; //was a NS or EW wall hit?
		//calculate step and initial sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (rayPosX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - rayPosX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (rayPosY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - rayPosY) * deltaDistY;
		}
		//PREFORM DDA
		while (hit == 0)
		{
			//jump to the next map square, OR in x-dir, or in y-dir
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if the ray has hit a wall
			if (world_map[mapX][mapY] > 0)
				hit = 1;
		}
		
		//Calculate distance projected on camera direction
		//(oblique distance will have fisheye effect)
		if (side == 0) 
			perpWallDist = (mapX - rayPosX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - rayPosY + (1 - stepY) / 2) / rayDirY;
		
		//Calculate height of line to draw on screen
		int lineHeight = (int)(h /perpWallDist);
		
		//Calculate lowest and highest pixel to fill in the current stripe
		int drawStart = -lineHeight / 2 + h / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + h / 2;
		if (drawEnd >= h)
			drawEnd = h - 1;

		//texturing calculations
		int texNum = world_map[mapX][mapY] - 1;

		//calculate value of wallX, where exactly the wall was hit.
		double wallX;
		wallX = side == 0
			? rayPosY + perpWallDist * rayDirY
			: rayPosX + perpWallDist * rayDirX;
		wallX -= fake_floor(wallX);

		//x coord on the texture
		int texX = (int)(wallX * (double)(texWidth));
		if(side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
		if(side == 1 && rayDirY < 0) texX = texWidth - texX - 1;	

		for (int y = drawStart; y<drawEnd; y++)
		{
			int color;
			int d = y * 256 - h * 128 + lineHeight * 128;  //256 and 128 factors to avoid floats
			int texY = ((d * texHeight) / lineHeight) / 256;
			color = texture[texNum][texHeight * texY + texX];
			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if(side == 1)
				color = (color >> 1) & 8355711;
			draw_point_to_img(x, y, color);
		}
		
		/* floor and ceiling hacky glitch look */
/*
		for (int i = drawEnd; i < h; i++)
		{
			int color;
			int d = i * 256 - h * 128 + lineHeight * 128;  //256 and 128 factors to avoid floats
			int texY = ((d * texHeight) / lineHeight) / 256;
			color = texture[7][texHeight * texY + texX];
			draw_point_to_img(x, i, color);
		}

		for (int i = 0; i < drawStart; i++)
		{
			int color;
			int d = i * 256 - h * 128 + lineHeight * 128;  //256 and 128 factors to avoid floats
			int texY = ((d * texHeight) / lineHeight) / 256;
			color = texture[7][texHeight * texY + texX];
			draw_point_to_img(x, i, color);
		}
*/		
		//move character left / right (straife)	
		if (key->d)
		{
			if(world_map[(int)(posX + planeX * moveSpeed)][(int)posY] == 0)
				posX += planeX * moveSpeed;
		   	if(world_map[(int)posX][(int)(posY + planeY * moveSpeed)] == 0)	
				posY += planeY * moveSpeed;
		}
		if (key->a)
		{
			if(world_map[(int)(posX - planeX * moveSpeed)][(int)posY] == 0)
				posX -= planeX * moveSpeed;
		   	if(world_map[(int)posX][(int)(posY - planeY * moveSpeed)] == 0)	
				posY -= planeY * moveSpeed;
		}
		//move forward if no wall in front of you
		if (key->w)
		{
			if(world_map[(int)(posX + dirX * moveSpeed)][(int)posY] == 0)
				posX += dirX * moveSpeed;
		   	if(world_map[(int)posX][(int)(posY + dirY * moveSpeed)] == 0)	
				posY += dirY * moveSpeed;
		}
		if (key->s)
		{
			if(world_map[(int)(posX - dirX * moveSpeed)][(int)posY] == 0)
				posX -= dirX * moveSpeed;
			if(world_map[(int)posX][(int)(posY - dirY * moveSpeed)] == 0)
				posY -= dirY * moveSpeed;
		}
		if (key->e)
			player_turn(-1, 1);
		if (key->q)
			player_turn(1, 1);
		x++;
	}
	mlx_put_image_to_window(mlx, window, img, 0, 0);
	mlx_destroy_image(mlx, img);
	// Now the window is ready for adding stuff on top of the wolf3d map

	mlx_string_put(mlx, window, 100, 0, 0x00FFFFFF, "Wolf 3D");
	mlx_string_put(mlx, window, 0, 0, 0x00FFFFFF, itoa((int)(1.0 / frame_time)));
	mlx_string_put(mlx, window, 400, 0, 0x00FFFFFF, itoa(cur_sec));

	//animate test
	//make a row of blocks one at a time, of each type down row 10 each sec
	world_map[cur_sec % 22 + 1][10] = cur_sec % 7;

	return (0);
}

int		key_press_hook(int keycode, void *nothing)
{
	(void) nothing;
	if (keycode == 12)
		key->q = 1;
	if (keycode == 14)
		key->e = 1;
	if (keycode == 0)
		key->a = 1;
	if (keycode == 1)
		key->s = 1;
	if (keycode == 2)
		key->d = 1;
	if (keycode == 13)
		key->w = 1;
	if (keycode == 53)
		exit(0);
	return (0);
}

int		key_release_hook(int keycode, void *nothing)
{
	(void) nothing;
	if (keycode == 12)
		key->q = 0;
	if (keycode == 14)
		key->e = 0;
	if (keycode == 0)
		key->a = 0;
	if (keycode == 1)
		key->s = 0;
	if (keycode == 2)
		key->d = 0;
	if (keycode == 13)
		key->w = 0;
	return (0);
}

int		exit_hook(void *nothing)
{
	(void) nothing;
	exit(0);
}

int		motion_hook(int x, int y, void *nothing)
{
	(void) nothing;
	if (mouse_x < x)
		player_turn(-1, 500);
	else if (mouse_x > x)
		player_turn(1, 500);
	mouse_x = x;
	mouse_y = y;
	return (0);
}

void	set_hooks(void *mlx, void *window)
{
	mlx_do_key_autorepeatoff(mlx);
	mlx_hook(window, 2, 0, key_press_hook, 0000);
	mlx_hook(window, 3, 0, key_release_hook, 0000);
	//mlx_hook(window, 4, 0, mouse_press_hook, 0000);
	//mlx_hook(window, 5, 0, mouse_release_hook, 0000);
	mlx_hook(window, 6, 0, motion_hook, 0000);
	//mlx_hook(window, 12, 0, expose_hook, 0000);
	mlx_hook(window, 17, 0, exit_hook, 0000);
}

int main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	texture_init();
	key = (struct s_key*)malloc(sizeof(struct s_key));
	mlx = mlx_init();
	window = mlx_new_window(mlx, w, h, "Wolf3d");
	set_hooks(mlx, window);
	mlx_loop_hook(mlx, loop_hook, 0);
	mlx_loop(mlx);
	return (0);
}
