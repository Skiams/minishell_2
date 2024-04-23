/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 13:14:34 by skiam             #+#    #+#             */
/*   Updated: 2024/04/23 18:16:24 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_add_value_only(t_data *data, char *var, char *value, int code)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (ft_strcmp(var, tmp->var) == 0 && code == 2)
			tmp->value = value;
		//demander comment faire ca si il faut free ou pas
		else if ((ft_strcmp(var, tmp->var) == 0 && code == 3))
		{
			//demander comment faire ca si il faut free ou pas
		}
		else
			tmp = tmp->next;
	}
	return (true);
}

bool	ft_add_var_and_value(t_data *data, char *str, int code)
{
	char	*var;
	char	*value;
	int		i;
	t_env	*newel;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	var = ft_substr(str, 0, i);
	value = ft_substr(str, i + 1, ft_strlen(str) - i + 1);
	if (!var || !value)
		return (false);
	if (code == 2)
	{
		if (!ft_var_is_in_env(data, var))
		{
			newel = ft_lstnew_env(var, value);
			if (!newel)
				return (false);
			ft_lstadd_back_env(&data->env, newel);
		}
		else if (!ft_add_value_only(data, var, value, 2))
			return (false);
	}
	else if (code == 3)
	{
		if (!ft_var_is_in_env(data, var))
		{
			newel = ft_lstnew_env(var, value);
			if (!newel)
				return (false);
			ft_lstadd_back_env(&data->env, newel);
		}
		else if (!ft_add_value_only(data, var, value, 3))
			return (false);
	}
	return (true);
}

static bool	ft_add_var_env(t_data *data, char *str, int code)
{
	t_env	*newel;

	if (code == 1 && !ft_var_is_in_env(data, str))
	{
		newel = ft_lstnew_env(str, NULL);
		if (!newel)
			return (false);
		ft_lstadd_back_env(&data->env, newel);
	}
	//possible de faire else if (code == 2 && !ft_add_var_value) -> return false?
	else if (code == 2)
	{
		if (!ft_add_var_and_value(data, str, 2))
			return (false);
	}
	else if (code == 3)
	{
		if (!ft_add_var_and_value(data, str, 3))
			return (false);
	}
	return (true);
}

//demander comment les retours d'erreur peuvent etre geres en cas de fail de  malloc
int	ft_export(t_data *data, char **args)
{
	int	i;
	int	code;

	code = 0;
	i = 1;
	if (!args[i])
		return (ft_display_export(data));
	else
	{
		while (args[i])
		{
			code = ft_check_export_case(args[i]);
			if (args[1][0] == '-')
			{
				ft_putstr_fd("minishell: export: -", 2);
				write(1, &args[1][1], 1);
				ft_putstr_fd(" invalid option", 2);
				ft_exit_code(2, ADD);
				break ;
			}
			else if (!ft_isalpha(args[i][0]) && args[i][0] != '_' && code != 0)
				ft_error_export(args[i]);
			//	else if (code == 0)
			//		ft_exit_code(1, ADD);
			// normalement gere dans error export
			else if (code >= 1 && code <= 3)
			{
				if (!ft_add_var_env(data, args[i], code))
					return (ft_exit_code(1, ADD));
				//exit direct avec autre signe d'erreur pour quitter direct ?
			}
			i++;
		}
	}
	return (ft_exit_code(0, GET));
}
