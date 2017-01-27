/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoung <myoung@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 10:11:53 by myoung            #+#    #+#             */
/*   Updated: 2017/01/24 22:55:46 by myoung           ###   ########.fr       */
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
	free(v->z_buff);
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

void	init_view(int w, int h, char *title)
{
	t_view *view;
	view = (t_view*)malloc(sizeof(t_view));
	view->mlx = mlx_init();
	view->map = parse_map("maps/demo.map");
	view->w = w;
	view->h = h;
	view->pos.x = 22;
	view->pos.y = 21;
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
	keys_init(&view->key);
	//sprite_init();
	texture_init(view);
	//create_minimap(view);
	set_hooks(view);
	view->z_buff = (double*)malloc(WINDOW_WIDTH * sizeof(double));
	mlx_loop_hook(view->mlx, loop_hook, view);	
	mlx_loop(view->mlx);
}

int main(int argc, char **argv)
{
	if (argc != 1 && argv)
		exit(1);
	init_view(WINDOW_WIDTH, WINDOW_HEIGHT, "Wolf3d");	
	return (0);
}
