NAME		=	minishell

CC			=	cc -Wall -Wextra -Werror -g3

SRCS		=	srcs/minishell.c\
				srcs/clean.c\
				srcs/error_handle.c\
				srcs/lst_token.c\
				srcs/parsing_utils.c\
				srcs/debug/debug.c\
				srcs/tokenization.c\
				srcs/parsing_cmd.c\
				srcs/lst_cmd.c

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
