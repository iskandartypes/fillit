/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteinbe <jsteinbe@student.42.us.or>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 04:21:09 by jsteinbe          #+#    #+#             */
/*   Updated: 2019/01/19 19:46:07 by ikourkji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int	check_spot(const t_etromino *t, t_int16 *square)
{
	return (!(*(t_int64 *)(square + t->y) & t->bits << t->x));
}

static void	toggle_piece(const t_etromino *t, t_int16 *square)
{
	*(t_int64 *)(square + t->y) ^= t->bits << t->x;
}

static int	backtrack(t_etromino **t, t_int16 *square, int size, int i)
{
	if (i == 0 && g_count == 1)
		return (1);
	t[i]->x = 0;
	t[i]->y = 0;
	while (t[i]->y <= size - (t[i]->height))
	{
		while (t[i]->x <= size - (t[i]->width))
		{
			if (check_spot(t[i], square))
			{
				toggle_piece(t[i], square);
				if (i == g_count - 1 || backtrack(t, square, size, i + 1))
					return (1);
				toggle_piece(t[i], square);
			}
			t[i]->x++;
		}
		t[i]->x = 0;
		t[i]->y++;
	}
	return (0);
}

void		solve(t_etromino **t)
{
	int		square_size;
	t_int16 *square;

	square = make_square();
	square_size = 2;
	while ((square_size * square_size) < (g_count * 4))
		square_size++;
	while (!backtrack(t, square, square_size, 0) && square_size <= 16)
	{
		ft_bzero(square, sizeof(t_int16) * 16);
		square_size++;
	}
	ft_memdel((void **)&square);
	if (square_size == 17)
		return ;
	print(square_size, t);
}
