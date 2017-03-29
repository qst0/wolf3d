/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoung <myoung@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 10:11:53 by myoung            #+#    #+#             */
/*   Updated: 2017/03/29 15:41:44 by myoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

int		expose_hook(t_view *v)
{
	(void)v;
	return (0);
}

int		exit_hook(t_view *v)
{
	int i;

	if (v->z_buff)
		free(v->z_buff);
	if (v->texture)
	{
		i = -1;
		while (++i < TEX_COUNT)
			free(v->texture[i]);
		free(v->texture);
	}
	if (v->map.cell)
		free_map(&(v->map));
	exit(0);
}

void	set_hooks(t_view *v)
{
	mlx_do_key_autorepeatoff(v->mlx);
	mlx_hook(v->window, 2, 0, key_press_hook, v);
	mlx_hook(v->window, 3, 0, key_release_hook, v);
	mlx_hook(v->window, 4, 0, mouse_press_hook, v);
	mlx_hook(v->window, 5, 0, mouse_release_hook, v);
	mlx_hook(v->window, 6, 0, motion_hook, v);
	mlx_hook(v->window, 12, 0, expose_hook, v);
	mlx_hook(v->window, 17, 0, exit_hook, v);
}

int main(int argc, char **argv)
{
	if (argc != 1 && argv)
		exit(1);
	init_view(WINDOW_WIDTH, WINDOW_HEIGHT, "Raycasting Demo - Wolf3d");
	return (0);
}
