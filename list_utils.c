/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikourkji <ikourkji@student.42.us.or>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 03:24:29 by ikourkji          #+#    #+#             */
/*   Updated: 2019/01/18 14:02:06 by ikourkji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static t_int64	embiggen(t_int16 bits)
{
	t_int64 ret;
	int		i;

	ret = 0;
	i = 3;
	while (i > 0)
	{
		ret |= (bits >> (i * 4)) & 0xF;
		ret <<= 16;
		i--;
	}
	ret |= bits & 0xF;
	return (ret);
}

t_etromino		*enlist(t_int16 bits)
{
	t_etromino	*piece;
	int			i;

	piece = (t_etromino *)malloc(sizeof(*piece));
	piece->bits = embiggen(bits);
	piece->x = 0;
	piece->y = 0;
	i = 0;
	piece->width = 0;
	while ((0x1111 << i++) & bits)
		piece->width++;
	i = 0;
	piece->height = 0;
	while ((0xF << i) & bits)
	{
		piece->height++;
		i += 4;
	}
	return (piece);
}

void			list_del(t_etromino **list, int count)
{
	int i;

	i = 0;
	while (i < count)
	{
		free(list[i]);
		list[i] = NULL;
		i++;
	}
	ft_memdel((void **)&list);
}
