# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ikourkji <ikourkji@student.42.us.or>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/30 20:28:37 by ikourkji          #+#    #+#              #
#    Updated: 2019/01/19 19:50:17 by ikourkji         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit

SRC = main.c file_in.c list_utils.c square.c solve.c

OBJ = main.o file_in.o list_utils.o square.o solve.o

LFT = libft/libft.a

DB = -g -fsanitize=address

CFLAGS = -Wall -Wextra -Werror

.PHONY: all $(NAME) $(LFT) clean fclean re

all: $(NAME)

$(NAME): $(LFT)
	gcc $(CFLAGS) -c $(SRC)
	gcc $(CFLAGS) -o $(NAME) $(OBJ) $(LFT)

test:
	gcc $(DB) $(SRC) $(LFT) -o test_$(NAME)

$(LFT):
	(cd libft; make all)

clean:
	rm -rf $(OBJ)
	(cd libft; make clean)

fclean: clean
	rm -f $(NAME)
	(cd libft; make fclean)

re: fclean all
