/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skiam <skiam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:08:34 by ahayon            #+#    #+#             */
/*   Updated: 2024/05/06 14:30:16 by skiam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char *ft_classic_exp(t_data *data, char *str, size_t *i, int code)
{
	size_t	start;
	char	*env_var;
	char	*env_value;

	(*i)++;
	if (str[*i] == '\0')
		return ("$");
	if (str[*i] == '?')
		return ((*i)++, ft_exp_question_m(data));
	else if (str[* i] == '$')
		return ((*i)++, ft_exp_pid(data));
	start = *i;
	if (code == NO_QUOTES)
	{
		//ligne ajoutee pour le cas d'export une variable apres un expand
		while (str[*i] && str[*i] != '$' && str[*i] != '=')
			(*i)++;
	}
	else if (code == QUOTES)
	{
		while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
			(*i)++;
	}
	if (!(env_var = ft_substr(str, start, *i - start)))
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

	if (!(exp_str = ft_strdup("")))
		return (ft_exit_code(12, ADD), NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			exp_str = ft_strjoin_exp(exp_str, ft_exp_squotes(str, &i));
		else if (str[i] == '"')
			exp_str = ft_strjoin_exp(exp_str, ft_exp_dquotes(data, str, &i));
		else if (str[i] == '$')
		{
			dprintf(2, "on rentre dans le $ de l'expand sans double quote normalement\n");
			exp_str = ft_strjoin_exp(exp_str, ft_classic_exp(data, str, &i, NO_QUOTES));
			ft_expand_code(1, ADD);
		}
		else
			exp_str = ft_strjoin_exp(exp_str, ft_normal_str(str, &i));
		if (!exp_str)
			return (ft_exit_code(12, ADD), NULL);
	}
	return (exp_str);
}
