/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:08:34 by ahayon            #+#    #+#             */
/*   Updated: 2024/04/22 19:08:07 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*ft_var_is_exp(t_data *data, char *str)
{
	t_env	*tmp;
	char	*dup_value;
	
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
	return (NULL);
}

static char	*ft_exp_no_quotes(t_data *data, char *str)
{
	char	*tmp_var;
	char	*tmp_value;
	char	*exp_str;
	char	*exp_dup;
	char	*mab;
	int		i;
	int		start;

	mab = NULL;
	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	exp_str = ft_substr(str, 0, i);
	if (!exp_str)
		return (ft_exit_code(12, ADD), NULL);
	i++;
	start = i;
	while (str[i] && str[i] != '$')
		i++;
	tmp_var = ft_substr(str, start, i - start);
	if (!tmp_var)
		return (ft_free_ptr(exp_str), ft_exit_code(12, ADD), NULL);
	tmp_value = ft_var_is_exp(data, tmp_var);
	if (tmp_value != NULL)
	{
		exp_str = ft_strjoin(exp_str, tmp_value);
		if (!exp_str)
			return (ft_exit_code(12, ADD), NULL);
		if (str[i] && str[i + 1])
		{
			mab = ft_substr(str, i, (ft_strlen(str) - i));
			exp_str = ft_strjoin(exp_str, mab);
		}
	}
	exp_dup = ft_strdup(exp_str);
	ft_free_ptr(exp_str);
	ft_free_ptr(mab);
	return (ft_free_ptr(str), ft_free_ptr(tmp_var), ft_free_ptr(tmp_value), exp_dup);
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

	if (!ft_is_quotes(str))
	{
		exp_str = ft_exp_no_quotes(data, str);
		if (!exp_str)
			return (ft_exit_code(12, ADD), NULL);
	}
	else
		exp_str = NULL;
	return (exp_str);
}
// static bool ft_replace_var(t_data *data, t_token *token, char *str, int start)
// {
// 	t_env	*tmp;
// 	char	*expanded_value;
// 	int		len;
// 	int		i;
// 	size_t	j;

// 	j = 0;
// 	i = 0;
// 	tmp = data->env;
// 	while (tmp)
// 	{
// 		if (ft_strcmp(str, tmp->var) == 0)
// 		{
// 			len = ft_strlen(token->value) - ft_strlen(str) - 1 + ft_strlen(tmp->value);
// 			expanded_value = malloc(sizeof(char) * len + 1);
// 			if (!expanded_value)
// 				return (ft_exit_code(12, ADD), false);
// 			while (i < start)
// 			{
// 				expanded_value[i] = token->value[i];
// 				i++;
// 			}
// 			while (j < ft_strlen(tmp->value))
// 			{
// 				expanded_value[i] = tmp->value[j];
// 				i++;
// 				j++;
// 			}
// 			start += ft_strlen(str) + 1;
// 			while (i < len)
// 			{
// 				expanded_value[i] = token->value[start];
// 				i++;
// 				start++;
// 			}
// 			free(token->value);
// 			token->value = malloc(sizeof(char) * len + 1);
// 			if (!token->value)
// 				return (ft_exit_code(12, ADD), false);
// 			token->value = expanded_value;
// 			//free (expanded_value);
// 			return (true);
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (true);
// }

// static bool	ft_exp_no_quotes(t_data *data, t_token *token)
// {
// 	int		i;
// 	int		start;
// 	char	*tmp_str;
	
// 	tmp_str = NULL;
// 	i = 0;
// 	start = 0;
// 	while (token->value[i])
// 	{
// 		if (token->value[i] == '$')
// 		{
// 			start = i + 1;
// 			while (token->value[i] && token->value[i] != '$')
// 				i++;
// 			tmp_str = ft_substr(token->value, start, (i - start));
// 			if (!tmp_str)
// 				return (ft_exit_code(12, ADD), false);
// 			if (!ft_replace_var(data, token, tmp_str, start))
// 				return (false);
// 			else
// 				return (true);
// 		}
// 		i++;
// 	}
// 	if (tmp_str)
// 		free(tmp_str);
// 	return (true);
// }



// bool	ft_expand(t_data *data)
// {
// 	t_token	*tmp;
	
// 	tmp = data->token_list;
// 	while (tmp)
// 	{
// 		if (ft_strchr(tmp->value, '$') == 1)
// 		{
// 			// if (ft_is_quotes(tmp->value) && !ft_exp_quotes(data, tmp))
// 			// 	return (false);
// 			if (!ft_is_quotes(tmp->value) && !ft_exp_no_quotes(data, tmp))
// 				return (false);
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (true);
// }

