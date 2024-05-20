/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:46:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/05/20 17:08:45 by eltouma          ###   ########.fr       */
/*   Updated: 2024/05/15 18:13:25 by eltouma          ###   ########.fr       */
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
	dprintf(2, "666\n");
	while (cmds->i++ < cmds->list_size)
		ft_waitpid(cmds);
}

// static bool ft_add_shlvl(t_data *data, char *value)
// {
// 	t_env	*tmp;

// 	tmp = data->env;
// 	while (tmp)
// 	{
// 		if (ft_strcmp(tmp->var, "SHLVL") == 0)
// 		{
// 			ft_free_ptr(tmp->value);
// 			tmp->value = ft_strdup(value);
// 			ft_free_ptr(value);
// 			if (!tmp->value)
// 				return (ft_exit_code(12, ADD), false);
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (true);
// }
// static bool	ft_increase_shlvl(t_data *data)
// {
// 	char	*shlvl;
// 	int		count;

// 	dprintf(2, "on increase le shlvl\n");	
// 	shlvl = ft_var_is_exp(data, "SHLVL");
// 	count = ft_atoi(shlvl);
// 	count++;
// 	ft_free_ptr(shlvl);
// 	if (!ft_add_shlvl(data, ft_itoa(count)))
// 		return (false);
// 	return (true);
// }

int	ft_one_no_built_in_cmd(t_data *data, t_cmds *cmds, char **env)
{
	dprintf(2, "Je suis dans one NO BUILT_IN cmd\n");
//	dprintf(2, "cmds->name %s, dams no_built_in\n", cmds->name);
	cmds->pid = fork();
	if (cmds->pid == -1)
		ft_handle_fork_error(data, cmds);
	if (cmds->pid == 0)
	{
/*
		if (cmds->redir)
			ft_handle_redir(data, cmds);
		cmds->right_path = ft_get_cmd_path(data, cmds, cmds->cmd, cmds->args);
		execve(cmds->right_path, cmds->args, env);
		ft_handle_execve_error(data, cmds);
*/
		// if (!ft_strcmp(cmds->cmd, "./minishell") && (!ft_increase_shlvl(data)))
		// 	return (ft_exit_code(0, GET));
		ft_exec_cmds(data, cmds, env);
		dprintf(2, "TA MERE\n");
	}
	else if (cmds->pid > 0)
	{
		
		cmds->i = 0;
		while (cmds->i++ < cmds->list_size)
			ft_waitpid_only_one_cmd(cmds);
	}
	return (ft_exit_code(0, GET));
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
	{
		ft_dup_stdin_stdout(data, cmds);
		ft_handle_redir_without_cmd(data, cmds);
		ft_dup2_and_close_stdin_stdout(data, cmds);
		return (ft_exit_code(0, GET));
	}
	if (ft_is_a_built_in(cmds->cmd))
	{
		ft_dup_stdin_stdout(data, cmds);
		if (cmds->redir)
			ft_handle_redir(data, cmds);
		if (cmds->infile != -1 && cmds->outfile != -1)
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

void	ft_init_exec(t_cmds *cmds)
{
	while (cmds != NULL)
	{
		cmds->list_size = ft_lstsize_cmd(cmds);
		cmds = cmds->next;
	}
}


int	ft_handle_here_doc(t_data *data, t_cmds *cmds)
{
	int	status;
	t_redir * head;
	t_cmds	*tmp;
	pid_t	pid;


	tmp = cmds;
	pid = fork();
	if	(!pid)
	{
		while (cmds != NULL)
		{
			head = cmds->redir;	
			while (head != NULL)
			{
				if (head->type == 2)
				{
					ft_exec_here_doc(data, cmds, head);
			//		dprintf(2, "cmds->nae dans handle_here_doc %s\n", cmds->name);
					if (cmds->name)
						ft_free_ptr(cmds->name);
				}
				head = head->next;
			}
			cmds = cmds->next;
		}
		ft_free_tab(tmp->cmd_path);
		ft_clean_all(data);
		exit(0);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return WEXITSTATUS(status);
	return (-1);
}

/*
static char	**ft_test(t_data *data, t_env *env, t_cmds *cmds)
{
	(void)data;

        int     i;
	char	*var;
	char	*val;
        t_env   *tmp_env;

        i = 0;
        tmp_env = env;
        while (env != NULL)
        {
                var = ft_strjoin(env->var, "=");
                val = ft_strjoin(var, env->value);
                dprintf(2, "%s\n", val);
		cmds->mini_env = &val;
		free(var);
		free(val);
                i += 1;
                env = env->next;
        }
	env = tmp_env;
	return (cmds->mini_env);
}
*/

int	ft_exec(t_data *data, t_cmds *cmds, char **env)
{
//	t_data *tmp;
//	t_cmds *cmds2;
	
	// Voir avec Antoine le code erreur
	if (!cmds)
		return (ft_exit_code(0, GET));
//	cmds2 = cmds;
//	tmp = data;
	ft_init_exec(cmds);
//	ft_test(tmp, tmp->env, cmds2);
	//print_cmds(cmds);
	ft_is_max_here_doc_nb_reached(data, cmds);
	ft_handle_here_doc(data, cmds);
	if (cmds->list_size == 1)
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
//	dprintf(2, "Dans exec() name vaut : %s\n", cmds->name);
//	if (cmds->name != NULL)
	//	unlink(cmds->name);
//		free(cmds->name);
//	if (!ft_strcmp(cmds->cmd, "./minishell") && (!ft_increase_shlvl(data)))
//		return (ft_exit_code(0, GET));
	return (ft_exit_code(0, GET));
}

