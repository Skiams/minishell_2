/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <eltouma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:34:32 by ahayon            #+#    #+#             */
/*   Updated: 2024/04/10 13:10:35 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ft_get_cmds(t_data *data)
{
	char	**tab;
	t_token	*tmp;
	int		i;
	int		j;
	
	tmp = data->token_list;
	i = 1;
	j = 0;
	while (tmp)
	{
		if (tmp->type == PIPE)
			i++;
		tmp = tmp->next;
	}
	// tab = (char **)malloc(sizeof(char *) * (i + 1));
	tab = ft_garbage(ADD, (char **)malloc(sizeof(char *) * (i + 1)));
	if (!tab)
		return (ft_exit_code(12, ADD), NULL);
	tmp = data->token_list;
	while (j < i && tmp)
	{
		// tab[j] = ft_substr(tmp->value, 0, ft_strlen(tmp->value));
		tab[j] = ft_garbage(ADD, ft_substr(tmp->value, 0, ft_strlen(tmp->value)));
		if (!tab[j])
			return (ft_exit_code(12, ADD), NULL);
		while (tmp->next && tmp->type != PIPE && tmp->next->type != PIPE)
		{
			// tab[j] = ft_strjoin_c(tab[j], tmp->next->value, 32);
			tab[j] = ft_garbage(ADD, ft_strjoin_c(tab[j], tmp->next->value, 32));
			if (!tab[j])
				return (ft_exit_code(12, ADD), NULL);
			tmp = tmp->next;
		}
		if (tmp->next != NULL && tmp->next->type == PIPE)
			tmp = tmp->next->next;
		else
			tmp = tmp->next;
		j++;
	}
	// int x = 0;
	// while (tab[x])
	// {
	// 	dprintf(1, "tab[%d] = %s\n", x, tab[x]);
	// 	x += 1;
	// }
	// dprintf(1, "\n");
	return (tab);
}
