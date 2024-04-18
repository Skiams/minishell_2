/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:18:15 by ahayon            #+#    #+#             */
/*   Updated: 2024/04/18 20:55:30 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/pipex.h"

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
	if (!ft_get_cmds(data, &data->token_list))
		return (false);
	return (true);
}

int	main(int argc, char **argv, char **env)
{
	int		i;
	t_data	data;

	(void)argv;
	i = 0;
	g_sig_exit = 0;
	if (argc != 1)
		ft_print_wrong_param();
	ft_memset(&data, 0, sizeof(t_data));
	if (env)
		data.env = ft_get_env(&data, env);
	else
		data.env = NULL;
	if (ft_exit_code(0, GET) == 1)
		return (ft_free_data(&data), 1);
	// a rajouter pour le get_env ?
	while (1)
	{
		ft_handle_signal();
		data.input = readline("minishell$ ");
		if (!data.input)
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		//print_env(data.env);
		ft_parsing(data.input, &data);
		ft_exec(&data, data.cmd_list, argc, argv, env);
		print_tokens(data.token_list);
		print_cmds(data.cmd_list);
		//dprintf(2, "exit code : %d\n", ft_exit_code(0, GET));
		ft_free_data(&data);
	}
	ft_clean_all(&data);
	return (ft_exit_code(0, GET));
}
