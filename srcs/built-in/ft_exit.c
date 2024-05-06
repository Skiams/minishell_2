/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skiam <skiam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:47:17 by ahayon            #+#    #+#             */
/*   Updated: 2024/05/06 15:55:56 by skiam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_exit_errors(int code, char *str)
{
	if (code == 1)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		ft_exit_code(2, ADD);
	}
	else if (code == 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		ft_exit_code(1, ADD);
	}
}

static bool	ft_is_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

static int	ft_get_status(char *nb)
{
	int					i;
	int					sign;
	unsigned long long	res;

	i = 0;
	res = 0;
	sign = 1;
	while (nb[i] && (nb[i] == 32 || nb[i] == 9))
		i++;
	if (nb[i] == '+' || nb[i] == '-')
	{
		if (nb[i] == '-')
			sign = -1;
		i++;
	}
	while (nb[i])
	{
		res = (res * 10) + (nb[i] - '0');
		if ((sign == 1 && res > LLONG_MAX)
		|| (sign == -1 && res - 1 > LLONG_MAX))
			return (-1);
		i++;
	}
	return ((res * sign) % 256);
}

void	ft_exit(t_data *data, t_cmds *cmd)
{
	if (!cmd->next && !cmd->prev)
		ft_putstr_fd("exit\n", 1);
	if (cmd->prev || cmd->next)
		return ;
	if (cmd->args[1] && !ft_is_number(cmd->args[1]))
	{
		ft_exit_errors(1, cmd->args[1]);
		if (cmd->prev || cmd->next)
			return ;
	}
	else if (cmd->args[1] && ft_is_number(cmd->args[1]))
	{
		if (ft_get_status(cmd->args[1]) == -1)
			ft_exit_errors(1, cmd->args[1]);
		else
			(ft_exit_code(ft_get_status(cmd->args[1]), ADD));
		if (cmd->prev || cmd->next)
			return ;
	}
	else if (cmd->args && cmd->args[1] && cmd->args[2])
		return (ft_exit_errors(2, cmd->args[1]));
	ft_dup2_and_close_stdin_stdout(data, cmd);
	ft_free_tab(cmd->cmd_path);
	ft_clean_all(data);
	exit (ft_exit_code(0, GET));
}
