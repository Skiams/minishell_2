/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skiam <skiam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:18:15 by ahayon            #+#    #+#             */
/*   Updated: 2024/04/11 16:41:51 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_sig_exit;

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
	int		i;
	t_data	data;
	//	char 	**tab;

	(void)argc;
	(void)argv;
	i = 0;
	ft_memset(&data, 0, sizeof(t_data));
	//data.env = ft_get_env(&data, env);
	if (env)
		data.env = ft_get_env(&data, env);
	else
		data.env = NULL;
	// if (ft_exit_code(0, GET) == 1)
	// 	return (ft_free_data(&data), 1);
	// a rajouter pour le get_env ?
	//	tab = NULL;
	while (i < 3)
	{
		data.input = readline("minishell: ");
		// if (!data.input)
		// 				(ft_putstr_fd("exit\n", 1), exit(1));
		ft_parsing(data.input, &data);
		//tab = ft_get_cmds(&data);
		//	if (!tab)
		//		break ;
		//dprintf(2, "exit code : %d\n", ft_exit_code(0, GET));
		ft_free_data(&data);
		i += 1;
	}
	ft_clean_all(&data);
	return (ft_exit_code(0, GET));
}
