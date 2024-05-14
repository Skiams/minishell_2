/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmds_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skiam <skiam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:02:55 by eltouma           #+#    #+#             */
/*   Updated: 2024/05/01 16:15:41 by skiam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int     ft_lstsize_cmd(t_cmds *cmd)
{
        int     i;

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

int     ft_args_nb(t_cmds *cmds)
{
        int     i;
        t_cmds  *tmp;
        
        i = 0;
        tmp = cmds;
        while (tmp->args[i])
                i++;
        return (i);
}

