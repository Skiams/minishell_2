/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 15:17:53 by eltouma           #+#    #+#             */
/*   Updated: 2024/04/20 20:18:41 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "structures.h"
# include "minishell.h"
# include "printf/srcs/ft_printf.h"
# include "get_next_line/get_next_line.h"

# define WARNING	 " → Warning\n"
# define CORRECT_ARGV		" Please enter correct arguments:\n"
# define ARROW	"\t→ "

int		ft_exec(t_data *data, t_cmds *cmds, char **env, t_redir *redir);
int     	ft_is_a_built_in(char *str);
void    ft_exec_built_in(t_data *data, t_cmds *cmds);
int     ft_is_a_built_in(char *str);

void	ft_close_processes(t_cmds *cmds);
void	ft_waitpid_only_one_cmd(t_cmds *cmds);
void	ft_waitpid(t_cmds *cmds);

char	*ft_get_cmd_path(t_data *data, t_cmds *cmds, char *cmd, char **args);
char	*ft_get_absolute_path(t_data *data, t_cmds *cmds, char *cmd, char **args);

void	ft_free(t_data *data, t_cmds *cmds, char *cmd, char *error);

void	ft_handle_pipe_error(t_cmds *cmds);
void	ft_handle_infile_error(char *argv, t_cmds *cmds, t_data *data);
void	ft_handle_outfile_error(char *argv, t_cmds *cmds, t_data *data);
void	ft_handle_fork_error(t_cmds *cmds);
void	ft_handle_dup2_error(t_cmds *cmds);
void	ft_handle_close_error(t_cmds *cmds);

void	ft_handle_no_file_or_dir(t_data *data, t_cmds *cmds, char *cmd, char **args);
void	ft_handle_rights(t_data *data, t_cmds *cmds, char *cmd, char **args, char *tmp2);
void	ft_handle_directory(t_data *data, t_cmds *cmds, char *cmd, char **args);

void	ft_handle_processes(t_data *data, t_cmds *cmd, char **argv, char **env);
int     	ft_is_only_one_cmd(t_data *data, t_cmds *cmds, char **env);
void	ft_handle_first_cmd(t_data *data, t_cmds *cmds);
void	ft_exec_cmds(t_data *data, t_cmds *cmds, char **argv, char **env);

void	ft_handle_input_redir(t_data *data, t_cmds *cmds);
void	ft_handle_output_redir(t_data *data, t_cmds *cmds);
void	ft_exec_here_doc(t_data *data, t_cmds *cmds);
void	ft_handle_here_doc(t_data *data, t_cmds *cmds);

int		ft_count_words(char *str);
int		ft_count_size_of_word(char *str);
char	**ft_split_exec(char *str);
void	*ft_free_tab(char **tab);

char	*ft_strdup(char *s);
void	ft_get_path(t_cmds *cmds, char **env);
char	*ft_strjoin(char *s1, char *s2);

void	ft_print_wrong_param(void);
void	ft_print_header(void);
void	ft_print_footer(void);

int		ft_is_space_only(char *str);
int		ft_is_slash_only(char *str);

char	*ft_handle_quotes_and_slash(char *argv);

#endif
