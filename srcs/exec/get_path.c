/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 22:12:16 by eltouma           #+#    #+#             */
/*   Updated: 2024/05/28 15:08:31 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

static int	ft_lstsize_env(t_env *env)
{
	int	i;
	t_env	*tmp;

	i = 0;
	tmp = env;
	if (!env)
		return (0);
	while (env != NULL)
	{
		env = env->next;
		i += 1;
	}
	env = tmp;
	return (i);
}

int     ft_count_words2(char *str)
{
        size_t  i;
        size_t  j;

        i = 0;
        j = 0;
	while (i < ft_strlen(str))
        {
                if (!ft_is_space(str[i]))
                        j += 1;
                while (!ft_is_space(str[i]) && str[i] != '\0')
                        i += 1;
                while (ft_is_space(str[i]) && str[i] != '\0')
                        i += 1;
        }
        return (j);
}

int     ft_count_size_of_word2(char *str)
{
        int     i;

        i = 0;
	while (!ft_is_space(str[i]) && str[i] != '\0')
                i += 1;
        return (i);
}

char    *ft_fill_tab2(char *str)
{               
        int             i;
        int             size;
        char    *s;
                
        i = 0;
        if (!str)
                return (NULL);
        size = ft_count_size_of_word2(str);
        s = (char *)malloc(sizeof(char) * size + 1);
        if (!s)
                return (NULL);
	 while (str[i] != '\0' && !ft_is_space(str[i]))
        {
                s[i] = str[i];
                i += 1;
        }
        s[i] = '\0';
        return (s);
}        

char    *ft_fill_tab3(char *str)
{               
        int             i;
        int             size;
        char    *s;
                
        i = 0;
        if (!str)
                return (NULL);
        size = ft_count_size_of_word2(str);
        s = (char *)malloc(sizeof(char) * size + 1);
        if (!s)
                return (NULL);
	 while (str[i] != '\0' && str[i] != 58 && !ft_is_space(str[i]))
        {
                s[i] = str[i];
                i += 1;
        }
        s[i] = '\0';
        return (s);
}        

char    **ft_split_exec2(char *str)
{
        int             j;
        char    **tab; 

        j = 0;
        if (!str)
                return (NULL);
        tab = ft_return_tab(str);
        if (!tab)
                return (NULL);
        tab[ft_count_words(str)] = NULL;
        while (*str != '\0')
        {
                if (!ft_is_space(*str) && *str != 58)
                {
                        tab[j] = ft_fill_tab3(str);
                        if (!tab[j++])
                                return (ft_free_tab(tab));
                        while (*str != '\0' && *str != 58
                                && !(ft_is_space(*str)))
                                str += 1;
                }
                else
                        str += 1;
        }
        return (tab);
}


static char	**ft_return_tab_size(int size)
{
	char	**tab;

	tab = (char **)malloc(sizeof(char *) * (size + 1));
	if (!tab)
		return (NULL);
	return (tab);
}

char	**ft_return_mini_env(t_data *data, t_env *env)
{
	dprintf(2, "JE SUIS DANS MINI_ENV\n");
	int     i;
	int	size;
	char	*var;
	char	*val;
	t_env	*tmp;

	tmp = env;
	i = 0;
	size = ft_lstsize_env(env);
	data->mini_env = ft_return_tab_size(size);
	if (!data->mini_env)
		return (NULL);
	data->mini_env[size] = NULL;
	while (env != NULL)
	{
		var = ft_strjoin(env->var, "=");
		val = ft_strjoin(var, env->value);
		if (!ft_strcmp(env->var, "PATH"))
			data->mini_env[i] = ft_fill_tab2(val);
		else
			data->mini_env[i] = ft_fill_tab(val);
		if (!data->mini_env[i])
			return (ft_free_tab(data->mini_env));
		ft_free_ptr(var);
		ft_free_ptr(val);
		i += 1;
		env = env->next;
	}
	env = tmp;
	return (data->mini_env);
}	

static char	*ft_strncmp_exec(t_data *data, char *str, int n)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	ft_return_mini_env(data, data->env);
	if (!data->mini_env)
		return (NULL);
	while (data->mini_env[i])
	{
		j = 0;
		k = 0;
		while (data->mini_env[i][j] == str[k] && k <= n)
		{
			j += 1;
			k += 1;
			if (k == n)
				return (&data->mini_env[i][j]);
		}
		i += 1;
	}
	return (NULL);
}

void	ft_get_path(t_data *data, t_cmds *cmds)
{
	cmds->env_path = ft_strncmp_exec(data, "PATH=", 5);
	if (cmds->env_path)
	{
		cmds->cmd_path = ft_split_exec2(cmds->env_path);
		if (!cmds->cmd_path)
			return ;
	}
	else
		cmds->cmd_path = NULL;
}
