/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoung <myoung@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 05:43:05 by myoung            #+#    #+#             */
/*   Updated: 2017/01/24 19:47:07 by myoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

void	draw_point_to_img(t_img *img, int x, int y, int color)
{
	int i;

	i = (x * (img->bits_per_pixel / 8)) + (y * img->size_line);
	img->pixels[i] = color;
	img->pixels[++i] = color >> 8;
	img->pixels[++i] = color >> 16;
}

t_rect	set_rect(int x, int y, int w, int h)
{
	t_rect r;

	r.x = x;
	r.y = y;
	r.w = w;
	r.h = h;
	return (r);
}

void	draw_filled_rect(t_view *v, t_rect rect, int color)
{
	int y;
	int x;

	y = -1;
	x = -16;
	while (++y < rect.h)
	{
		while (++x < rect.w)
			draw_point_to_img(&v->image, x + rect.x, y + rect.y, color);
		x = -1;
	}
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
