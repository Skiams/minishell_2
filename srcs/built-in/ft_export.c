/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skiam <skiam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 13:14:34 by skiam             #+#    #+#             */
/*   Updated: 2024/05/06 15:55:26 by skiam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_add_value_only(t_data *data, char *var, char *value, int code)
{
	t_env	*tmp;
	char	*tmp_value;

	tmp_value = NULL;
	tmp = data->env;
	while (tmp)
	{
		if (ft_strcmp(var, tmp->var) == 0 && code == 2)
		{
			ft_free_ptr(var);
			ft_free_ptr(tmp->value);
			tmp->value = ft_strdup(value);
			if (!tmp->value)
				return (ft_exit_code(12, ADD), false);
			ft_free_ptr(value);
			if (tmp->next)
				tmp = tmp->next;
			return (true);
		}
		else if ((ft_strcmp(var, tmp->var) == 0 && code == 3))
		{
			ft_free_ptr(var);
			tmp_value = ft_strjoin_exp(tmp->value, value);
			if (!tmp_value)
				return (ft_exit_code(12, ADD), false);
			tmp->value = ft_strdup(tmp_value);
			if (!tmp_value)
				return (ft_exit_code(12, ADD), false);
			ft_free_ptr(tmp_value);
			if (tmp->next)
				tmp = tmp->next;
			return (true);
		}
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

	value = NULL;
	i = 0;
	while (str[i] && str[i] != '=' && str[i] != '+')
		i++;
	var = ft_substr(str, 0, i);
	if (!var)
		return (ft_exit_code(12, ADD), false);
	if (code == 2)
		value = ft_substr(str, i + 1, ft_strlen(str) - i + 1);
	else if (code == 3)
		value = ft_substr(str, i + 2, ft_strlen(str) - i);
	if (!value)
		return (ft_free_ptr(var), ft_exit_code(12, ADD), false);
	if (code == 2)
	{
		if (!ft_var_is_in_env(data, var))
		{
			newel = ft_lstnew_env(var, value);
			if (!newel)
				return (ft_exit_code(12, ADD), false);
			ft_lstadd_back_env(&data->env, newel);
		}
		else if (!ft_add_value_only(data, var, value, 2))
			return (ft_exit_code(12, ADD), false);
	}
	else if (code == 3)
	{
		if (!ft_var_is_in_env(data, var))
		{
			newel = ft_lstnew_env(var, value);
			if (!newel)
				return (ft_exit_code(12, ADD), false);
			ft_lstadd_back_env(&data->env, newel);
		}
		else if (!ft_add_value_only(data, var, value, 3))
			return (ft_exit_code(12, ADD), false);
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

int	ft_export(t_data *data, char **args)
{
	int		i;
	int		code;
	char	*dup_arg;

	code = 0;
	i = 1;
	if (!args[i])
		return (ft_display_export(data));
	else
	{
		while (args[i])
		{
			dup_arg = ft_strdup(args[i]);
			if (!dup_arg)
				return (ft_exit_code(12, ADD));
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
			else if (code >= 1 && code <= 3)
			{
				if (!ft_add_var_env(data, dup_arg, code))
					return (ft_exit_code(12, ADD));
			}
			i++;
		}
	}
	if (code == 2 || code == 3)
		ft_free_ptr(dup_arg);
	return (ft_exit_code(0, GET));
}
