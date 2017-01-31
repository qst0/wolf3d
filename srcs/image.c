/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoung <myoung@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 05:44:26 by myoung            #+#    #+#             */
/*   Updated: 2017/01/27 02:55:04 by myoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

void	use_image(t_view *v)
{
	mlx_put_image_to_window(v->mlx, v->window, v->image.ptr,
			v->image.x_offset, v->image.y_offset);
	mlx_destroy_image(v->mlx, v->image.ptr);
}

void	create_image(void *mlx, t_img *image, int w, int h)
{
	image->width = w;
	image->height = h;
	image->ptr = mlx_new_image(mlx, w, h);
	image->pixels = mlx_get_data_addr(image->ptr,
			&image->bits_per_pixel,
			&image->size_line,
			&image->endian);
}
