/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoung <myoung@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 06:21:08 by myoung            #+#    #+#             */
/*   Updated: 2017/03/29 12:02:21 by myoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

void	texture_init(t_view *v)
{
	v->texture = malloc(sizeof(int*) * TEX_COUNT);
	v->tex_width = TEX_WIDTH;
	v->tex_height = TEX_HEIGHT;

	int i;

	i = -1;
	while (++i < TEX_COUNT)
		v->texture[i] = malloc(sizeof(int) * v->tex_width * v->tex_height);

	for(int x = 0; x < v->tex_width; x++)
		for(int y = 0; y < v->tex_height; y++)
		{
			int xorcolor = (x * 256 / v->tex_width) ^ (y * 256 / v->tex_height);
			//int xcolor = x * 256 / v->tex_width;
			//int ycolor = y * 256 / v->tex_height;
			int xycolor = y * 128 / v->tex_height + x * 128 / v->tex_width;

			//bright red with black cross
			v->texture[0][v->tex_width * y + x] =
				0x10000 * 0xFF * (x != y && x != v->tex_width - y);
			//sloped greyscale
			v->texture[1][v->tex_width * y + x] =
				xycolor +
			   	0x100 * xycolor +
			   	0x10000 * xycolor;
			//sloped yellow gradient
			v->texture[2][v->tex_width * y + x] =
				256 * xycolor +
			   	0x10000 * xycolor;
			//xor greyscale
			v->texture[3][v->tex_width * y + x] =
				xorcolor +
			   	0x100 * xorcolor +
			   	0x10000 * xorcolor;
			//xor green
			v->texture[4][v->tex_width * y + x] =
				0x100 * xorcolor;
			//red bricks
			v->texture[5][v->tex_width * y + x] =
			   	0x10000 * 0xFF * (x % 8 && y % 8);
			//green bricks
			v->texture[6][v->tex_width * y + x] =
				0x100 * 0xFF * (x % 16 && y % 16);
			//blue bricks
			v->texture[7][v->tex_width * y + x] =
			   	0xFF * (x % 32 && y % 32);
			//red gradient left dark right bright
			//v->texture[6][v->tex_width * y + x] = 0x10000 * xcolor;

			//red gradient top dark bottom bright
			//v->texture[6][v->tex_width * y + x] = 0x10000 * ycolor;

			//flat grey texture
			//v->texture[7][v->tex_width * y + x] = 0x808080;
		}
}
