/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoung <myoung@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 06:07:20 by myoung            #+#    #+#             */
/*   Updated: 2017/01/18 00:14:24 by myoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

static void key_init_split(t_keys *key)
{
	key->a = 0;
	key->s = 0;
	key->d = 0;
	key->f = 0;
	key->h = 0;
	key->g = 0;
	key->z = 0;
	key->x = 0;
	key->c = 0;
	key->v = 0;
	key->b = 0;
	key->q = 0;
	key->w = 0;
	key->e = 0;
	key->r = 0;
	key->y = 0;
	key->t = 0;
	key->one = 0;
	key->two = 0;
	key->three = 0;
	key->four = 0;
	key->six = 0;
	key->five = 0;
	key->nine = 0;
	key->seven = 0;
}

void	keys_init(t_keys *key)
{
	key_init_split(key);
	key->eight = 0;
	key->zero = 0;
	key->brace_r = 0;
	key->o = 0;
	key->u = 0;
	key->brace_l = 0;
	key->i = 0;
	key->p = 0;
	key->l = 0;
	key->j = 0;
	key->k = 0;
	key->semi = 0;
	key->n = 0;
	key->m = 0;
	key->tab = 0;
	key->plus = 0;
	key->minus = 0;
	key->left = 0;
	key->right = 0;
	key->down = 0;
	key->up = 0;
}

static void	key_toggle_split_one(t_keys *key, int keycode, int toggle)
{
	keycode == KEY_A ? key->a = toggle : 0;
	keycode == KEY_S ? key->s = toggle : 0;
	keycode == KEY_D ? key->d = toggle : 0;
	keycode == KEY_F ? key->f = toggle : 0;
	keycode == KEY_H ? key->h = toggle : 0;
	keycode == KEY_G ? key->g = toggle : 0;
	keycode == KEY_Z ? key->z = toggle : 0;
	keycode == KEY_X ? key->x = toggle : 0;
	keycode == KEY_C ? key->c = toggle : 0;
	keycode == KEY_V ? key->v = toggle : 0;
	keycode == KEY_B ? key->b = toggle : 0;
	keycode == KEY_Q ? key->q = toggle : 0;
	keycode == KEY_W ? key->w = toggle : 0;
	keycode == KEY_E ? key->e = toggle : 0;
	keycode == KEY_R ? key->r = toggle : 0;
	keycode == KEY_Y ? key->y = toggle : 0;
	keycode == KEY_T ? key->t = toggle : 0;
	keycode == KEY_ONE ? key->one = toggle : 0;
	keycode == KEY_TWO ? key->two = toggle : 0;
	keycode == KEY_THREE ? key->three = toggle : 0;
	keycode == KEY_FOUR ? key->four = toggle : 0;
	keycode == KEY_SIX ? key->six = toggle : 0;
	keycode == KEY_FIVE ? key->five = toggle : 0;
	keycode == KEY_NINE ? key->nine = toggle : 0;
	keycode == KEY_SEVEN ? key->seven = toggle : 0;
}

static void key_toggle_split_two(t_keys *key, int keycode, int toggle)
{
	keycode == KEY_EIGHT ? key->eight = toggle : 0;
	keycode == KEY_ZERO ? key->zero = toggle : 0;
	keycode == KEY_BRACE_R ? key->brace_r = toggle : 0;
	keycode == KEY_O ? key->o = toggle : 0;
	keycode == KEY_U ? key->u = toggle : 0;
	keycode == KEY_BRACE_L ? key->brace_l = toggle : 0;
	keycode == KEY_I ? key->i = toggle : 0;
	keycode == KEY_P ? key->p = toggle : 0;
	keycode == KEY_L ? key->l = toggle : 0;
	keycode == KEY_J ? key->j = toggle : 0;
	keycode == KEY_K ? key->k = toggle : 0;
	keycode == KEY_SEMI ? key->semi = toggle : 0;
	keycode == KEY_N ? key->n = toggle : 0;
	keycode == KEY_M ? key->m = toggle : 0;
	keycode == KEY_TAB ? key->tab = toggle : 0;
	keycode == KEY_PLUS ? key->plus = toggle : 0;
	keycode == KEY_MINUS ? key->minus = toggle : 0;
	keycode == KEY_LEFT ? key->left = toggle : 0;
	keycode == KEY_RIGHT ? key->right = toggle : 0;
	keycode == KEY_DOWN ? key->down = toggle : 0;
	keycode == KEY_UP ? key->up = toggle : 0;
}

void		key_toggle(t_keys *key, int keycode, int toggle)
{
	printf("%d\n", keycode);
	if (keycode < 27)
		key_toggle_split_one(key, keycode, toggle);
	else
		key_toggle_split_two(key, keycode, toggle);
}
