/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skiam <skiam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 15:17:53 by eltouma           #+#    #+#             */
/*   Updated: 2024/04/11 23:59:41 by eltouma          ###   ########.fr       */
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
# include "printf/srcs/ft_printf.h"
# include "get_next_line/get_next_line.h"

# define WARNING	 " → Warning\n"
# define CORRECT_ARGV		" Please enter correct arguments:\n"
# define ARROW	"\t→ "

typedef struct s_pipex
{
	int		curr_pipe[2];
	int		prev_pipe[2];
	int		i;
	int		argc;
	int		here_doc;
	int		is_here_doc;
	int		infile;
	int		outfile;
	int		code_status;
	pid_t	pid1;
	pid_t	pid2;
	char	*env_path;
	char	**cmd_path;
}		t_pipex;

void	ft_exec_here_doc(t_pipex *pipex, char **argv);
void	ft_handle_processes(t_pipex *pipex, char **argv, char **env);
void	ft_close_processes(t_pipex *pipex);
void	ft_waitpid(t_pipex *pipex);

int		ft_count_words(char *str);
int		ft_count_size_of_word(char *str);
char	**ft_split_exec(char *str);
void	*ft_free_tab(char **tab);

char	*ft_strdup(char *s);
void	ft_get_path(t_pipex *pipex, char **env);
char	*ft_strjoin(char *s1, char *s2);

void	ft_print_missing_param(void);
void	ft_print_header(void);
void	ft_print_footer(void);

char	*ft_get_cmd_path(t_pipex *pipex, char *argv, char **cmds_path);
char	*ft_get_absolute_path(t_pipex *pipex, char *argv, char **path);
void	ft_handle_no_file_or_dir(char *argv);
void	ft_handle_directory(t_pipex *pipex, char *argv, char **path);
void	ft_handle_rights(t_pipex *pipex, char *argv, char **path, char *tmp2);
void	ft_free(t_pipex *pipex, char *argv, char **path, char *error);
int		ft_is_space_only(char *str);
int		ft_is_slash_only(char *str);
void	ft_handle_space_error(char **argv, t_pipex *pipex);
void	ft_handle_slash_error(char **argv, t_pipex *pipex);
char	*ft_handle_quotes_and_slash(char *argv);

void	ft_putstr_fd(char *str, int fd);
void	ft_handle_file_error(char **argv, t_pipex *pipex);
void	ft_handle_cmd_path_error(t_pipex *pipex);
void	ft_handle_pipe_error(t_pipex *pipex);
void	ft_handle_fork_error(t_pipex *pipex);
void	ft_handle_close_error(t_pipex *pipex);
void	ft_handle_dup2_error(t_pipex *pipex);

#endif
