NAME		=	minishell

CC			=	cc -Wall -Wextra -Werror -g3

SRCS		=	srcs/main.c\
				srcs/built-in/ft_echo.c\
				srcs/built-in/ft_env.c\
				srcs/built-in/ft_export.c\
				srcs/built-in/ft_export_utils.c\
				srcs/built-in/ft_unset.c\
				srcs/built-in/ft_exit.c\
				srcs/clean_exit/clean.c\
				srcs/clean_exit/singletons.c\
				srcs/commands/cmds.c\
				srcs/commands/cmd_args.c\
				srcs/commands/lst_cmds.c\
				srcs/commands/lst_cmds_2.c\
				srcs/commands/redir_cmds.c\
				srcs/debug/debug.c\
				srcs/env/get_env.c\
				srcs/env/lst_env.c\
				srcs/errors/error_handle.c\
				srcs/expand/expand.c\
				srcs/built-in/ft_pwd.c\
				srcs/parsing-lexer/tokenization.c\
				srcs/parsing-lexer/lst_token.c\
				srcs/parsing-lexer/check_syntax.c\
				srcs/parsing-lexer/parsing_utils.c\
				srcs/parsing-lexer/parsing_utils_2.c\
				srcs/signals/signals.c\
				srcs/exec/get_path.c\
				srcs/exec/handle_access.c\
				srcs/exec/handle_errors.c\
				srcs/exec/handle_path.c\
				srcs/exec/handle_processes.c\
				srcs/exec/handle_quotes_and_slash.c\
				srcs/exec/handle_spaces_and_slashes.c\
				srcs/exec/here_doc.c\
				srcs/exec/exec.c\
				srcs/exec/print_errors.c\
				srcs/exec/size_functions.c\
				srcs/exec/split.c\
				srcs/exec/string_functions.c\
				srcs/exec/wait_and_close.c\
				srcs/exec/handle_built_in.c\
				includes/get_next_line/get_next_line.c\
				includes/get_next_line/get_next_line_utils.c\

OBJS		=	${SRCS:.c=.o}

LIBFT		=	includes/libft

FT_LIBFT	=	includes/libft/libft.a

PRINTF		=	includes/printf

FT_PRINTF	=	includes/printf/libftprintf.a


all:	${NAME} $(LIBFT) $(PRINTF)


$(NAME):	$(OBJS)
			make -C $(LIBFT) && make -C $(PRINTF) 
			$(CC) $(OBJS) -o $(NAME) $(FT_LIBFT) $(FT_PRINTF) -lreadline

clean:
			rm -f $(OBJS)
			make clean -C $(LIBFT) && make clean -C $(PRINTF) 

fclean:		clean
			rm -f ${NAME}
			make fclean -C $(LIBFT) && make fclean -C $(PRINTF)

re:			fclean all

.PHONY:		all clean fclean re
