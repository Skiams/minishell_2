/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:18:15 by ahayon            #+#    #+#             */
/*   Updated: 2024/03/05 14:35:45 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_first_check(t_data *data)
{
	int		i;
	int		token_tp;
	char	*str;

	token_tp = 0;
	i = 0;
	// if (ft_is_only_space(str) == true)
	// 	return un truc d'erreur t'sais;	
	str = ft_del_edge_spaces(data->input);
	// if (!str)
	// 	return un truc d'erreur t'sais;
	while (str[i] != '\0')
	{
		if (!ft_is_whitespace(str, i) && str[i])
		{
			token_tp = ft_define_token_type(str, i);
			i = ft_add_token(data, str, token_tp, i);
		}
		else
			i++;
	}
}

static void	ft_parsing(char *str, t_data *data)
{
	if (str)
		add_history(str);
	ft_first_check(data);
	print_tokens(data->token_list);
}

int	main(int argc, char **argv)
{
	t_data	data;

	(void)argc;
	(void)argv;
	ft_printf("Coucou Antoine, c'etait une blague !\n");
	ft_memset(&data, 0, sizeof(t_data));
	while (1)
	{
		data.input = readline("entre un truc batard : ");
		ft_parsing(data.input, &data);
	}
	return (0);
}
