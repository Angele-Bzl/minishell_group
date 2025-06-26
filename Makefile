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
DIR_BUILTINS	=	builtins
DIR_PARS        =   parsing
DIR_UTILS       =   utils
DIR_OBJ			=	obj
DIR_HEADER		=	header
DIR_LIBFT		=	libft

#####################################################
#					FLAGS							#
#####################################################
CFLAGS		=	-Wall -Wextra -Werror -MMD -MP -I$(DIR_HEADER) -g3 -g
LFLAGS		=	-lreadline -lncurses

#####################################################
#					FILES							#
#####################################################
FILES_EXEC  =   execution.c\
				command.c\
				utils_exec.c\
				single_cmd.c\
				error_exec.c\
				children.c\
				input_output.c\
				clean.c\
				manage_heredoc.c\
				$(addprefix $(DIR_BUILTINS)/, $(FILES_BUILT))

FILES_BUILT	=	utils_builtin.c\
				cd.c\
				echo.c\
				env.c\
				export.c\
				exit.c\
				pwd.c\
				unset.c
FILES_PARS  =   cmd_token_utils.c\
				cmd_token.c\
				expand_var.c\
				extract_token_without_quotes.c\
				ft_countpipe_utils.c\
				linked_list_file.c\
				linked_list_token.c\
				manage_dollar_utils.c\
				manage_dollar.c\
                manage_quotes.c\
				parsing.c\
				pipe_segmentation.c\
				prompt_check.c\
				rafter_token.c\
				rafter_token_utils.c\
				skip_quote.c\
				split_whitespace_quote.c\
				tokenisation.c
FILES_UTILS =   cutstr.c\
				debug_print.c\
				free_minishell.c\
				free_utils.c\
				ft_isspace.c
FILES		=	struct_init.c\
				main.c\
				$(addprefix $(DIR_PARS)/,$(FILES_PARS))\
                $(addprefix $(DIR_UTILS)/, $(FILES_UTILS))\
                $(addprefix $(DIR_EXEC)/, $(FILES_EXEC))

FILE_HEADER	=	minishell.h
SRC			=	$(DIR_SRC)/$(FILES) $(DIR_SRC)/$(FILES_UTILS)
HEADERS		=	$(DIR_HEADER)/$(FILE_HEADER)
OBJ			=	$(FILES:%.c=$(DIR_OBJ)/%.o)
DEP			=	$(OBJ:%.o=%.d)


#####################################################
#					ARCHIVES						#
#####################################################
 LIBFT		=	libft/libft.a\
 				libft/printf/libftprintf.a\
 				libft/printf_err/libftprintf.a\

all :
	$(MAKE) -C $(DIR_LIBFT)/
	$(MAKE) $(NAME)

-include $(DEP)

$(NAME) : $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(DIR_OBJ)/%.o : $(DIR_SRC)/%.c Makefile | $(DIR_OBJ)
	$(CC) $(CFLAGS) -o $@ -c $<

$(DIR_OBJ):
	mkdir -p $(DIR_OBJ)
	mkdir -p $(DIR_OBJ)/$(DIR_EXEC)
	mkdir -p $(DIR_OBJ)/$(DIR_EXEC)/$(DIR_BUILTINS)
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
