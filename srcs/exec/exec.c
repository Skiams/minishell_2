/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:46:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/06/16 20:58:06 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_close_hd_sig(t_data *data, t_cmds *head_cmds)
{
	t_redir	*head;
	t_cmds	*tmp;

	tmp = head_cmds;
	while (tmp != NULL)
	{
		head = tmp->redir;
		while (head != NULL)
		{
			if (head->type == HEREDOC)
			{
				if (close(tmp->hd_read) == -1)
					ft_handle_close_error(data, head_cmds);
			}
			head = head->next;
		}
		tmp = tmp->next;
	}
}

static void	ft_init_exec(t_cmds *cmds)
{
	while (cmds != NULL)
	{
		cmds->cmd_count = ft_lstsize_cmd(cmds);
		cmds = cmds->next;
	}
}

int	ft_handle_here_doc(t_data *data, t_cmds *cmds)
{
	t_redir	*head;
	t_cmds	*head_cmds;

	head_cmds = cmds;
	while (cmds != NULL)
	{
		head = cmds->redir;
		while (head != NULL)
		{
			if (head->type == 2)
			{
				if (!ft_exec_here_doc(data, cmds, head, head_cmds))
					return (-2);
			}
			head = head->next;
		}
		cmds = cmds->next;
	}
	return (-1);
}

// Voir avec Antoine le code erreur
int	ft_exec(t_data *data, t_cmds *cmds)
{
	if (!cmds)
		return (ft_exit_code(0, GET));
	ft_init_exec(cmds);
	ft_is_max_here_doc_nb_reached(data, cmds);
	if (ft_handle_here_doc(data, cmds) == -2)
		return (ft_exit_code(0, GET));
	if (cmds->cmd_count == 1)
	{
		ft_is_only_one_cmd(data, cmds);
		ft_free_tab(cmds->cmd_path);
		ft_free_tab(data->mini_env);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		if (pipe(cmds->prev_pipe) == -1)
			ft_handle_pipe_error(data, cmds);
		ft_handle_pipes(data, cmds);
	}
	ft_close_hd_in_fork(cmds, NULL);
	return (ft_exit_code(0, GET));
}

/*
TESTS QUI NE MARCHENT PAS 

cat << a <, a | cat << a <, a													// OK 
cat << a << b << c | echo << a << b << c										// OK
<< ok << ok << ok << ah << ls | cat << a << b << c << d | << ok << ah << d		// OK
<< ok << ok << ok << ah << ls | << ok << ah << d								// OK
<< Makefile cat < infile														// OK
	// => Affiche Makefile
<< eof cat < infile																// OK
	// => eof no such file or directory
*/
