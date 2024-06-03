/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:46:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/05/31 18:41:42 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_swap_pipes(t_data *data, t_cmds *cmds)
{
	if (close(cmds->prev_pipe[0]) == -1)
		ft_handle_close_error(data, cmds);
	if (close(cmds->prev_pipe[1]) == -1)
		ft_handle_close_error(data, cmds);
	if (cmds->next)
	{
		cmds->next->prev_pipe[0] = cmds->curr_pipe[0];
		cmds->next->prev_pipe[1] = cmds->curr_pipe[1];
	}
	ft_free_tab(cmds->cmd_path);
	ft_free_tab(data->mini_env);
}

static void	ft_fork_built_in_pipes(t_data *data, t_cmds *cmds, char **env)
{
	(void)env;
	cmds->pid = fork();
	if (cmds->pid == -1)
		ft_handle_fork_error(data, cmds);
	if (cmds->pid == 0)
		ft_handle_processes(data, cmds, NULL);
	if (cmds->here_doc_count > 0 && close(cmds->here_doc) == -1)
		ft_handle_close_error(data, cmds);
	//ft_handle_processes(data, cmds, data->mini_env);
	ft_waitpid_only_one_cmd(cmds);
}

static	void	ft_fork_no_built_in(t_data *data, t_cmds *cmds, char **env)
{
	(void)env;
	if (ft_strcmp(ft_var_is_exp(data, "SHLVL"), "2") == 0)
		ft_handle_signal(1, 2);
	else
		ft_handle_signal(2, 2);
	cmds->pid = fork();
	if (cmds->pid == -1)
		ft_handle_fork_error(data, cmds);
	if (cmds->pid == 0)
		ft_handle_processes(data, cmds, NULL);
	//		ft_handle_processes(data, cmds, data->env);
}

void	ft_handle_pipes(t_data *data, t_cmds *cmds, char **env)
{
	(void)env;
	t_cmds	*tmp;

	tmp = cmds;
	while (cmds && cmds != NULL)
	{
		ft_get_path(data, cmds);
		if (pipe(cmds->curr_pipe) == -1)
			ft_handle_pipe_error(data, cmds);
		if (ft_is_a_built_in(cmds->cmd))
			ft_fork_built_in_pipes(data, cmds, NULL);
		//ft_fork_built_in_pipes(data, cmds, data->env);
		else
			ft_fork_no_built_in(data, cmds, NULL);
		//ft_fork_no_built_in(data, cmds, data->env);
//		pas la
		ft_swap_pipes(data, cmds);
//		pas la
		if (cmds->next == NULL)
			break ;
		cmds = cmds->next;
	}
	cmds = tmp;
	cmds->i = 0;
	dprintf(2, "\n666\n");
//	if (cmds->here_doc_count > 0 && close(cmds->here_doc) == -1)
//		ft_handle_close_error(data, cmds);
	while (cmds->i++ < cmds->cmd_count)
		ft_waitpid(cmds);
	if (ft_strcmp(ft_var_is_exp(data, "SHLVL"), "2") == 0)
		ft_handle_signal(1, 1);
	else
		ft_handle_signal(2, 1);
}
