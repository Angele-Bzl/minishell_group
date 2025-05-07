# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/04 13:44:29 by abarzila          #+#    #+#              #
#    Updated: 2025/05/06 18:07:41 by abarzila         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a
CC	=	cc
CFLAG	=	-Wall -Wextra -Werror -g
INC		=	libft.h\
			get_next_line.h

OBJ	=	$(SRC:.c=.o)
SRC	=	ft_isalpha.c\
		ft_isdigit.c\
		ft_isalnum.c\
		ft_isascii.c\
		ft_isprint.c\
		ft_strlen.c\
		ft_memset.c\
		ft_bzero.c\
		ft_memcpy.c\
		ft_memmove.c\
		ft_strlcpy.c\
		ft_strlcat.c\
		ft_toupper.c\
		ft_tolower.c\
		ft_strchr.c\
		ft_strrchr.c\
		ft_memchr.c\
		ft_atoi.c\
		ft_memcmp.c\
		ft_strnstr.c\
		ft_strdup.c\
		ft_strncmp.c\
		ft_substr.c\
		ft_strjoin.c\
		ft_split.c\
		ft_strtrim.c\
		ft_putchar_fd.c\
		ft_putstr_fd.c\
		ft_putendl_fd.c\
		ft_putnbr_fd.c\
		ft_strmapi.c\
		ft_striteri.c\
		ft_itoa.c\
		ft_calloc.c\
		get_next_line.c\
		get_next_line_utils.c\
		ft_lstnew_bonus.c\
		ft_lstadd_front_bonus.c\
		ft_lstsize_bonus.c\
		ft_lstlast_bonus.c\
		ft_lstadd_back_bonus.c\
		ft_lstdelone_bonus.c\
		ft_lstclear_bonus.c\
		ft_lstiter_bonus.c\
		ft_lstmap_bonus.c

all: $(NAME)
	$(MAKE) -C printf
	$(MAKE) -C printf_err

$(NAME): $(OBJ) $(INC) Makefile
	ar rcs $(NAME) $(OBJ)

%.o: %.c $(INC)
	$(CC) $(CFLAG) -c $< -o $@

clean:
	rm -f $(OBJ)
	$(MAKE) clean -C printf/
	$(MAKE) clean -C printf_err/

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C printf/
	$(MAKE) fclean -C printf_err/

re: fclean all

.PHONY: all clean fclean re
