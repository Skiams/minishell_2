/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <eltouma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:46:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/05/21 19:04:43 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	int		status;
	t_redir	*head;
	t_cmds	*tmp;
	pid_t	pid;

	tmp = cmds;
	pid = fork();
	if (pid == 0)
	{
		while (cmds != NULL)
		{
			head = cmds->redir;
			while (head != NULL)
			{
				if (head->type == 2)
				{
					ft_exec_here_doc(data, cmds, head);
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
		return (WEXITSTATUS(status));
	return (-1);
}

// Voir avec Antoine le code erreur
int	ft_exec(t_data *data, t_cmds *cmds, char **env)
{
	if (!cmds)
		return (ft_exit_code(0, GET));
	ft_init_exec(cmds);
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
		ft_handle_pipes(data, cmds, env);
	}
	return (ft_exit_code(0, GET));
}
