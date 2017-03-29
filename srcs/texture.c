/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoung <myoung@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 06:21:08 by myoung            #+#    #+#             */
/*   Updated: 2017/03/29 16:01:21 by myoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

static void	make_textures(t_view *v, int x, int y)
{
	int xorcolor;
	int xycolor;

	xorcolor = (x * 256 / v->tex_width) ^ (y * 256 / v->tex_height);
	xycolor = y * 128 / v->tex_height + x * 128 / v->tex_width;
	v->texture[0][v->tex_width * y + x] =
		0x10000 * 0xFF * (x != y && x != v->tex_width - y);
	v->texture[1][v->tex_width * y + x] =
		xycolor + 0x100 * xycolor + 0x10000 * xycolor;
	v->texture[2][v->tex_width * y + x] = 256 * xycolor +
		0x10000 * xycolor;
	v->texture[3][v->tex_width * y + x] = xorcolor + 0x100 *
		xorcolor + 0x10000 * xorcolor;
	v->texture[4][v->tex_width * y + x] = 0x100 * xorcolor;
	v->texture[5][v->tex_width * y + x] = 0x10000 * 0xFF * (x % 8 && y % 8);
	v->texture[6][v->tex_width * y + x] = 0x100 * 0xFF * (x % 16 && y % 16);
	v->texture[7][v->tex_width * y + x] = 0xFF * (x % 32 && y % 32);	
}

void	texture_init(t_view *v)
{
	int i;
	int x;
	int y;

	v->texture = malloc(sizeof(int*) * TEX_COUNT);
	v->tex_width = TEX_WIDTH;
	v->tex_height = TEX_HEIGHT;
	i = -1;
	x = -1;
	y = -1;
	while (++i < TEX_COUNT)
		v->texture[i] = malloc(sizeof(int) * v->tex_width * v->tex_height);	
	while (++x < v->tex_width)
	{
		while (++y < v->tex_height)
			make_textures(v, x, y);
		y = -1;
	}
}
