/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoung <myoung@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 02:37:28 by myoung            #+#    #+#             */
/*   Updated: 2017/01/24 20:46:24 by myoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

//for read
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

//for open
#include <fcntl.h>
#include <stdio.h>

//for malloc
#include <stdlib.h>

int			ft_atoi(const char *str)
{
	int					i;
	int					sign;
	unsigned long long	result;

	i = 0;
	while (str[0] == '\t' || str[0] == '\n' || str[0] == '\v' ||
			str[0] == '\f' || str[0] == ' ' || str[0] == '\r')
		str++;
	result = 0;
	sign = (str[0] == '-' ? -1 : 1);
	str = (str[0] == '-' || str[0] == '+') ? str + 1 : str;
	while (str[0] == '0')
		str++;
	while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
		result = result * 10 + (str[i++] - '0');
	if (i > 19 || result >= 9223372036854775808ULL)
		return (sign == 1 ? -1 : 0);
	return (result * sign);
}

t_map		parse_map(const char *filename)
{
	int fd;
	char buff[4097];

	char **lines;
	char **line;
	t_map	map;
	int row;
	int col;

	row = 0;
	fd = open(filename, O_RDONLY);
	read(fd, buff, 4097);
	lines = ft_strsplit(buff, '\n');
	while (lines[row])
	{
		line = ft_strsplit(lines[row], ' ');
		col = 0;
		while (line[col])
			col++;
		row++;
	}
	map.width = col;
	map.height = row;
	map.cell = (int**)malloc(sizeof(int*) * row);
	int col_size;
	col_size = col;
	row = 0;
	while (lines[row])
	{
		line = ft_strsplit(lines[row], ' ');
		map.cell[row] = (int*)malloc(sizeof(int) * col_size);
		col = 0;
		while (line[col])
		{
			map.cell[row][col] = ft_atoi(line[col]);
			col++;
		}
		row++;
	}
	
	return (map);
}
