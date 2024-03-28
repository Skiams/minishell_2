/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skiam <skiam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 13:14:34 by skiam             #+#    #+#             */
/*   Updated: 2024/03/28 20:25:03 by skiam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_error_export(char *str)
{
	int	i;

	i = 0;
	ft_putstr_fd("minishell: export: '", 2);
	while (str[i++])
		write(2, &str[i], 1);
	ft_putstr_fd("': not a valid identifier\n", 2);
	ft_exit_code(1, ADD);
}

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

int ft_export(t_data *data, char **args)
{
    int i;
	int	k;

	k = 0;
    i = 1;
    if (!args[i])
        return (ft_display_export(data));
	while (args[i])
	{
        if (args[1][0] == '-')
        {
			ft_putstr_fd("minishell: unset: -", 1);
            write(1, &args[1][1], 1);
            ft_putstr_fd(" invalid option", 1);
            ft_exit_code(2, ADD);
            break ;
        }
		else if (!ft_isalpha(args[i][0]) && args[i][0] != '_')
			ft_error_export(args[i]);
		else if (ft_strchr(args[i], '=') == NULL)
		{
			while (args[i][k])
			{
				if (!ft_isalnum && args[i][k] != '_')
					ft_error_export(args[i]);
			}
		}
		i++;
	}
}