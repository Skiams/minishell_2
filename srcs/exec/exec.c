/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:46:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/04/18 20:58:19 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/pipex.h"

/*
   static void	ft_handle_multi_pipes(t_data *data, t_pipex *pipex, char **argv, char **env)
   {
   while (pipex->i < pipex->argc - 3)
   {
   if (pipe(pipex->curr_pipe) == -1)
   ft_handle_pipe_error(pipex);
   pipex->pid1 = fork();
   if (pipex->pid1 == -1)
   ft_handle_fork_error(pipex);
   if (pipex->pid1 == 0)
   ft_handle_processes(data, pipex, argv, env);
   else if (pipex->pid1 > 0)
   {
   close(pipex->prev_pipe[0]);
   close(pipex->prev_pipe[1]);
   pipex->prev_pipe[0] = pipex->curr_pipe[0];
   pipex->prev_pipe[1] = pipex->curr_pipe[1];
   }
   pipex->i += 1;
   }
   }
 */
static void	ft_handle_multi_pipes2(t_data *data, t_cmds *cmds, char **argv, char **env)
{
	(void)data;
	(void)cmds;
	(void)env;
	(void)argv;

	ft_printf(1, "\nhandle_multi_pipes()\n\n");
	//	ft_printf(1, "cmds->i:\t%d\n\n", cmds->i);
/*
	int	j = 0;
	while (cmds->cmd != NULL && j < cmds->argc)
	{
		ft_printf(1, "cmds->cmd\t%s\n", cmds->cmd);
		cmds = cmds->next;
		j += 1;
	}
*/
	while (cmds->i < cmds->argc)
	{
		ft_printf(2, "argc vaut : %d\n", cmds->argc);
		ft_printf(2, "i vaut : %d\n", cmds->i);
		if (pipe(cmds->curr_pipe) == -1)
			ft_handle_pipe_error2(cmds);
		cmds->pid1 = fork();
		if (cmds->pid1 == -1)
			ft_handle_fork_error2(cmds);
		if (cmds->pid1 == 0)
			ft_handle_processes2(data, cmds, &cmds->cmd, env);
		else if (cmds->pid1 > 0)
		{
			close(cmds->prev_pipe[0]);
			close(cmds->prev_pipe[1]);
			cmds->prev_pipe[0] = cmds->curr_pipe[0];
			cmds->prev_pipe[1] = cmds->curr_pipe[1];
		}
//`		cmds = cmds->next;
		cmds->i += 1;
	}
	ft_close_processes2(cmds);
	cmds->i = 0;
	while (cmds->i++ < cmds->argc)
		ft_waitpid2(cmds);
}

int	ft_is_only_one_cmd(t_data *data, t_cmds *cmds, char **env)
{
	char	*cmds_path;

	//	if (!cmds)
	//		return (0);
	if (!cmds->cmd)
		return  (0);
	if (ft_is_a_built_in(cmds->cmd))
	{
		ft_exec_built_in(data, cmds);
		return (0);
	}
	else
	{
		cmds->pid1 = fork();
		if (cmds->pid1 == -1)
			ft_handle_fork_error2(cmds);
		if (cmds->pid1 == 0)
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
		else if (cmds->pid1 > 0)
		{
			cmds->i = 0;
			while (cmds->i++ < cmds->argc)
				ft_waitpid_only_one_cmd(cmds);
		}
		return (ft_exit_code(0, GET));
	}
}

int	ft_exec(t_data *data, t_cmds *cmds, int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_pipex	pipex;

	ft_memset(&pipex, 0, sizeof(t_pipex));
	// Voir avec Antoine le code erreur
	if (!cmds)
		return (0);
	cmds->argc = ft_lstsize_cmd(cmds);
	cmds->i = 0;
	//	ft_exec_here_doc(&pipex, argv);
	ft_get_path(cmds, env);
	ft_printf(1, "\nNombre de commandes: cmds->argc ➡️ \t%d\n", cmds->argc);
	ft_printf(1, "\ni ➡️ \t%d\n", cmds->i);
	if (cmds->argc == 1)
		ft_is_only_one_cmd(data, cmds, env);
	else
	{
		if (pipe(cmds->prev_pipe) == -1)
			ft_handle_pipe_error2(cmds);
		ft_handle_multi_pipes2(data, cmds, &cmds->cmd, env);
	}
	ft_free_tab(pipex.cmd_path);
	ft_free_tab(cmds->cmd_path);
	return (0);
}
