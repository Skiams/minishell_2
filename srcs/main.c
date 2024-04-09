/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <eltouma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:18:15 by ahayon            #+#    #+#             */
/*   Updated: 2024/04/10 01:23:31 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	sig_exit;

static bool	ft_parsing(char *str, t_data *data)
{
	if (str)
		add_history(str);
	if (ft_is_only_spacetab(str) == true)
		return (false);
	if (!ft_tokenization(data))
		return (false);
	if (ft_check_syntax(data) != 0)
		return (false);
	//ft_check_expand(data);
	
	return (true);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	char 	**tab;
	int		i;
	
	(void)argc;
	(void)argv;
	i = 0;
	ft_memset(&data, 0, sizeof(t_data));
	// dprintf(2, "oui\n");
	data.env = ft_get_env(&data, env);
	// dprintf(2, "non\n");
	// if (env)
	// 	data.env = ft_get_env(&data, env);
	// else
	// 	data.env = NULL;
	// if (ft_exit_code(0, GET) == 1)
	// 	return (ft_free_data(&data), 1);
	// a rajouter pour le get_env ?
	tab = NULL;
	while (i < 2)
	{
		data.input = readline("minishell: ");
		
		// if (!data.input)
		// 				(ft_putstr_fd("exit\n", 1), exit(1));
		ft_parsing(data.input, &data);
		//print_tokens(data.token_list);
		tab = ft_get_cmds(&data);
		if (!tab)
			break;
		//print_tab(tab);
		// if (ft_parsing(data.input, &data))
			// 	//gogo gadgeto exe;
		//ft_free_data(&data);
		dprintf(2, "exit code : %d\n", ft_exit_code(0, GET));
		i += 1;
	}
	//ft_clean_all(&data);
	ft_garbage(GAR_FREE_ALL, NULL);
	return (ft_exit_code(0, GET));
}
