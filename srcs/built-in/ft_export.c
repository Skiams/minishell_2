/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skiam <skiam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 13:14:34 by skiam             #+#    #+#             */
/*   Updated: 2024/03/27 22:24:29 by skiam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_order_export_env(t_env **export_env)
{
	t_env	*node;
	char	*tmp;

	if (!*export_env)
		return ;
	node = *export_env;
	while (node->next)
	{
		if (strcmp(node->var, node->next->var) > 0)
		{
			tmp = node->next->var;
			node->next->var = node->var;
			node->var = tmp;
			tmp = node->next->value;
			node->next->value = node->value;
			node->value = tmp;
			node = *export_env;
		}
		else
			node = node->next;
	}	
}

int ft_display_export(t_data *data)
{
    t_env   *sorted_env;
    
    sorted_env = data->env;
    ft_order_export_env(&sorted_env);
    while (sorted_env)
    {
        ft_putstr_fd(sorted_env->var, 1);
        if (sorted_env->value != NULL)
        {
            ft_putstr_fd("=", 1);
            ft_putstr_fd(sorted_env->value, 1);
        }
        ft_putstr_fd("\n", 1);
        sorted_env = sorted_env->next;
    }
    return(ft_exit_code(0, ADD));
}

// int ft_export(t_data *data, char **args)
// {
//     int i;

//     i = 1;
//     if (!args[i])
//         return (ft_display_export(data));
// }