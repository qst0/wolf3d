/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoung <myoung@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 02:37:28 by myoung            #+#    #+#             */
/*   Updated: 2017/03/29 12:00:49 by myoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

/*
** imports for read
*/
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

/*
** imports for open
*/
#include <fcntl.h>
#include <stdio.h>

/*
** imports for malloc
*/
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

t_map		parser(t_map *map, char **lines, char **line)
{	
	int col_size;
	int row;
	int col;
	
	map->cell = (int**)malloc(sizeof(int*) * map->height);
	col_size = map->width;
	row = 0;
	while (lines[row])
	{
		line = ft_strsplit(lines[row], ' ');
		map->cell[row] = (int*)malloc(sizeof(int) * col_size);
		col = 0;
		while (line[col])
		{
			map->cell[row][col] = ft_atoi(line[col]);
			col++;
		}
		row++;
	}
	return (*map);
}

t_map		parse_map(const char *filename)
{
	char	buff[4097];
	char	**lines;
	char	**line;
	t_map	map;
	int		fd;

	map.height = 0;
	while (map.height < 4097)
		buff[map.height++] = 0;
	fd = open(filename, O_RDONLY);
	read(fd, buff, 4097);
	close(fd);
	map.height = 0;
	lines = ft_strsplit(buff, '\n');
	while (lines[map.height])
	{
		line = ft_strsplit(lines[map.height], ' ');
		map.width = 0;
		while (line[map.width])
			map.width++;
		map.height++;
	}
	return (parser(&map, lines, line));
}

