/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:08:04 by ahayon            #+#    #+#             */
/*   Updated: 2024/03/15 16:51:58 by ahayon           ###   ########.fr       */
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
	RED_IN,
	RED_OUT,
	PIPE,
	WORD,
	WHITESPACE,
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
	t_cmd	*cmd_list;
}	t_data;

// TOKENIZATION

int 	ft_add_sep(t_token **token_lst, int type, char *str, int i);
int		ft_add_word(t_token **token_lst, char *str, int i);
int		ft_add_token(t_data *data, char *str, int type, int i);
int		ft_define_token_type(char *str, int i);
t_token	*ft_lstnew_token(char *value, t_token_tp type);
void	ft_lstadd_back_token(t_token **token_lst, t_token *new_token);
t_token	*ft_lstlast_token(t_token *token);
bool	ft_tokenization(t_data *data);
int		ft_check_syntax(t_data *data);
bool	ft_check_quotes(char *str, int i);
int		ft_check_end_quotes(char *str, int i, char c);

// PARSING COMMANDS

bool	ft_set_cmd(t_data *data, t_token **token_lst);
t_cmd	*ft_lstnew_cmd(void);
t_cmd	*ft_lstlast_cmd(t_cmd *cmd);
void	ft_lstadd_back_cmd(t_cmd **cmd_lst, t_cmd *new_cmd);

// UTILS

char	*ft_del_edge_spaces(char *str);
bool 	ft_is_only_space(char *str);
bool	ft_is_whitespace(char *str, int i);
bool	ft_is_sep(char *str, int i);

// ERRORS

void	ft_error_quotes();
void	ft_syntax_error(char *str);

// CLEAN & EXIT

void	ft_free_data(t_data *data);
void	ft_free_ptr(void *ptr);
void	ft_token_lstclear(t_token **token_lst, void (*del)(void *));
int		ft_exit_code(int exit_code, int mode);

// DEBUG

void	print_tokens(t_token *token_lst);
void	print_cmd(t_cmd *cmd_lst);


#endif
