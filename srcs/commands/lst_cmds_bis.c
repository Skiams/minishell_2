/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmds_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:02:55 by eltouma           #+#    #+#             */
/*   Updated: 2024/05/17 14:47:08 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_lstsize_cmd(t_cmds *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return (0);
	while (cmd != NULL)
	{
		cmd = cmd->next;
		i += 1;
	}
	return (i);
}

int	ft_args_nb(t_cmds *cmds)
{
	int		i;
	t_cmds	*tmp;

	i = 0;
	tmp = cmds;
	while (tmp->args[i])
		i++;
	return (i);
}
