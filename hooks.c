/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoung <myoung@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 06:05:58 by myoung            #+#    #+#             */
/*   Updated: 2017/01/24 22:47:00 by myoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

int		key_press_hook(int keycode, t_view *v)
{
	keycode == KEY_ESC ? exit(0) : 0;
	key_toggle(&v->key, keycode, 1);
	if (keycode == KEY_R)
		v->plane.y = .6;
	return (0);
}

int		key_release_hook(int keycode, t_view *v)
{
	key_toggle(&v->key, keycode, 0);
	return (0);
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
	(void)view;
	printf("x: %d\ty: %d", x, y);
	return (0);
}

int		mouse_release_hook(int x, int y, t_view *view)
{
	(void)view;
	printf("x: %d\ty: %d", x, y);
	return (0);
}
