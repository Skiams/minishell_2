/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skiam <skiam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:58:07 by skiam             #+#    #+#             */
/*   Updated: 2024/03/27 22:25:52 by skiam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_remove_var(t_env *env, char *var_name)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->var, var_name) == 0)
		{
			if (tmp->prev != NULL)
				tmp->prev->next = tmp->next;
			if (tmp->next != NULL)
				tmp->next->prev = tmp->prev;
			free(tmp->value);
			free(tmp->var);
			free(tmp);
			break ;
		}
		tmp = tmp->next;
	}
}

int	ft_unset(t_data *data, char **args)
{
	int	i;

	if (!args[1])
		return (0);
	i = 1;
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
		else
			ft_remove_var(data->env, args[i]);
		ft_exit_code(0, ADD);
		i++;
	}
	return (ft_exit_code(0, GET));
}