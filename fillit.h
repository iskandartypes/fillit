/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikourkji <ikourkji@student.42.us.or>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 17:38:20 by ikourkji          #+#    #+#             */
/*   Updated: 2019/01/19 02:29:30 by ikourkji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "libft/libft.h"

# define SETBIT(A, k)	( (A) |= (1ULL << (k)) )
# define CLEARBIT(A, k)	( (A) &= ~( 1ULL << (k)) )
# define TESTBIT(A, k)	( (A) & (1ULL << (k)) )

typedef struct s_etromino	t_etromino;
typedef uint16_t			t_int16;
typedef uint64_t			t_int64;

extern char					g_count;

struct						s_etromino
{
	t_int64			bits;
	unsigned char	x;
	unsigned char	y;
	unsigned char	width;
	unsigned char	height;
};

int							read_in(int fd, t_etromino ***t);
t_etromino					*enlist(t_int16 bits);
void						list_del(t_etromino **list, int count);
t_int16						*make_square(void);
void						print(int size, t_etromino **t);
void						solve(t_etromino **t);

#endif
