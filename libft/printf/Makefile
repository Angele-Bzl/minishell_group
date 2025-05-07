# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/26 15:50:41 by abarzila          #+#    #+#              #
#    Updated: 2025/03/03 11:12:54 by abarzila         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libftprintf.a
CC		=	cc
CFLAG	=	-Wall -Wextra -Werror
INC		=	ft_printf.h
OBJ		=	$(SRC:.c=.o)
SRC		=	ft_printf.c\
			ft_print_big_x.c\
			ft_print_c.c\
			ft_print_d.c\
			ft_print_percent.c\
			ft_print_s.c\
			ft_print_small_x.c\
			ft_print_u.c\
			ft_print_p.c

all: $(NAME)


$(NAME): $(OBJ) $(INC) Makefile
# the libft is outside of this direcotry
	cp ../libft.a $(NAME)
	ar rcs $(NAME) $(OBJ)

%.o: %.c $(INC)
	$(CC) $(CFLAG) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
