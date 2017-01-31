/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoung <myoung@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 22:39:12 by myoung            #+#    #+#             */
/*   Updated: 2017/01/27 02:50:22 by myoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

void	put_player_minimap(t_view *v)
{
	t_2dp	p;
	
	//player location is flipped or something. Try to understand better.
	p.x = v->pos.y * 10;
	p.y = v->pos.x * 10;
	draw_filled_square(v, p, 15, 0xFF0000);
	p.x += v->dir.y * 10;
	p.y += v->dir.x * 10;
	draw_filled_square(v, p, 10, 0xFF00);	
}

void	put_minimap(t_view *v)
{
	t_2dp	p;
	int y;
	int x;

	x = 0,
	y = 0;
	create_image(v->mlx, &v->minimap_image, v->map.width * 10, v->map.height * 10);
	while (y < v->map.height)
	{
		while (x < v->map.width)
		{
			p.x = x * 10;
			p.y = y * 10;
 			draw_filled_square(v, p, 10, TILE_AT(x,y) >= 1 ? 0xFF : 0xFFFFFF);
			x++;
		}
		x = 0;
		y++;
	}
	put_player_minimap(v);
	mlx_put_image_to_window(v->mlx, v->minimap_window,
		   	v->minimap_image.ptr, 0, 0);
	mlx_destroy_image(v->mlx, v->minimap_image.ptr);
}

void	create_minimap(t_view *v)
{
	v->minimap_window = mlx_new_window(v->mlx, v->map.width * 10, v->map.height * 10, "Minimap");
	put_minimap(v);
}

