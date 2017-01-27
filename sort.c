/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoung <myoung@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 05:46:16 by myoung            #+#    #+#             */
/*   Updated: 2017/01/27 02:04:58 by myoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

void	ft_swap_int(int *a, int *b)
{
	int temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	ft_swap_double(double *a, double *b)
{
	int temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	comb_sort(int *order, double *dist, int amount)
{
	int gap;
	int	swapped;
	int i;
	int j;

	gap = amount;
	swapped = 0;
	while (gap > 1 || swapped)
	{
		gap = (gap * 10) / 13;
		gap = (gap == 9 || gap == 10) ? 11 : gap;
		gap = gap < 1 ? 1 : gap;
		swapped = 0;
		i = -1;
		while (++i < amount - gap)
		{
			j = i + gap;
			if (dist[i] < dist[j])
			{
				ft_swap_double(&dist[i], &dist[j]);
				ft_swap_int(&order[i], &order[j]);
				swapped = 1;
			}
		}
	}
}
