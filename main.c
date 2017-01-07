/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoung <myoung@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 10:11:53 by myoung            #+#    #+#             */
/*   Updated: 2017/01/03 18:13:09 by myoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MAP_WIDTH 24
#define MAP_HEIGHT 24

#include <stdio.h>
#include <math.h>
#include <mlx.h>

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
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,2,4,0,0,0,1},
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
double		time = 0;
double		oldTime = 0;
int			h = 384;
int			w = 512;

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

int		loop_hook(void *nothing_right_now)
{
	int x;
	x = 0;

	while (x < w)
	{
		//printf("LOOP, THERE IT IS! x:%d\n", x);
		//calculate ray postion and directions
		double cameraX = 2 * x / (double)w - 1; //x-coordinate in camera space
		double rayPosX = posX;
		double rayPosY = posY;
		/*
		double rayDir = M_PI - 0.33 * cameraX;	
		double rayDirX = cos(rayDir);
		double rayDirY = sin(rayDir);
		*/
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

		//
		int color;
		switch (world_map[mapX][mapY])
		{
			case 1: color = 0x00FF0000; break;
			case 2: color = 0x0000FF00; break;
			case 3: color = 0x000000FF; break;
			case 4: color = 0x00FFFFFF; break;
			default: color = 0x00FFFF00; break;
		}

		if (side == 1)
			color = color / 2;

		int i;
		i = 0;
		
		while(i < drawEnd - drawStart)
		{
			mlx_pixel_put(mlx, window, x, drawStart + i, color);
			i++;
		}
		/* draw floor 
		while(i < h)
		{
			mlx_pixel_put(mlx, window, x, drawStart + i, 0x00FF00FF);
			i++;
		}
		*/

#define MOVE_SPEED 0.000166666
#define rotSpeed 0.000166666
	
		if (key->e)
		{
			if(world_map[(int)(posX + dirX * MOVE_SPEED)][(int)posY] == 0)
				posX += planeX * MOVE_SPEED;
		   	if(world_map[(int)posX][(int)(posY + dirY * MOVE_SPEED)] == 0)	
				posY += planeY * MOVE_SPEED;
		}
		if (key->q)
		{
			if(world_map[(int)(posX - planeX * MOVE_SPEED)][(int)posY] == 0)
				posX -= planeX * MOVE_SPEED;
		   	if(world_map[(int)posX][(int)(posY - planeY * MOVE_SPEED)] == 0)	
				posY -= planeY * MOVE_SPEED;
		}
		//move forward if no wall in front of you
		if (key->w)
		{
			if(world_map[(int)(posX + dirX * MOVE_SPEED)][(int)posY] == 0)
				posX += dirX * MOVE_SPEED;
		   	if(world_map[(int)posX][(int)(posY + dirY * MOVE_SPEED)] == 0)	
				posY += dirY * MOVE_SPEED;
		}
		if (key->s)
		{
			if(world_map[(int)(posX - dirX * MOVE_SPEED)][(int)posY] == 0)
				posX -= dirX * MOVE_SPEED;
			if(world_map[(int)posX][(int)(posY - dirY * MOVE_SPEED)] == 0)
				posY -= dirY * MOVE_SPEED;
		}
		if (key->d)
		{	
			//both camera direction and camera plane must be rotated
			double oldDirX = dirX;
			dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
			dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
			double oldPlaneX = planeX;
			planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
			planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
		}
		if (key->a)
		{
			//both camera direction and camera plane must be rotated
			double oldDirX = dirX;
			dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
			dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
			double oldPlaneX = planeX;
			planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
			planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
		}
		x++;
	}
	//timeing for input and FPS counter
	oldTime = time;
	//time = getTicks();
	//double frameTime = (time - oldTime) / 1000.0;
	//frameTime is the time this frame has taken, in seconds
	//mlx_string_put(mlx, window, 0, 0, 0x00FFFFFF, itoa(1.0 / frameTime));
	//FPS Counter
	mlx_clear_window(mlx, window);

	//speed modifiers
	//double moveSpeed = frameTime * 5.0; //constant value in squares/second
	//double rotSpeed = frameTime * 3.0; //constant value in radians/second
	
	return (0);
}

#include <stdlib.h>

int		key_press_hook(int keycode, void *nothing)
{
	printf("posY: %f\n", posY);
	printf("posX: %f\n", posX);
	printf("Keycode: %d\n", keycode);
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
	printf("Keycode: %d\n", keycode);
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

void	set_hooks(void *mlx, void *window)
{
	mlx_do_key_autorepeatoff(mlx);
	mlx_hook(window, 2, 0, key_press_hook, 0000);
	mlx_hook(window, 3, 0, key_release_hook, 0000);
	//mlx_hook(window, 4, 0, mouse_press_hook, 0000);
	//mlx_hook(window, 5, 0, mouse_release_hook, 0000);
	//mlx_hook(window, 6, 0, motion_hook, 0000);
	//mlx_hook(window, 12, 0, expose_hook, 0000);
	mlx_hook(window, 17, 0, exit_hook, 0000);
}

int main(int argc, char **argv)
{
	key = (struct s_key*)malloc(sizeof(struct s_key));
	mlx = mlx_init();
	window = mlx_new_window(mlx, w, h, "Wolf3d");
	mlx_loop_hook(mlx, loop_hook, 0);
	set_hooks(mlx, window);
	mlx_loop(mlx);
	(void) argc;
	(void) argv;
}
