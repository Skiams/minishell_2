/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_bis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:30:52 by ahayon            #+#    #+#             */
/*   Updated: 2024/06/14 12:18:29 by ahayon           ###   ########.fr       */
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

static char	*ft_exp_pid(t_data *data)
{
	char	*str;
	int		pid;

	(void)data;
	pid = getpid();
	str = ft_itoa(pid);
	if (!str)
	{
		ft_exit_code(300, ADD);
		ft_exit_if_malloc(data);
	}
	return (str);
}

static void	ft_classic_exp_bis(char *str, size_t *i, int code)
{
	if (code == NO_QUOTES)
	{
		while (str[*i] && str[*i] != '$' && str[*i] != '=' && str[*i] != '"'
			&& str[*i] != '/')
			(*i)++;
	}
	else if (code == QUOTES)
	{
		while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
			(*i)++;
	}
}

char	*ft_classic_exp(t_data *data, char *str, size_t *i, int code)
{
	size_t	start;
	char	*env_var;
	char	*env_value;

	(*i)++;
	if (str[*i] == '\0')
		return (ft_strdup_exec(data, "$"));
	if (str[*i] == '?')
		return ((*i)++, ft_exp_question_m(data));
	else if (str[*i] == '$')
		return ((*i)++, ft_exp_pid(data));
	else if (str[*i] == '\'' || str[*i] == '"')
		return (ft_strdup_exec(data, "\0"));
	start = *i;
	ft_classic_exp_bis(str, i, code);
	env_var = ft_substr_exec(data, str, start, *i - start);
	env_value = ft_var_is_exp(data, env_var);
	if (env_value[0] == '\0')
		data->flag_null_exp = 1;
	else
		env_value = ft_remove_space(env_value);
	if (env_value)
		return (ft_free_ptr(env_var), env_value);
	else
		return (NULL);
}

char	*ft_strjoin_exp(char *s1, char *s2)
{
	int		i;
	int		j;
	int		size;
	char	*str;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i += 1;
	}
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = '\0';
	return (ft_free_ptr(s1), ft_free_ptr(s2), str);
}
