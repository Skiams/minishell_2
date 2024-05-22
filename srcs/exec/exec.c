/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <eltouma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:46:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/05/22 18:07:50 by eltouma          ###   ########.fr       */
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

void	ft_init_exec(t_data *data, t_cmds *cmds)
{
	(void)data;
	while (cmds != NULL)
	{
		cmds->cmd_count = ft_lstsize_cmd(cmds);
		cmds = cmds->next;
	}
}

void	ft_handle_here_doc(t_data *data, t_cmds *cmds)
{
	t_redir	*head;
	t_cmds	*tmp;

	tmp = cmds;
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
//	ft_free_tab(tmp->cmd_path);
//	ft_free_tab(data->mini_env);
	//return (-1);
}

// Voir avec Antoine le code erreur
int	ft_exec(t_data *data, t_cmds *cmds, char **env)
{
	(void)env;
	if (!cmds)
		return (ft_exit_code(0, GET));
	ft_init_exec(data, cmds);
	ft_is_max_here_doc_nb_reached(data, cmds);
	ft_handle_here_doc(data, cmds);
	if (cmds->cmd_count == 1)
	{
		//ft_is_only_one_cmd(data, cmds, data->env);
		ft_is_only_one_cmd(data, cmds, NULL);
		ft_free_tab(cmds->cmd_path);
		ft_free_tab(data->mini_env);
	}
	else
	{
		if (pipe(cmds->prev_pipe) == -1)
			ft_handle_pipe_error(data, cmds);
		ft_handle_pipes(data, cmds, NULL);
		//		ft_handle_pipes(data, cmds, data->env);
	}
	return (ft_exit_code(0, GET));
}
