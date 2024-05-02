/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skiam <skiam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:08:34 by ahayon            #+#    #+#             */
/*   Updated: 2024/05/02 15:55:59 by skiam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char *ft_classic_exp(t_data *data, char *str, size_t *i, int code)
{
	size_t	start;
	char	*env_var;
	char	*env_value;

	(*i)++;
	if (str[*i] == '?')
		return ((*i)++, ft_exp_question_m(data));
	else if (str[* i] == '$')
		return ((*i)++, ft_exp_pid(data));
	start = *i;
	if (code == NO_QUOTES)
	{
		while (str[*i] && str[*i] != '$')
			(*i)++;
	}
	else if (code == QUOTES)
	{
		while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
			(*i)++;
	}
	env_var = ft_substr(str, start, *i - start);
	if (!env_var)
		return (ft_exit_code(12, ADD), NULL);
	env_value = ft_var_is_exp(data, env_var);
	if (env_value)
		return (free(env_var), env_value);
	else
		return (NULL);
}

static char *ft_normal_str(char *str, size_t *i)
{
	size_t	start;
	char	*normal_str;

	start = *i;
	while (str[*i] && str[*i] != '\'' && str[*i] != '"' && str[*i] != '$')
		(*i)++;
	normal_str = ft_substr(str, start, *i - start);
	if (!normal_str)
		return (ft_exit_code(12, ADD), NULL);
	return (normal_str);
}

static char *ft_normal_dq_str(char *str, size_t *i)
{
	size_t	start;
	char	*dq_str;

	start = (*i);
	while (str[*i] && str[*i] != '"' && str[*i] != '$')
		(*i)++;
	dq_str = ft_substr(str, start, *i - start);
	if (!dq_str)
		return (ft_exit_code(12, ADD), NULL);
	return (dq_str);
}

static char	*ft_exp_dquotes(t_data *data, char *str, size_t *i)
{
	char	*dq_str;
	
	dq_str = ft_strdup("\"");
	if (!dq_str)
		return (ft_exit_code(12, ADD), NULL);
	(*i)++;
	while (str[*i] && str[*i] != '"')
	{
		if (str[*i] == '$')
			dq_str = ft_strjoin_exp(dq_str, ft_classic_exp(data, str, i, QUOTES));
		else
			dq_str = ft_strjoin_exp(dq_str, ft_normal_dq_str(str, i));
		if (!dq_str)
			return (ft_exit_code(12, ADD), NULL);
	}
	(*i)++;
	dq_str = ft_strjoin_exp(dq_str, ft_strdup("\""));
	if (!dq_str)
		return (ft_exit_code(12, ADD), NULL);
	return (dq_str);
}

static char	*ft_exp_squotes(char *str, size_t *i)
{
	size_t	start;
	char	*sq_str;
	
	start = (*i);
	(*i)++;
	while (str[*i] != '\'')
		(*i)++;
	(*i)++;
	sq_str = ft_substr(str, start, (*i) - start);
	if (!sq_str)
		return (ft_exit_code(12, ADD), NULL);
	return (sq_str);
}

char	*ft_expand(t_data *data, char *str)
{
	char	*exp_str;
	size_t	i;

	exp_str = ft_strdup("");
	if (!exp_str)
		return (ft_exit_code(12, ADD), NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			exp_str = ft_strjoin_exp(exp_str, ft_exp_squotes(str, &i));
		else if (str[i] == '"')
			exp_str = ft_strjoin_exp(exp_str, ft_exp_dquotes(data, str, &i));
		else if (str[i] == '$')
			exp_str = ft_strjoin_exp(exp_str, ft_classic_exp(data, str, &i, NO_QUOTES));
		else
			exp_str = ft_strjoin_exp(exp_str, ft_normal_str(str, &i));
		if (!exp_str)
			return (ft_exit_code(12, ADD), NULL);
	}
	return (exp_str);
}


// static bool	ft_is_quotes(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '\'' || str[i] == '"')
// 			return (true);
// 		i++;
// 	}
// 	return (false);
// }

// int	ft_check_dollar(char *str)
// {
// 	int	i;
// 	int	dollar_nb;

// 	i = 0;
// 	dollar_nb = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '$')
// 			dollar_nb++;
// 		i++;
// 	}
// 	return (dollar_nb);
// }

// char	*ft_expand(t_data *data, char *str)
// {
// 	char	*exp_str;
// 	char	*tmp;
// 	char	*exp_d;

// 	tmp = NULL;
// 	exp_d = NULL;
// 	if (!ft_is_quotes(str))
// 	{
// 		exp_str = ft_exp_no_quotes(data, str, tmp, exp_d);
// 		if (!exp_str)
// 			return (ft_exit_code(12, ADD), NULL);
// 	}
// 	else
// 		// exp_str = ft_exp_quotes(data, str, tmp, exp_d);
// 		exp_str = NULL;
// 	return (exp_str);
// }

// static char	*ft_classic_expand(t_data *data, char *str, int *i)
// {
// 	return (NULL);
// }

// static char	*ft_exp_quotes(t_data *data, char *str, char *tmp, char *exp_d)
// {
// 	static int	quotes_count = 0;
// 	int			i;
// 	int			check;
	
// 	i = 0;
// 	check = 0;
// 	while(str[i] && str[i] != '$' && str[i] != '\'' && str[i] != '"')
// 		i++;
// 	if (str[i] == '\'' && check <= quotes_count)
// 	{
// 		quotes_count++;
// 		while (str[i] && str[i] != '\'')
// 			i++;
// 	}
// 	else if (str[i] == '"' && check <= quotes_count)
// 	{
// 		quotes_count++;
// 		while (str[i] && str[i] != '"')
// 			i++;
// 	}	
// }

// static char	*ft_exp_no_quotes(t_data *data, char *str, char *tmp, char *exp_d)
// {
// 	char	*tmp_var;
// 	char	*exp_str;
// 	char	*exp_rest;
// 	int		i;
// 	int		start;

// 	ft_init_var_exp(&tmp_var, &exp_rest, &i, &start);
// 	while (str[i] && str[i] != '$')
// 		i++;
// 	exp_str = ft_substr(str, 0, i);
// 	if (!exp_str)
// 		return (ft_exit_code(12, ADD), NULL);
// 	i++;
// 	if (str[i] == '?')
// 		tmp = ft_exp_question_m(data);
// 	else
// 	{
// 		start = i;
// 		while (str[i] && str[i] != '$')
// 			i++;
// 		tmp_var = ft_substr(str, start, i - start);
// 		if (!tmp_var)
// 			return (ft_free_ptr(exp_str), ft_exit_code(12, ADD), NULL);
// 		tmp = ft_var_is_exp(data, tmp_var);
// 	}
// 	if (tmp != NULL)
// 	{
// 		exp_str = ft_strjoin_exp(exp_str, tmp);
// 		if (!exp_str)
// 			return (ft_exit_code(12, ADD), NULL);
// 		if (str[i] && str[i + 1])
// 		{
// 			exp_rest = ft_substr(str, i, (ft_strlen(str) - i));
// 			exp_str = ft_strjoin_exp(exp_str, exp_rest);
// 		}
// 	}
// 	exp_d = ft_strdup(exp_str);
// 	ft_free_ptr(exp_str);
// 	return (ft_free_ptr(str), ft_free_ptr(tmp_var), exp_d);
// }