/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:18:15 by ahayon            #+#    #+#             */
/*   Updated: 2024/06/15 17:07:47 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			g_sig_exit;

static bool	ft_add_shlvl(t_data *data, char *value)
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
				return (ft_exit_code(300, ADD), false);
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
		return (ft_exit_code(300, ADD), NULL);
	if (!ft_lstinit_env(&data->env, "PWD", pwd))
		return (ft_exit_code(300, ADD), NULL);
	if (!ft_lstinit_env(&data->env, "_", "/usr/bin/env"))
		return (ft_exit_code(300, ADD), NULL);
	return (data->env);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	int		fd;
	int		i;

	(void)argv;
	i = 0;
	g_sig_exit = 0;
	if (argc != 1)
		ft_print_wrong_param();
	ft_memset(&data, 0, sizeof(t_data));
	while (i < 1024)
	{
		data.pidlist[i] = -1;
		i += 1;
	}
	if (env && env[0])
	{
		data.env = ft_get_env(&data, env);
		ft_increase_shlvl(&data);
	}
	else
		data.env = ft_no_env(&data);
	if (isatty(STDIN_FILENO) == 0)
	{
		ft_putstr_fd("Non-interactive mode blocked\n", 2);
		ft_clean_all(&data);
		return (ft_exit_code(0, GET));
	}
	if (isatty(0) == 1)
	{
		fd = open("/dev/stdin", O_RDWR);
		(dup2(fd, STDOUT_FILENO), close(fd));
	}
	if (ft_exit_code(0, GET) == 300)
		return (ft_free_data(&data), 255);
	while (1)
	{
		ft_handle_signal(1);
		data.input = readline("1️⃣   minishell$ ");
		if (!data.input)
			return (ft_clean_all(&data), ft_putstr_fd("exit\n", 1),
				ft_exit_code(0, GET));
		if (ft_parsing(data.input, &data))
			ft_exec(&data, data.cmd_list);
		// J'avais mis ce waitpid en commentaire, et je l'avais mis dans exec
		ft_waitpid(&data);
		if (ft_exit_code(0, GET) == 300)
			break ;
		ft_free_data(&data);
	}
	ft_clean_all(&data);
	if (ft_exit_code(0, GET) == 300)
		ft_exit_code(255, ADD);
	return (ft_exit_code(0, GET));
}
