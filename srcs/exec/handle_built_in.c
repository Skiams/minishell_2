/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_built_in.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:28:03 by eltouma           #+#    #+#             */
/*   Updated: 2024/04/16 19:05:04 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exec_built_in(t_data *data)
{
	if (!ft_strcmp(data->cmd_list->cmd, "echo")) 
		ft_echo(data->cmd_list->args);
	if (!ft_strcmp(data->cmd_list->cmd, "pwd")) 
		ft_pwd(data);
}

int	ft_is_a_built_in(char *str)
{
	if (!str)
		return (0);
	if (!ft_strcmp(str, "echo")) 
		return (1);
	if (!ft_strcmp(str, "pwd")) 
		return (1);
	return (0);
}
