/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skiam <skiam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:08:04 by ahayon            #+#    #+#             */
/*   Updated: 2024/05/06 17:55:21 by skiam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <linux/limits.h>
# include <stdbool.h>
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/types.h>
# include "structures.h"
# include "libft/libft.h"
# include "printf/srcs/ft_printf.h"
# include "get_next_line/get_next_line.h"
# include "pipex.h"

extern int	g_sig_exit;

// TOKENIZATION

int		ft_add_sep(t_token **token_lst, int type, char *str, int i);
int		ft_add_word(t_data *data, t_token **token_lst, char *str, int i);
int		ft_add_token(t_data *data, char *str, int type, int i);
int		ft_define_token_type(char *str, int i);
t_token	*ft_lstnew_token(char *value, t_token_tp type);
void	ft_lstadd_back_token(t_token **token_lst, t_token *new_token);
t_token	*ft_lstlast_token(t_token *token);
bool	ft_tokenization(t_data *data);
int		ft_check_syntax(t_data *data);
bool	ft_check_quotes(char *str, int i);
int		ft_check_end_quotes(char *str, int i, char c);
bool	ft_clean_quotes(t_data *data);
char	*ft_remove_quotes(char *str);
bool	ft_add_exp_token(t_token **token_lst, char *str);
bool	ft_check_space_expand(char *str);

// EXPAND

bool	ft_check_env_var(char *tmp_var, t_env *env);
char	*ft_expand(t_data *data, char *str);
int		ft_check_dollar(char *str);
char	*ft_strjoin_exp(char *s1, char *s2);
void	ft_init_var_exp(char **tmp_var, char **exp_rest, int *i, int *start);
char	*ft_var_is_exp(t_data *data, char *str);
char	*ft_exp_question_m(t_data *data);
char	*ft_exp_pid(t_data *data);
int 	ft_expand_code(int expand_code, int mode);

// COMMANDS

bool	ft_get_cmds(t_data *data, t_token **token_lst);
t_cmds	*ft_last_cmd(t_cmds *cmd);
int		ft_lstsize_cmd(t_cmds *cmd);
bool	ft_set_args(t_cmds *last_cmd, t_token **token_list);
bool	ft_set_more_args(t_cmds *last_cmd, t_token **token_lst);
bool	ft_redir_cmd(t_cmds **cmd_lst, t_token **token_lst, t_token_tp type);
void	lst_add_back_cmd(t_cmds **cmd_lst, t_cmds *cmd);
t_cmds	*lst_new_cmd(void);
int     ft_args_nb(t_cmds *cmds);

// ENV

t_env	*ft_get_env(t_data *data, char **env);
t_env	*ft_lstnew_env(char *var, char *value);
void	ft_lstadd_back_env(t_env **env_lst, t_env *new_env);
t_env	*ft_lstlast_env(t_env *env);
char	**ft_lst_to_tab(t_data *data);
t_env   *ft_create_export_env(t_data *data);
bool	ft_lstinit_env(t_env **env, char *var, char *value);

// BUILT-INS

void	ft_order_export_env(t_env **export_env);
int		ft_display_export(t_data *data);
int		ft_export(t_data *data, char **args);
bool	ft_var_is_in_env(t_data *data, char *str);
int		ft_check_export_case(char *str);
void	ft_error_export(char *str);
void	ft_order_export_env(t_env **export_env);
int		ft_display_export(t_data *data);
void	ft_echo(char **args);
int		ft_env(t_data *data);
int		ft_unset(t_data *data, char **args);
int		ft_pwd(t_cmds *cmds);
void	ft_exit(t_data *data, t_cmds *cmd);
void	ft_handle_exit_built_in(t_data *data, t_cmds *cmds);
int 	ft_cd(t_cmds *cmd, t_data *data);
bool	ft_add_value_only(t_data *data, char *var, char *value, int code);

// UTILS

char	*ft_del_edge_spaces(char *str);
bool	ft_is_only_spacetab(char *str);
bool	ft_is_whitespace(char *str, int i);
bool	ft_is_sep(char *str, int i);
char	*ft_strjoin_c(char *s1, char *s2, char c);

// ERRORS

void	ft_error_quotes(void);
void	ft_syntax_error(char *str);

// SIGNALS

void	ft_cc_handler(int sig);
void	ft_handle_signal();

// CLEAN & EXIT

void	ft_free_env(t_env *env);
void	ft_free_data(t_data *data);
void	ft_free_ptr(void *ptr);
void	ft_token_lstclear(t_token **token_lst, void (*del)(void *));
void	ft_lstclear_cmd(t_cmds **cmd_lst, void (*del)(void *));
int		ft_exit_code(int exit_code, int mode);
void	ft_clean_all(t_data *data);
void	ft_clear_redirlst(t_redir **redir_list, void (*del)(void *));

// DEBUG

void	print_tokens(t_token *token_lst);
void	print_tab(char **tab);
void	print_env(t_env *env_lst);
void	print_cmds(t_cmds *cmd_list);
void	print_redir(t_redir *redir);

#endif
