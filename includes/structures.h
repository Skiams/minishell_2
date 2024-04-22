/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:08:04 by ahayon            #+#    #+#             */
/*   Updated: 2024/04/20 15:11:50 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef enum e_rule
{
	ADD,
	GET,
	MALLOC,
	FREE,
	FREEALL,
	DATALST,
	ENVLST,
}	t_rule;

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

typedef struct s_env
{
	char			*var;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_redir
{
	int				type;
	char			*path;
	char			**args;
	struct s_redir	*next;
	struct s_redir	*prev;	
}	t_redir;

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
	char	**argv;
	char	*env_path;
	char	**cmd_path;
}		t_pipex;

typedef struct s_cmds
{
	t_redir	*redirections;
	char	*env_path;
	char	**cmd_path;
	char	*cmd;
	char	**args;
	int		curr_pipe[2];
	int		prev_pipe[2];
	int		argc;
	int		i;
	int		here_doc;
	int		is_here_doc;
	int		code_status;
	pid_t	pid;
	struct s_cmds	*next;
	struct s_cmds	*prev;
	t_pipex	*pipex;
}	t_cmds;

typedef struct s_token
{
	int				quote_type;
	char			*value;
	t_token_tp		type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_data
{
	char	*input;
	char	**cmds_exec;
	char	**env_exec;
	int		status;
	int		infile;
	int		outfile;
	t_token	*token_list;
	t_cmds	*cmd_list;
	t_redir	*redir_list;
	t_env	*env;
}	t_data;

#endif
