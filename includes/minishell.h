/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:08:04 by ahayon            #+#    #+#             */
/*   Updated: 2024/03/05 13:31:19 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "printf/srcs/ft_printf.h" 

typedef enum e_token_tp
{
	APPEND = 1,
	HEREDOC,
	PIPE,
	RED_IN,
	RED_OUT,
	WORD,
}	t_token_tp;

typedef struct s_cmd
{
	char			*value;
	char			**args;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_token
{
	char			*value;
	t_token_tp		type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_data
{
	char	*input;
	t_token	*token_list;
}	t_data;

// TOKENIZATION

int 	ft_add_sep(t_token **token_lst, int type, char *str, int i);
int		ft_add_word(t_token **token_lst, char *str, int i);
int		ft_add_token(t_data *data, char *str, int type, int i);
int		ft_define_token_type(char *str, int i);
t_token	*ft_lstnew_token(char *value, t_token_tp type);
void	ft_lstadd_back_token(t_token **token_lst, t_token *new_token);
t_token	*ft_lstlast_token(t_token *token);

// UTILS

char	*ft_del_edge_spaces(char *str);
bool 	ft_is_only_space(char *str);
bool	ft_is_whitespace(char *str, int i);

// DEBUG

void	print_tokens(t_token *token_lst);

#endif
