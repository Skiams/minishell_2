/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <eltouma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:08:04 by ahayon            #+#    #+#             */
/*   Updated: 2024/05/31 23:12:42 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "get_next_line/get_next_line.h"
# include "libft/libft.h"
# include "pipex.h"
# include "printf/srcs/ft_printf.h"
# include "structures.h"
# include <fcntl.h>
# include <limits.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define WARNING " → Warning\n"
# define CORRECT_ARGV " Please enter correct arguments:\n"
# define ARROW "\t→ "

extern int	g_sig_exit;

// TOKENIZATION

int			ft_add_sep(t_token **token_lst, int type, char *str, int i);
int			ft_define_token_type(char *str, int i);
t_token		*ft_lstnew_token(char *value, t_token_tp type);
void		ft_lstadd_back_token(t_token **token_lst, t_token *new_token);
t_token		*ft_lstlast_token(t_token *token);
bool		ft_tokenization(t_data *data);
int			ft_check_syntax(t_data *data);
bool		ft_check_quotes(char *str, int i);
int			ft_check_end_quotes(char *str, int i, char c);
bool		ft_clean_quotes(t_data *data);
char		*ft_remove_quotes(char *str, int code);
bool		ft_add_exp_token(t_token **token_lst, char *str);
bool		ft_check_space_expand(char *str);

// EXPAND

bool		ft_check_env_var(char *tmp_var, t_env *env);
char		*ft_expand(t_data *data, char *str);
int			ft_check_dollar(char *str);
char		*ft_strjoin_exp(char *s1, char *s2);
char		*ft_var_is_exp(t_data *data, char *str);
int			ft_expand_code(int expand_code, int mode);
char		*ft_classic_exp(t_data *data, char *str, size_t *i, int code);

// COMMANDS

bool		ft_get_cmds(t_data *data, t_token **token_lst);
t_cmds		*ft_last_cmd(t_cmds *cmd);
int			ft_lstsize_cmd(t_cmds *cmd);
bool		ft_set_args(t_cmds *last_cmd, t_token **token_list);
bool		ft_set_more_args(t_cmds *last_cmd, t_token **token_lst);
bool		ft_redir_cmd(t_cmds **cmd_lst, t_token **token_lst,
				t_token_tp type);
void		lst_add_back_cmd(t_cmds **cmd_lst, t_cmds *cmd);
t_cmds		*lst_new_cmd(void);
int			ft_args_nb(t_cmds *cmds);

// ENV

t_env		*ft_get_env(t_data *data, char **env);
t_env		*ft_lstnew_env(char *var, char *value);
void		ft_lstadd_back_env(t_env **env_lst, t_env *new_env);
t_env		*ft_lstlast_env(t_env *env);
char		**ft_lst_to_tab(t_data *data);
t_env		*ft_create_export_env(t_data *data);
bool		ft_lstinit_env(t_env **env, char *var, char *value);

// BUILT-INS

void		ft_order_export_env(t_env **export_env);
int			ft_display_export(t_data *data);
int			ft_export(t_data *data, char **args);
bool		ft_var_is_in_env(t_data *data, char *str);
int			ft_check_export_case(char *str);
void		ft_error_export(char *str, int code);
void		ft_order_export_env(t_env **export_env);
int			ft_display_export(t_data *data);
void		ft_echo(char **args);
int			ft_env(t_data *data);
int			ft_unset(t_data *data, char **args);
int			ft_pwd(t_cmds *cmds);
void		ft_exit(t_data *data, t_cmds *cmd);
void		ft_clean_exit(t_data *data, t_cmds *cmd);
void		ft_handle_exit_built_in(t_data *data, t_cmds *cmds);
int			ft_cd(t_cmds *cmd, t_data *data);
void		ft_print_cd_error(char **args);
bool		ft_add_value_only(t_data *data, char *var, char *value, int code);
bool		ft_add_var_and_value(t_data *data, char *str, int code);
bool		ft_add_var_and_value_bis(t_data *data, char *var, char *value,
				int code);
int			ft_export_bis(t_data *data, char *dup_arg, int code);
bool		ft_add_var_env(t_data *data, char *str, int code);

// EXEC
	// exec_cmds
int			ft_exec(t_data *data, t_cmds *cmds);
int			ft_is_only_one_cmd(t_data *data, t_cmds *cmds);
void		ft_handle_pipes(t_data *data, t_cmds *cmds);
void		ft_handle_processes(t_data *data, t_cmds *cmd);
int			ft_is_a_built_in(char *str);
void		ft_exec_built_in(t_data *data, t_cmds *cmds);
void		ft_exec_cmds(t_data *data, t_cmds *cmds);

	// redirections
void		ft_handle_redir(t_data *data, t_cmds *cmds);
void		ft_handle_output_and_append_redir(t_data *data, t_cmds *cmds);
void	ft_handle_input_redir(t_data *data, t_cmds *cmds, t_redir *tmp);

	// here_doc
int			ft_count_here_doc(t_cmds *cmds);
void		ft_is_max_here_doc_nb_reached(t_data *data, t_cmds *cmds);
void		ft_exec_here_doc(t_data *data, t_cmds *cmds, t_redir *redir, t_cmds *headcmds);
void		ft_close_hd_in_fork(t_cmds *headcmds, t_cmds *me);

	// split
int			ft_is_space(char c);
int			ft_count_words(char *str);
int			ft_count_size_of_word_colon(char *str);
int			ft_count_size_of_word(char *str);
char		*ft_fill_tab(char *str);
char		*ft_fill_tab_colon(char *str);
char		**ft_return_tab(char *str);
char		**ft_split_exec(char *str);

	// free
void		ft_free(t_data *data, t_cmds *cmds, char *cmd, char *error);
void		*ft_free_tab(char **tab);

	// errors
void		ft_handle_no_file_or_dir(t_data *data, t_cmds *cmds, char *cmd);
void		ft_handle_rights(t_data *data, t_cmds *cmds, char *cmd, char *tmp2);
void		ft_handle_directory(t_data *data, t_cmds *cmds, char *cmd, char **args);
void    	ft_handle_file_error(t_data *data, t_cmds *cmds);
void		ft_handle_pipe_error(t_data *data, t_cmds *cmds);
void		ft_handle_fork_error(t_data *data, t_cmds *cmds);
void		ft_handle_close_error(t_data *data, t_cmds *cmds);
void		ft_handle_execve_error(t_data *data, t_cmds *cmds);



// UTILS

char		*ft_del_edge_spaces(char *str);
bool		ft_is_only_spacetab(char *str);
bool		ft_is_whitespace(char *str, int i);
bool		ft_is_sep(char *str, int i);
char		*ft_strjoin_c(char *s1, char *s2, char c);

// ERRORS

void		ft_error_quotes(void);
void		ft_syntax_error(char *str);

// SIGNALS

void		ft_cc_handler(int sig);
void		ft_handle_signal(int code);
void		ft_handle_sig_heredoc(void);
void		ft_cc_heredoc(int sig);
void		ft_cc_blocking(int sig);

// CLEAN & EXIT

void		ft_free_env(t_env *env);
void		ft_free_data(t_data *data);
void		ft_free_ptr(void *ptr);
void		ft_token_lstclear(t_token **token_lst, void (*del)(void *));
void		ft_lstclear_cmd(t_cmds **cmd_lst, void (*del)(void *));
int			ft_exit_code(int exit_code, int mode);
void		ft_clean_all(t_data *data);
void		ft_clear_redirlst(t_redir **redir_list, void (*del)(void *));

// DEBUG

void		print_tokens(t_token *token_lst);
void		print_tab(char **tab);
void		print_env(t_env *env_lst);
void		print_cmds(t_cmds *cmd_list);
void		print_redir(t_redir *redir);

void		ft_lstclear_hd(t_hd **hd_lst, void (*del)(void *));
void		ft_lstdelone_hd(t_hd *hd, void (*del)(void *));
t_hd		*ft_last_hd(t_hd *hd);
void		lst_add_back_hd(t_hd **hd_lst, t_hd *hd);
t_hd		*lst_new_hd(char *name);

#endif
