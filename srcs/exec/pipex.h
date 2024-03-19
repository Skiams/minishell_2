/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 15:17:53 by eltouma           #+#    #+#             */
/*   Updated: 2024/03/19 17:02:19 by eltouma          ###   ########.fr       */
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
# include "../printf/srcs/ft_printf.h"

# define WARNING	 " → Warning\n"
# define CORRECT_ARGV		" Please enter correct arguments:\n"
# define ARROW	"\t→ "

typedef struct s_pipex
{
	int		fd_pipe[2];
	int		infile;
	int		outfile;
	int		code_status;
	pid_t	cmd1;
	pid_t	cmd2;
	char	*env_path;
	char	**cmd_path;
}		t_pipex;

void	ft_close_processes(t_pipex *pipex);
void	ft_child_process(t_pipex *pipex, char **argv, char **env);
void	ft_handle_parent(t_pipex *pipex, char **argv);
void	ft_parent_process(t_pipex *pipex, char **argv, char **env);

int		ft_strlen(char *str);
int		ft_count_words(char *str);
int		ft_count_size_of_word(char *str);
char	**ft_split(char *str);
void	*ft_free_tab(char **tab);

char	*ft_strdup(char *s);
int		ft_strchr(char *str, char c);
void	ft_get_env(t_pipex *pipex, char **env);
char	*ft_strjoin(char *s1, char *s2);
void	*ft_memset(void *s, int c, unsigned int n);

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

void	ft_putstr_fd(char *str, int fd);
void	ft_handle_file_error(char **argv, t_pipex *pipex);
void	ft_handle_cmd_path_error(t_pipex *pipex);
void	ft_handle_pipe_error(t_pipex *pipex);
void	ft_handle_fork_error(t_pipex *pipex);
void	ft_handle_close_error(t_pipex *pipex);
void	ft_handle_dup2_error(t_pipex *pipex);
#endif
