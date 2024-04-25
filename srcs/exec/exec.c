/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <eltouma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:46:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/04/21 22:42:47 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_handle_multi_pipes2(t_data *data, t_cmds *cmds, char **argv, char **env)
{
	(void)argv;

	t_cmds *tmp;
	
	tmp = cmds;
	while (cmds && cmds != NULL)
	{
		if (pipe(cmds->curr_pipe) == -1)
			ft_handle_pipe_error2(cmds);
		cmds->pid = fork();
		if (cmds->pid == -1)
			ft_handle_fork_error2(cmds);
		if (cmds->pid == 0)
			ft_handle_processes2(data, cmds, &cmds->cmd, env);
		else if (cmds->pid > 0)
		{
			close(cmds->prev_pipe[0]);
			close(cmds->prev_pipe[1]);
			if (cmds->next)
			{
				cmds->next->prev_pipe[0] = cmds->curr_pipe[0];
				cmds->next->prev_pipe[1] = cmds->curr_pipe[1];
			}
			ft_free_tab(cmds->cmd_path);
			if (cmds->next == NULL)
				break;
		}
		cmds = cmds->next;
	}
	cmds = tmp;
	cmds->i = 0;
	while (cmds->i++ < cmds->argc)
		ft_waitpid2(cmds);
}

/*
int	ft_is_a_redir(t_cmds *cmds)
{
	t_redir	*redir;

	redir = cmds->redirections;
	while (redir)
	{
		if (redir->type == RED_OUT) // && !ft_handle_outfile(redir, &status))
			return (1);
		redir = redir->next;
	}
	return (0);
}

*/
int	ft_is_only_one_cmd(t_data *data, t_cmds *cmds, char **env)
{
	// Voir avec Antoine le code erreur
	char	*cmds_path;

	if (!cmds->args)
	{
//		if (ft_is_a_redir(cmds))
//			ft_putstr_fd("oui\n", 2);
		return (ft_exit_code(0, GET));
	}
	if (ft_is_a_built_in(cmds->cmd))
	{
		ft_exec_built_in(data, cmds);
		ft_putstr_fd("\n\nUne seule commande built-in\n\n", 1);
		return (0);
	}
	else
	{
		if (cmds->redir)
		{
			ft_putstr_fd("redir ici\n", 1);
			if (pipe(cmds->prev_pipe) == -1)
				ft_handle_pipe_error2(cmds);
		}
		cmds->pid = fork();
		if (cmds->pid == -1)
			ft_handle_fork_error2(cmds);
		if (cmds->pid == 0)
		{
			if (cmds->redir)
			{
				ft_putstr_fd("Je suis apres le fork()\n", 1);
				cmds->infile = open(cmds->redir->path, O_WRONLY, 0755);
				if (cmds->infile == -1)
					ft_handle_file_error2(cmds->redir->path, cmds, data);
				if (dup2(cmds->infile, 0) == -1)
					ft_handle_dup2_error2(cmds);
				if (close(cmds->infile) == -1)
					ft_handle_close_error2(cmds);
				if (close(cmds->prev_pipe[0]) == -1)
					ft_handle_close_error2(cmds);
				if (dup2(cmds->prev_pipe[1], 1) == -1)
					ft_handle_dup2_error2(cmds);
				if (close(cmds->prev_pipe[1]) == -1)
					ft_handle_close_error2(cmds);
			}
			cmds_path = ft_get_cmd_path2(data, cmds, cmds->cmd, cmds->args);
			execve(cmds_path, cmds->args, env);
			ft_putstr_fd("Attention tout le monde ! Je fail\n", 2);
			ft_putstr_fd("minishell: ", 2);
			perror(cmds_path);
			free(cmds_path);
			ft_free_tab(cmds->cmd_path);
			ft_clean_all(data);
			ft_exit_code(1, ADD);
			exit (1);
		}
		else if (cmds->pid > 0)
		{
			cmds->i = 0;
			while (cmds->i++ < cmds->argc)
				ft_waitpid_only_one_cmd(cmds);
		}
		return (ft_exit_code(0, GET));
	}
}

int	ft_exec(t_data *data, t_cmds *cmds, char **env, t_redir *redir)
{
	(void)redir;
	t_cmds	*tmp;

	tmp = cmds;
	// Voir avec Antoine le code erreur
	if (!cmds)
		return (0);
	while (cmds != NULL)
	{
		cmds->argc = ft_lstsize_cmd(cmds);
		ft_get_path(cmds, env);
		cmds = cmds->next;
	}
	cmds = tmp;
	if (cmds->argc == 1)
	{
//		Pour la norme
//		ft_is_only_one_cmd(data, cmds, env), ft_free_tab(cmds->cmd_path);
		ft_is_only_one_cmd(data, cmds, env);
		ft_free_tab(cmds->cmd_path);
	}
	else
	{
		if (pipe(cmds->prev_pipe) == -1)
			ft_handle_pipe_error2(cmds);
		ft_handle_multi_pipes2(data, cmds, &cmds->cmd, env);
	}
	return (ft_exit_code(0, GET));
}
