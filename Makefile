#####################################################
#					PROGRAM							#
#####################################################
NAME		=	minishell

#####################################################
#					COMPILING						#
#####################################################
CC			=	cc

#####################################################
#					DIRECTORY						#
#####################################################
DIR_SRC			=	src
DIR_EXEC        =   execution
DIR_PARS        =   parsing
DIR_UTILS       =   utils
DIR_OBJ			=	obj
DIR_HEADER		=	header
DIR_LIBFT		=	libft

#####################################################
#					FLAGS							#
#####################################################
CFLAGS		=	-Wall -Wextra -Werror -g3 -g
LFLAGS		=	-lreadline -lncurses

#####################################################
#					FILES							#
#####################################################
FILES_EXEC  =   execution.c\
				command.c\
				utils_exec.c
FILES_PARS  =   parsing.c\
                manage_quotes.c
FILES_UTILS =   cutstr.c\
				skip_under_quote.c\
				split_pipe_smart.c
FILES		=	struct_init.c\
				main.c\
				$(addprefix $(DIR_PARS)/,$(FILES_PARS))\
                $(addprefix $(DIR_UTILS)/, $(FILES_UTILS))
                # $(DIR_EXEC)/$(FILES_EXEC)

FILE_HEADER	=	minishell.h
SRC			=	$(DIR_SRC)/$(FILES) $(DIR_SRC)/$(FILES_UTILS)
HEADERS		=	$(DIR_HEADER)/$(FILE_HEADER)
OBJ			=	$(FILES:%.c=$(DIR_OBJ)/%.o)


#####################################################
#					ARCHIVES						#
#####################################################
 LIBFT		=	libft/libft.a\
 				libft/printf/libftprintf.a\
 				libft/printf_err/libftprintf.a\

all :
	$(MAKE) -C $(DIR_LIBFT)/
	$(MAKE) $(NAME)

$(NAME) : $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(DIR_OBJ)/%.o : $(DIR_SRC)/%.c $(HEADERS) Makefile | $(DIR_OBJ)
	$(CC) $(CFLAGS) -o $@ -c $<

$(DIR_OBJ):
	mkdir -p $(DIR_OBJ)
	mkdir -p $(DIR_OBJ)/$(DIR_EXEC)
	mkdir -p $(DIR_OBJ)/$(DIR_PARS)
	mkdir -p $(DIR_OBJ)/$(DIR_UTILS)

re: fclean
	$(MAKE) all

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(DIR_LIBFT)/

clean :
	rm -rf $(DIR_OBJ)
	$(MAKE) clean -C $(DIR_LIBFT)/
