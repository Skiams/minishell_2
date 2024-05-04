/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skiam <skiam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:10:40 by ahayon            #+#    #+#             */
/*   Updated: 2024/05/04 21:20:53 by skiam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check_end_quotes(char *str, int i, char c)
{
	i++;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == c)
	{
		i++;
		return (i);
	}
	else
		return (0);
}

bool	ft_check_space_expand(char *str)
{
	// int	i;

	// i = 0;
	// while (str[i] && (str[i] == 32 || str[i] == 9))
	// 	i++;
	// dprintf(2, "index exp i = %d\n", i);
	// while (str[i] && str[i] != 32 && str[i] != 9)
	// 	i++;
	// dprintf(2, "index exp i = %d\n", i);
	// while (str[i] && (str[i] == 32 || str[i] == 9))
	// 	i++;
	// dprintf(2, "index exp i = %d\n", i);
	// if (str[i] != 32 && str[i] != 9)
	// 	return (true);
	// else
	// 	return (false);
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < ft_strlen(str))
	{
		if (!(str[i] >= 9 && str[i] <= 13) && str[i] != 32 && str[i] != 58)
			j += 1;
		while (!(str[i] >= 9 && str[i] <= 13)
			&& str[i] != 32 && str[i] != 58 && str[i] != '\0')
			i += 1;
		while (((str[i] >= 9 && str[i] <= 13) || str[i] == 32 || str[i] == 58)
			&& str[i] != '\0')
			i += 1;
	}
	if (j >= 2)
		return (true);
	else
		return (false);
}
bool	ft_add_exp_token(t_token **token_lst, char *str)
{
	int		i;
	int		start;
	char	*cmd;
	char	*arg;
	t_token	*new_token;
	t_token *rest_token;
	
	cmd = NULL;
	arg = NULL;
	i = 0;
	while (str[i] && (str[i] == 32 || str[i] == 9))
		i++;
	start = i;
	while (str[i] && str[i] != 32 && str[i] != 9)
		i++;
	if (!(cmd = ft_substr(str, start, i - start)))
		return (ft_exit_code(12, ADD), false);
	new_token = ft_lstnew_token(cmd, WORD);
	if (!new_token)
		return (ft_free_ptr(cmd), ft_exit_code(12, ADD), false);
	ft_lstadd_back_token(token_lst, new_token);
	while (str[i] && (str[i] == 32 || str[i] == 9))
		i++;
	start = i;
	while (str[i])
		i++;
	if (!(arg = ft_substr(str, start, i - start)))
		return (ft_exit_code(12, ADD), false);
	dprintf(2, "arg = %s\n", arg);
	rest_token = ft_lstnew_token(arg, WORD);
	if (!rest_token)
		return (ft_free_ptr(cmd), ft_free_ptr(arg), ft_exit_code(12, ADD), false);
	ft_lstadd_back_token(token_lst, rest_token);
	return (ft_free_ptr(str), true);
}
