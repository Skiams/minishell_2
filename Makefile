NAME		=	minishell

CC			=	cc -Wall -Wextra -Werror -g3

SRCS		=	srcs/main.c\
				srcs/env/get_env.c\
				srcs/env/lst_env.c\
				srcs/parsing-lexer/tokenization.c\
				srcs/parsing-lexer/lst_token.c\
				srcs/parsing-lexer/check_syntax.c\
				srcs/parsing-lexer/parsing_utils.c\
				srcs/parsing-lexer/parsing_utils_2.c\
				srcs/parsing-command/parsing_cmd.c\
				srcs/parsing-command/lst_cmd.c\
				srcs/built-in/ft_echo.c\
				srcs/errors/error_handle.c\
				srcs/clean_exit/clean.c\
				srcs/clean_exit/singletons.c\
				srcs/debug/debug.c

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
