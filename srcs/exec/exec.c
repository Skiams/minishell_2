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
void    ft_handle_close_error2(t_data *data, t_cmds *cmds)
{
	ft_putstr_fd("close failed\n", 2);
	ft_free_tab(cmds->cmd_path);
	close(cmds->outfile);
	ft_free_tab(cmds->cmd_path);
	ft_clean_all(data);
	ft_close_processes(cmds);
	exit (1);
}


static void	ft_handle_multi_pipes(t_data *data, t_cmds *cmds, char **env)
{
	t_cmds *tmp;

	tmp = cmds;
	while (cmds && cmds != NULL)
	{
		if (pipe(cmds->curr_pipe) == -1)
			ft_handle_pipe_error(cmds);
		if (ft_is_a_built_in(cmds->cmd))
			ft_exec_built_in(data, cmds);
		//				if (close(cmds->prev_pipe[1]) == -1)
		//				{
		//					ft_putstr_fd("Ma cravate est laaiiide\n", 2);
		//					ft_handle_close_error2(data, cmds);
		//				}		

		//			ft_exec_built_in(data, cmds);
		else 
		{
			cmds->pid = fork();
			if (cmds->pid == -1)
				ft_handle_fork_error(cmds);
			if (cmds->pid == 0)
				ft_handle_processes(data, cmds, &cmds->cmd, env);
		}
		if (close(cmds->prev_pipe[0]) == -1)
		{
			ft_putstr_fd("Oh nooon ! Mes fraises sont molles\n", 2);
			ft_handle_close_error2(data, cmds);
		}
		if (close(cmds->prev_pipe[1]) == -1)
		{
			ft_putstr_fd("Oh nooooon ! J'ai fait une tache de fraise molle sur ma cravate laaaiiide\n", 2);
			ft_handle_close_error2(data, cmds);
		}
		if (cmds->next)
		{
			cmds->next->prev_pipe[0] = cmds->curr_pipe[0];
			cmds->next->prev_pipe[1] = cmds->curr_pipe[1];
		}
		ft_free_tab(cmds->cmd_path);
		if (cmds->next == NULL)
			break;
		cmds = cmds->next;
	}
	cmds = tmp;
	cmds->i = 0;
	while (cmds->i++ < cmds->argc)
		ft_waitpid(cmds);
}

int	ft_one_no_built_in_cmd(t_data *data, t_cmds *cmds, char **env)
{
	cmds->pid = fork();
	if (cmds->pid == -1)
		ft_handle_fork_error(cmds);
	if (cmds->pid == 0)
	{
		if (cmds->redir)
			ft_handle_redir(data, cmds);
		cmds->right_path = ft_get_cmd_path(data, cmds, cmds->cmd, cmds->args);
		execve(cmds->right_path, cmds->args, env);
		ft_handle_execve_error(data, cmds);
	}
	else if (cmds->pid > 0)
	{
		cmds->i = 0;
		while (cmds->i++ < cmds->argc)
			ft_waitpid_only_one_cmd(cmds);
	}
	return (ft_exit_code(0, GET));
}

int	ft_is_only_one_cmd(t_data *data, t_cmds *cmds, char **env)
{
	// Voir avec Antoine le code erreur
	if (!cmds->args)
		return (ft_handle_redir_without_cmd(data, cmds));
	if (ft_is_a_built_in(cmds->cmd))
	{
		ft_dup_stdin_stdout(data, cmds);
		if (cmds->redir)
			ft_handle_redir(data, cmds);
		ft_exec_built_in(data, cmds);
		ft_dup2_and_close_stdin_stdout(data, cmds);
		return (ft_exit_code(0, GET));
	}
	else
		return (ft_one_no_built_in_cmd(data, cmds, env));
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
		ft_is_only_one_cmd(data, cmds, env), ft_free_tab(cmds->cmd_path);
	else
	{
		if (pipe(cmds->prev_pipe) == -1)
			ft_handle_pipe_error(cmds);
		ft_handle_multi_pipes(data, cmds, env);
	}
	return (ft_exit_code(0, GET));
}
