/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:08:34 by ahayon            #+#    #+#             */
/*   Updated: 2024/04/23 18:56:50 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*ft_exp_question_m(t_data *data)
{
	char	*str;

	(void)data;
	str = ft_itoa(ft_exit_code(0, GET));
	if (!str)
		return (NULL);
	return (str);
}

static char	*ft_var_is_exp(t_data *data, char *str)
{
	t_env	*tmp;
	char	*dup_value;

	dup_value = NULL;
	tmp = data->env;
	while (tmp)
	{
		if (ft_strcmp(str, tmp->var) == 0)
		{
			dup_value = ft_strdup(tmp->value);
			return (dup_value);
		}
		tmp = tmp->next;
	}
	dup_value = malloc(sizeof(char));
	dup_value[0] = '\0';
	return (dup_value);
}

// static char	*ft_exp_quotes(t_data *data, char *str, char *tmp, char *exp_d)
// {
// 	static int	quotes_count = 0;
// 	int			i;
	
// 	i = 0;
// 	while(str[i] && str[i] != '$' && str[i] != '\'' && str[i] != '"')
// 		i++;
// 	if (str[i] == '\'')
// 	{
// 		quotes_count++;
// 		while (str[i] && str[i] != '\'')
// 			i++;
// 	}
// 	else if (str[i] == '"')
// 	{
// 		quotes_count++;
		
// 	}	
// }

static char	*ft_exp_no_quotes(t_data *data, char *str, char *tmp, char *exp_d)
{
	char	*tmp_var;
	char	*exp_str;
	char	*exp_rest;
	int		i;
	int		start;

	ft_init_var_exp(&tmp_var, &exp_rest, &i, &start);
	while (str[i] && str[i] != '$')
		i++;
	exp_str = ft_substr(str, 0, i);
	if (!exp_str)
		return (ft_exit_code(12, ADD), NULL);
	i++;
	if (str[i] == '?')
		tmp = ft_exp_question_m(data);
	else
	{
		start = i;
		while (str[i] && str[i] != '$')
			i++;
		tmp_var = ft_substr(str, start, i - start);
		if (!tmp_var)
			return (ft_free_ptr(exp_str), ft_exit_code(12, ADD), NULL);
		tmp = ft_var_is_exp(data, tmp_var);
	}
	if (tmp != NULL)
	{
		exp_str = ft_strjoin_exp(exp_str, tmp);
		if (!exp_str)
			return (ft_exit_code(12, ADD), NULL);
		if (str[i] && str[i + 1])
		{
			exp_rest = ft_substr(str, i, (ft_strlen(str) - i));
			exp_str = ft_strjoin_exp(exp_str, exp_rest);
		}
	}
	exp_d = ft_strdup(exp_str);
	ft_free_ptr(exp_str);
	return (ft_free_ptr(str), ft_free_ptr(tmp_var), exp_d);
}

static bool	ft_is_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			return (true);
		i++;
	}
	return (false);
}

int	ft_check_dollar(char *str)
{
	int	i;
	int	dollar_nb;

	i = 0;
	dollar_nb = 0;
	while (str[i])
	{
		if (str[i] == '$')
			dollar_nb++;
		i++;
	}
	return (dollar_nb);
}

char	*ft_expand(t_data *data, char *str)
{
	char	*exp_str;
	char	*tmp;
	char	*exp_d;

	tmp = NULL;
	exp_d = NULL;
	if (!ft_is_quotes(str))
	{
		exp_str = ft_exp_no_quotes(data, str, tmp, exp_d);
		if (!exp_str)
			return (ft_exit_code(12, ADD), NULL);
	}
	else
		// exp_str = ft_exp_quotes(data, str, tmp, exp_d);
		exp_str = NULL;
	return (exp_str);
}
