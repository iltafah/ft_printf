# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iltafah <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/18 16:56:28 by iltafah           #+#    #+#              #
#    Updated: 2019/12/18 15:45:11 by iltafah          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

FLAGS = -Wall -Wextra -Werror

SRC = char_manipulation.c  formats_functions.c  the_rest_of_formats_functions.c  calc_functions.c  filling_functions.c  ft_printf.c  print_functions.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $@ $^
	ranlib $@

%.o : %.c
	gcc $(FLAGS) -c $^

clean :
		rm -f *.o

fclean : clean
		rm -f $(NAME)

re : fclean all
