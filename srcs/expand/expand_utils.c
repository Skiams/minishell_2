/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skiam <skiam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:27:39 by ahayon            #+#    #+#             */
/*   Updated: 2024/05/03 14:55:32 by skiam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int		ft_count_quotes(char *str)
{
	int		i;
	int		quote_nb;
	char	c;

	quote_nb = 0;
	i = 0;
	c = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			c = str[i];
			i++;
			while (str[i] != c)
				i++;
			if (str[i] == c)
			quote_nb += 2;
		}
		i++;
	}
	return (quote_nb);
}

bool	ft_is_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			return (true);
	}
	return (false);
}

char	*ft_remove_quotes(char *str)
{
	int		i;
	int		j;
	int		quote_nb;
	char	*new_str;
	char	c;

	i = 0;
	j = 0;
	quote_nb = ft_count_quotes(str);
	new_str = malloc(sizeof(char) * (ft_strlen(str) - quote_nb) + 1);
	if (!new_str)
		return (ft_exit_code(12, ADD), NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			c = str[i];
			i++;
			while (str[i] != c)
				new_str[j++] = str[i++];
			if (str[i] == c)
				i++;
		}
		else
			new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	return (free(str), new_str);
}

void	ft_init_var_exp(char **tmp_var, char **exp_rest, int *i, int *start)
{
	*tmp_var = NULL;
	*exp_rest = NULL;
	*i = 0;
	*start = 0;
}

char	*ft_exp_question_m(t_data *data)
{
	char	*str;

	(void)data;
	str = ft_itoa(ft_exit_code(0, GET));
	if (!str)
		return (NULL);
	return (str);
}

char	*ft_exp_pid(t_data *data)
{
	char	*str;
	int		pid;

	(void)data;
	pid = getpid();
	str = ft_itoa(pid);
	if (!str)
		return (NULL);
	return (str);
}

char	*ft_var_is_exp(t_data *data, char *str)
{
	t_env	*tmp;
	char	*dup_value;

	dup_value = NULL;
	tmp = data->env;
	while (tmp)
	{
		if (ft_strcmp(str, tmp->var) == 0 && tmp->value)
		{
			dup_value = ft_strdup(tmp->value);
			if (!dup_value)
				return (ft_exit_code(12, ADD), NULL);
			return (dup_value);
		}
		tmp = tmp->next;
	}
	dup_value = malloc(sizeof(char));
	if (!dup_value)
		return (ft_exit_code(12, ADD), NULL);
	dup_value[0] = '\0';
	return (dup_value);
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
