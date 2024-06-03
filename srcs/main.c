/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:18:15 by ahayon            #+#    #+#             */
/*   Updated: 2024/05/31 18:40:00 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

int			g_sig_exit;


static bool ft_add_shlvl(t_data *data, char *value)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (ft_strcmp(tmp->var, "SHLVL") == 0)
		{
			ft_free_ptr(tmp->value);
			tmp->value = ft_strdup(value);
			ft_free_ptr(value);
			if (!tmp->value)
				return (ft_exit_code(12, ADD), false);
		}
		tmp = tmp->next;
	}
	return (true);
}

static bool	ft_increase_shlvl(t_data *data)
{
	char	*shlvl;
	int		count;

	if (ft_var_is_in_env(data, "SHLVL"))
	{
		shlvl = ft_var_is_exp(data, "SHLVL");
		count = ft_atoi(shlvl);
		count++;
		ft_free_ptr(shlvl);
		if (!ft_add_shlvl(data, ft_itoa(count)))
			return (false);
	}
	return (true);
}

static bool	ft_parsing(char *str, t_data *data)
{
	if (str)
		add_history(str);
	if (ft_is_only_spacetab(str))
		return (false);
	if (!ft_tokenization(data))
		return (false);
	if (ft_check_syntax(data) != 0)
		return (false);
	if (!ft_get_cmds(data, &data->token_list))
		return (false);
	return (true);
}

static t_env	*ft_no_env(t_data *data)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!ft_lstinit_env(&data->env, "SHLVL", "2"))
		return (ft_exit_code(12, ADD), NULL);
	if (!ft_lstinit_env(&data->env, "PWD", pwd))
		return (ft_exit_code(12, ADD), NULL);
	if (!ft_lstinit_env(&data->env, "_", "/usr/bin/env"))
		return (ft_exit_code(12, ADD), NULL);
	return (data->env);
}

static void	ft_non_interactive(t_data *data, char **env)
{
	(void)env;
	data->input = get_next_line(STDIN_FILENO);
	if (!data->input)
	{
		ft_clean_all(data);
		ft_putstr_fd("exit\n", 1);
		ft_exit_code(0, GET);
	}
	while (data->input)
	{
		if (ft_parsing(data->input, data))
			ft_exec(data, data->cmd_list);
		ft_free_data(data);
		data->input = get_next_line(STDIN_FILENO);
	}
	ft_clean_all(data);
	exit(ft_exit_code(0, GET));
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	(void)argv;
	g_sig_exit = 0;
	if (argc != 1)
		ft_print_wrong_param();	
	ft_memset(&data, 0, sizeof(t_data));
	if (env && env[0])
	{
		data.env = ft_get_env(&data, env);
		ft_increase_shlvl(&data);
	}
	else
		data.env = ft_no_env(&data);
	if (ft_exit_code(0, GET) == 12)
		return (ft_free_data(&data), 12);
	if (isatty(STDIN_FILENO) == 0)
		ft_non_interactive(&data, env);
// A MODIFIER, PASSER DATA.ENV
//		ft_non_interactive(&data, data.env);
	while (1)
	{
		if (ft_strcmp(ft_var_is_exp(&data, "SHLVL"), "2") == 0)
			ft_handle_signal(1, 1);
		else
			ft_handle_signal(2, 1);
		data.input = readline("1️⃣   minishell$ ");
		if (!data.input)
			return(ft_clean_all(&data), ft_putstr_fd("exit\n", 1),
			ft_exit_code(0, GET));
		if (ft_parsing(data.input, &data))
			ft_exec(&data, data.cmd_list);
		else if (ft_exit_code(0, GET) == 12)
			break ;
		ft_free_data(&data);
	}
	ft_clean_all(&data);
	return (ft_exit_code(0, GET));
}
