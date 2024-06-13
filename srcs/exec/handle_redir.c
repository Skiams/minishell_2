/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:14:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/06/13 18:56:18 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_handle_redir(t_data *data, t_cmds *cmds)
{
	t_redir	*tmp;
	int		count;

	tmp = cmds->redir;
	count = 0;
	while (tmp != NULL)
	{
		if (tmp->type == APPEND)
			ft_handle_output_and_append(data, cmds, tmp);
		if (tmp->type == HEREDOC)
			ft_read_here_doc(data, cmds, &count);
		if (tmp->type == RED_IN)
			return (ft_handle_input(data, cmds, tmp));
		if (tmp->type == RED_OUT)
			ft_handle_output_and_append(data, cmds, tmp);
		tmp = tmp->next;
	}
	ft_close_hd_in_fork(data->cmd_list, NULL);
	ft_clear_redirlst(&cmds->redir, &ft_free_ptr);
	return (1);
}
