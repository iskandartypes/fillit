/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikourkji <ikourkji@student.42.us.or>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 17:34:47 by ikourkji          #+#    #+#             */
/*   Updated: 2019/01/19 20:39:58 by ikourkji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

char	g_count = 0;

int		main(int ac, char **av)
{
	int			fd;
	t_etromino	**t_etris;

	if (ac != 2)
	{
		ft_putstr("usage: fillit fillit_file\n");
		return (1);
	}
	if ((fd = open(av[1], O_RDONLY)) < 0)
	{
		ft_putstr("error\n");
		return (1);
	}
	g_count = read_in(fd, &t_etris);
	if (g_count < 1)
	{
		ft_putstr("error\n");
		close(fd);
		return (1);
	}
	solve(t_etris);
	list_del(t_etris, g_count);
	close(fd);
	return (0);
}
