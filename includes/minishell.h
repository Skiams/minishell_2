/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skiam <skiam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:08:04 by ahayon            #+#    #+#             */
/*   Updated: 2024/04/03 20:48:24 by skiam            ###   ########.fr       */
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

# define ADD 1
# define GET 2
# define FREE 3
# define FREELST 4
# define DATALST 5
# define ENVLST 6


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

// typedef struct s_garb_env
// {
// 	void				*ptr;
// 	struct s_garb_env	*next;
// }	t_garb_env;

// typedef struct s_garb_data
// {
// 	void					*ptr;
// 	struct s_garb_data	*next;
// }	t_garb_data;


typedef struct s_env
{
	char			*var;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;


// typedef struct s_cmd
// {
// 	char			*value;
// 	char			**args;
// 	struct s_cmd	*next;
// 	struct s_cmd	*prev;
// }	t_cmd;

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
	//t_cmd	*cmd_list;
	t_env	*env;
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

// EXPAND

bool	ft_check_env_var(char *tmp_var, t_env *env);
void	ft_check_expand(t_data *data);

// ENV

t_env	*ft_get_env(t_data *data, char **env);
t_env	*ft_lstnew_env(char *var, char *value);
void	ft_lstadd_back_env(t_env **env_lst, t_env *new_env);
t_env	*ft_lstlast_env(t_env *env);

// PARSING COMMANDS

// bool	ft_set_cmd(t_data *data, t_token **token_lst);
// t_cmd	*ft_lstnew_cmd(void);
// t_cmd	*ft_lstlast_cmd(t_cmd *cmd);
// void	ft_lstadd_back_cmd(t_cmd **cmd_lst, t_cmd *new_cmd);

// BUILT-INS

void	ft_order_export_env(t_env **export_env);
int 	ft_display_export(t_data *data);
int 	ft_export(t_data *data, char **args);
bool	ft_var_is_in_env(t_data *data, char *str);
int		ft_check_export_case(char *str);
void	ft_error_export(char *str);
void	ft_order_export_env(t_env **export_env);
int		ft_display_export(t_data *data);
void	ft_echo(char **args);
int 	ft_env(t_data *data);
int		ft_unset(t_data *data, char **args);


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
//void	print_cmd(t_cmd *cmd_lst);
void	print_env(t_env *env_lst);


#endif
