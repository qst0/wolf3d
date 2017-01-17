/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoung <myoung@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 06:15:06 by myoung            #+#    #+#             */
/*   Updated: 2017/01/17 06:15:14 by myoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

int		nlen(int n)
{
	int len = 0;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*itoa(int i)
{
	char *result;
	int len;

	len = nlen(i);
	result = (char*)malloc(len + 1);
	result[len--] = '\0';
	while (i)
	{
		result[len--] = i % 10 + '0';
		i /= 10;
	}
	return (result);
}

int		fake_floor(double x)
{
	return (int)(x + 100000) - 100000;
}


