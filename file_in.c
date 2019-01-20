/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_in.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikourkji <ikourkji@student.42.us.or>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 21:41:21 by ikourkji          #+#    #+#             */
/*   Updated: 2019/01/19 17:47:42 by ikourkji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int	read_store_error(int fd, t_int16 *bits)
{
	char	buf[21];
	int		len;
	int		tcount;
	int		i;

	tcount = 0;
	i = 0;
	while ((len = read(fd, buf, 21)) > 0)
	{
		IFRET((tcount == 26), -1);
		IFRET((len != 21 && len != 20), -1);
		i = 0;
		while (i < len)
		{
			if ((i == 20 || (i + 1) % 5 == 0) && buf[i++] == '\n')
				continue ;
			if (buf[i] == '#')
				SETBIT(bits[tcount], i - ((i + 1) / 5));
			ELIFRET((buf[i] != '.'), -1);
			i++;
		}
		tcount++;
	}
	IFRET((i != 20), -1);
	return (tcount);
}

static int	validate(t_int16 *bits, int i)
{
	int hash;
	int touch;
	int j;

	hash = 0;
	touch = 0;
	j = 0;
	while (j < 16)
	{
		if (TESTBIT(bits[i], j))
		{
			hash++;
			if (j > 3 && TESTBIT(bits[i], j - 4))
				touch++;
			if (j < 12 && TESTBIT(bits[i], j + 4))
				touch++;
			if (j % 4 > 0 && TESTBIT(bits[i], j - 1))
				touch++;
			if (j % 4 < 3 && TESTBIT(bits[i], j + 1))
				touch++;
		}
		j++;
	}
	IFRET((hash != 4 || (touch != 6 && touch != 8)), -1);
	return (0);
}

static void	normalize(t_int16 *bits)
{
	while (!(0x1111 & *bits))
		*bits >>= 1;
	while (!(0xF & *bits))
		*bits >>= 4;
}

static int	check_make(t_int16 *bits, t_etromino **t_etris)
{
	int i;

	i = 0;
	while (i < g_count)
	{
		if (validate(bits, i) == -1)
		{
			list_del(t_etris, i - 1);
			ft_memdel((void **)&bits);
			return (-1);
		}
		normalize(&bits[i]);
		t_etris[i] = enlist(bits[i]);
		i++;
	}
	return (0);
}

int			read_in(int fd, t_etromino ***t_etris)
{
	t_int16 *bits;

	if (!(bits = (t_int16 *)ft_memalloc(sizeof(*bits) * 26)))
		return (-1);
	g_count = read_store_error(fd, bits);
	if (g_count > 0)
	{
		*t_etris = (t_etromino **)ft_memalloc(sizeof(*t_etris) * g_count);
		if (check_make(bits, *t_etris) == -1)
			return (-1);
	}
	ft_memdel((void **)&bits);
	return (g_count);
}
