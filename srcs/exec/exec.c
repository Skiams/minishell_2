/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skiam <skiam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:46:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/05/03 17:37:05 by skiam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_handle_multi_pipes(t_data *data, t_cmds *cmds, char **env)
{
	t_cmds	*tmp;

	tmp = cmds;
	while (cmds && cmds != NULL)
	{
		ft_get_path(cmds, env);
		if (pipe(cmds->curr_pipe) == -1)
			ft_handle_pipe_error(data, cmds);
		if (ft_is_a_built_in(cmds->cmd))
		{
			cmds->pid = fork();
			if (cmds->pid == -1)
				ft_handle_fork_error(data, cmds);
			if (cmds->pid == 0)
				ft_handle_processes(data, cmds, env);
			ft_waitpid_only_one_cmd(cmds);
		}
		else
		{
			cmds->pid = fork();
			if (cmds->pid == -1)
				ft_handle_fork_error(data, cmds);
			if (cmds->pid == 0)
				ft_handle_processes(data, cmds, env);
		}
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
		if (cmds->next == NULL)
			break ;
		cmds = cmds->next;
	}
	cmds = tmp;
	cmds->i = 0;
	while (cmds->i++ < cmds->argc)
		ft_waitpid(cmds);
}

int	ft_one_no_built_in_cmd(t_data *data, t_cmds *cmds, char **env)
{
//	dprintf(2, "on est dans one no built in\n");
	cmds->pid = fork();
	if (cmds->pid == -1)
		ft_handle_fork_error(data, cmds);
	if (cmds->pid == 0)
	{
//		dprintf(2, "j'arrive la\n");
		if (cmds->redir)
			ft_handle_redir(data, cmds);
//		dprintf(2, "pourquoi je ne passe pas la\n");
		ft_exec_cmds(data, cmds, env);
	}
	else if (cmds->pid > 0)
	{
		cmds->i = 0;
		while (cmds->i++ < cmds->argc)
			ft_waitpid_only_one_cmd(cmds);
	}
	return (ft_exit_code(0, GET));
}

void	ft_handle_exit_built_in(t_data *data, t_cmds *cmds)
{
	if (!ft_strcmp(cmds->cmd, "exit"))
		ft_exit(data, cmds);
}

/*
 * Pourquoi ce if (cmds->infile != -1) ?
 *
 * On a set cmds->infile a 0 au debut
 * S'il est a -1 c'est qu'il y a eu une erreur, qu'on n'a pas pu l'ouvrir
 * S'il est au contraire il est != -1, c'est que tout s'est bien passe, qu'on a un infile
 * Et la deux options :
 * 	1 - la commande est exit, donc il close stdin/stdout qu'on avait ouvert avant de quitter
 * 	2 - la commande n'est pas exit, on l'execute
 */
int	ft_is_only_one_cmd(t_data *data, t_cmds *cmds, char **env)
{
	// Voir avec Antoine le code erreur
	dprintf(2, "Je suis dans only_one_cmd\n");
	ft_get_path(cmds, env);
	if (!ft_strcmp(cmds->cmd, ":") || !ft_strcmp(cmds->cmd, "!"))
	{
		ft_putstr_fd("", 1);
		return (ft_exit_code(0, GET));
	}
	if (!cmds->args)
		return (ft_handle_redir_without_cmd(data, cmds));
	if (ft_is_a_built_in(cmds->cmd))
	{
		ft_dup_stdin_stdout(data, cmds);
		if (cmds->redir)
			ft_handle_redir(data, cmds);
//		dprintf(2, "Est-ce que je repasse ici ?\n");
		if (cmds->infile != -1)
		{
			ft_handle_exit_built_in(data, cmds);
			ft_exec_built_in(data, cmds);
		}
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
		cmds->infile = 0;
		cmds->outfile = 0;
		cmds->here_doc_count = 0;
		cmds->right_path = NULL;
		cmds->cmd_path = NULL;
		cmds = cmds->next;
	}
	cmds = tmp;
	if (cmds->argc == 1)
	{
		ft_is_only_one_cmd(data, cmds, env);
		ft_free_tab(cmds->cmd_path);
	}
	else
	{
		if (pipe(cmds->prev_pipe) == -1)
			ft_handle_pipe_error(data, cmds);
		ft_handle_multi_pipes(data, cmds, env);
	}
	return (ft_exit_code(0, GET));
}
