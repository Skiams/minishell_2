/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:09:05 by eltouma           #+#    #+#             */
/*   Updated: 2024/05/28 14:13:14 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_clean_exit(t_data *data, t_cmds *cmds)
{
	ft_dup2_and_close_stdin_stdout(data, cmds);
	ft_free_tab(cmds->cmd_path);
	ft_free_tab(data->mini_env);
	ft_clean_all(data);
}
