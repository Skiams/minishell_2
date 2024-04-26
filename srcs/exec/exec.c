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

static void	ft_handle_multi_pipes(t_data *data, t_cmds *cmds, char **argv, char **env)
{
	(void)argv;

	t_cmds *tmp;

	tmp = cmds;
	while (cmds && cmds != NULL)
	{
		if (pipe(cmds->curr_pipe) == -1)
			ft_handle_pipe_error(cmds);
		cmds->pid = fork();
		if (cmds->pid == -1)
			ft_handle_fork_error(cmds);
		if (cmds->pid == 0)
			ft_handle_processes(data, cmds, &cmds->cmd, env);
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
		ft_waitpid(cmds);
}

int	ft_is_only_one_cmd(t_data *data, t_cmds *cmds, char **env)
{
	// Voir avec Antoine le code erreur
	char	*cmds_path;
	if (!cmds->args)
		return (ft_exit_code(0, GET));
	if (ft_is_a_built_in(cmds->cmd))
	{
/*
		while (cmds->redir)
		{
			int dev_null = open("/dev/stdin", O_WRONLY | O_CREAT | O_TRUNC, 0755);
			if (dev_null == -1)
				ft_putstr_fd("dev_null failed\n", 2);
			if (dup2(dev_null, 1) == -1)
				ft_handle_dup2_error(cmds);
			ft_handle_redir(data, cmds);
			if (close(dev_null) == -1)
				ft_handle_close_error(cmds);
			cmds->redir = cmds->redir->next;
		}
*/
		ft_exec_built_in(data, cmds);
		return (ft_exit_code(0, GET));
	}
	else
	{
		cmds->pid = fork();
		if (cmds->pid == -1)
			ft_handle_fork_error(cmds);
		if (cmds->pid == 0)
		{
			if (cmds->redir)
			{
				cmds->dev_stdin = open("/dev/stdin", O_WRONLY | O_CREAT | O_TRUNC, 0755);
				if (cmds->dev_stdin == -1)
					ft_putstr_fd("dev_stdin failed\n", 2);
				if (dup2(cmds->dev_stdin, 1) == -1)
					ft_handle_dup2_error(cmds);
				ft_handle_redir(data, cmds);
				if (close(cmds->dev_stdin) == -1)
					ft_handle_close_error(cmds);
			}
			while (cmds->redir)
			{
				ft_handle_redir(data, cmds);
				cmds->redir = cmds->redir->next;
			}
			cmds_path = ft_get_cmd_path(data, cmds, cmds->cmd, cmds->args);
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
			ft_handle_pipe_error(cmds);
		ft_handle_multi_pipes(data, cmds, &cmds->cmd, env);
	}
	return (ft_exit_code(0, GET));
}
