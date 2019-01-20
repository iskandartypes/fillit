/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikourkji <ikourkji@student.42.us.or>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 01:40:16 by ikourkji          #+#    #+#             */
/*   Updated: 2019/01/19 03:17:47 by ikourkji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

t_int16		*make_square(void)
{
	t_int16	*square;

	if (!(square = (t_int16 *)ft_memalloc(sizeof(*square) * 20)))
		return (NULL);
	return (square);
}

static void	del_map(char **map, int size)
{
	int i;

	i = 0;
	while (size)
		ft_strdel(&map[size-- - 1]);
	ft_memdel((void **)&map);
}

static char	**blank_map(int size)
{
	int		row;
	int		i;
	char	**map;

	if (!(map = (char **)ft_memalloc(sizeof(*map) * size)))
		return (NULL);
	row = 0;
	while (row < size)
	{
		if (!(map[row] = (char *)ft_memalloc(sizeof(**map) * (size + 1))))
		{
			del_map(map, size);
			return (NULL);
		}
		i = 0;
		while (i < size)
			map[row][i++] = '.';
		map[row][i] = '\0';
		row++;
	}
	return (map);
}

void		print(int size, t_etromino **t)
{
	char	**map;
	int		i;
	int		j;

	if (!(map = blank_map(size)))
		return ;
	i = 0;
	while (i < g_count)
	{
		j = 0;
		while (j < 64)
		{
			if (t[i]->bits >> j & 1)
				map[t[i]->y + (j / 16)][j % 16 + t[i]->x] = 'A' + i;
			j++;
		}
		i++;
	}
	i = 0;
	while (i < size)
	{
		ft_putstr(map[i++]);
		ft_putchar('\n');
	}
	del_map(map, size);
}
