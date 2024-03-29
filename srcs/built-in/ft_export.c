/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skiam <skiam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 13:14:34 by skiam             #+#    #+#             */
/*   Updated: 2024/03/29 16:46:47 by skiam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check_export_case(char *str)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (ft_error_export(str), 0);
		else if (str[i] == '=' && str[i - 1] == '+')
			return (3);
		else if (str[i] == '=')
			return (2);
		else
			return (1);
	}
}
void	ft_error_export(char *str)
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

void	ft_add_var_env(t_data *data, char *str, int code)
{
	if (code == 1)
	{
		
	}
}

int ft_export(t_data *data, char **args)
{
    int i;

    i = 1;
    if (!args[i])
        return (ft_display_export(data));
	while (args[i])
	{
        if (args[1][0] == '-')
        {
			ft_putstr_fd("minishell: export: -", 2);
            write(1, &args[1][1], 1);
            ft_putstr_fd(" invalid option", 2);
            ft_exit_code(2, ADD);
            break ;
        }
		else if (!ft_isalpha(args[i][0]) && args[i][0] != '_')
			ft_error_export(args[i]);
		else if (ft_check_export_case(args[i] == 1))
			ft_add_var_env(data, args[i], 1);
		else if (ft_check_export_case(args[i] == 2))
		else if (ft_check_export_case(args[i] == 3))
		i++;
	}
	return (ft_exit_code(0, GET));
}