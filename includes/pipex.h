/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <eltouma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 15:17:53 by eltouma           #+#    #+#             */
/*   Updated: 2024/05/31 18:56:54 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include "get_next_line/get_next_line.h"
# include "minishell.h"
# include "printf/srcs/ft_printf.h"
# include "structures.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

void	ft_close_processes(t_cmds *cmds);
void	ft_waitpid_only_one_cmd(t_cmds *cmds);
void	ft_waitpid(t_cmds *cmds);

char	*ft_get_cmd_path(t_data *data, t_cmds *cmds, char *cmd, char **args);
char	*ft_get_absolute_path(t_data *data, t_cmds *cmds, char *cmd,
			char **args);


void	ft_exit_properly(t_data *data, t_cmds *cmds);

void	ft_dup_stdin_stdout(t_data *data, t_cmds *cmds);
void	ft_dup2_and_close_stdin_stdout(t_data *data, t_cmds *cmds);
void	ft_handle_dup2_error(t_data *data, t_cmds *cmds);


char	*ft_strdup(char *s);
void	ft_get_path(t_data *data, t_cmds *cmds);
char	**ft_return_mini_env(t_data *data, t_env *env);
char	*ft_strjoin(char *s1, char *s2);

void	ft_print_wrong_param(void);
void	ft_print_header(void);
void	ft_print_footer(void);

int		ft_is_space_only(char *str);
int		ft_is_slash_only(char *str);

char	*ft_handle_quotes_and_slash(char *argv);

#endif
