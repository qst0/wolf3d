/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoung <myoung@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 06:05:58 by myoung            #+#    #+#             */
/*   Updated: 2017/01/19 02:26:24 by myoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

int		key_press_hook(int keycode, t_view *v)
{
	keycode == KEY_ESC ? exit(0) : 0;
	key_toggle(&v->key, keycode, 1);
	return (0);
}

int		key_release_hook(int keycode, t_view *v)
{
	key_toggle(&v->key, keycode, 0);
	return (0);
}

int		exit_hook(t_view *v)
{
	(void) v;
	exit(0);
}

int		motion_hook(int x, int y, t_view *v)
{
	if (v->mouse_x < x)
		player_turn(v, -1, 0.5);
	else if (v->mouse_x > x)
		player_turn(v, 1, 0.5);
	v->mouse_x = x;
	v->mouse_y = y;
	return (0);
}

int		mouse_press_hook(int x, int y, t_view *view)
{
	//view->mouse_x = x;
	//view->mouse_y = y;
	(void) view;
	printf("x: %d\ty: %d", x, y);
	return (0);
}

int		mouse_release_hook(int x, int y, t_view *view)
{
	//view->mouse_x = x;
	//view->mouse_y = y;
	(void) view;
	printf("x: %d\ty: %d", x, y);
	return (0);
}

int		expose_hook(t_view *v)
{
	(void) v;
	return (0);//loop_hook(v));
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
