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

int	ft_is_only_one_cmd(t_data *data, t_cmds *cmds, char **env)
{
	char	*cmds_path;

	if (!cmds->cmd)
		return  (0);
	if (ft_is_a_built_in(cmds->cmd))
	{
		ft_exec_built_in(data, cmds);
		return (0);
	}
	else
	{
		cmds->pid = fork();
		if (cmds->pid == -1)
			ft_handle_fork_error2(cmds);
		if (cmds->pid == 0)
		{
			cmds_path = ft_get_cmd_path2(data, cmds, cmds->cmd, cmds->args);
			execve(cmds_path, cmds->args, env);
			ft_printf(2, "Attention tout le monde ! Je fail\n");
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
		ft_free_tab(cmds->cmd_path);
		return (ft_exit_code(0, GET));
	}
}

int	ft_exec(t_data *data, t_cmds *cmds, char **env)
{
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
		ft_is_only_one_cmd(data, cmds, env);
	else
	{
		if (pipe(cmds->prev_pipe) == -1)
			ft_handle_pipe_error2(cmds);
		ft_handle_multi_pipes2(data, cmds, &cmds->cmd, env);
	}
	return (ft_exit_code(0, GET));
}
