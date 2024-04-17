/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:47:17 by ahayon            #+#    #+#             */
/*   Updated: 2024/04/17 19:04:27 by ahayon           ###   ########.fr       */
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
		ft_putstr_fd("minishell: exit: too many arguments", 2);
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
		|| (sign == -1 && res < LLONG_MIN - 1))
			return (-1);
		i++;
	}
	return ((res * sign) % 256);
}

void	ft_exit(t_data *data, t_cmds *cmd)
{
	int	code;

	code = 0;
	if (!cmd->next && !cmd->prev)
		ft_pustr_fd("exit\n", 1);
	if (cmd->prev || cmd->next)
		return ;
	if (cmd->args[1] && !ft_is_number(cmd->args[1]))
	{
		ft_exit_errors(1, cmd->args[1]);
		if (cmd->prev || cmd->next)
			return ;
	}
	else if (cmd->args[1] && ft_get_status(cmd->args[1]) == -1)
	{
		ft_exit_errors(1, cmd->args[1]);
		if (cmd->prev || cmd->next)
			return ;
	}
	else if (cmd->args[2])
		return (ft_exit_errors(2, cmd->args[1]));
	ft_clean_all(data);
	exit (ft_exit_code(0, GET));
}


	// if (cmd->args[1] && !ft_isnumber(cmd->args[1]))
	// {
	// 	if (!cmd->next && !cmd->prev)
	// 		ft_putstr_fd("exit\n", 2);
	// 	ft_putstr_fd("minishell: exit: ", 2);
	// 	ft_putstr_fd(cmd->args[1], 2);
	// 	ft_putstr_fd(": numeric argument required\n", 2);
	// 	if (cmd->next || cmd->prev)
	// 	{
	// 		if (!cmd->next)
	// 			ft_exit_code(2, ADD);
	// 		return ;
	// 	} 
	// }
	// if ((!cmd->next && !cmd->prev)|| (!cmd->next && cmd->prev
	// && !cmd->args[2]))
	// {
	// 	ft_putstr_fd("exit\n", 1);
	// 	if (cmd->args[1] && !ft_isnumber(cmd->args[1]))
	// 	{
	// 		ft_putstr_fd("minishell: exit: ", 2);
	// 		ft_putstr_fd(cmd->args[1], 2);
	// 		ft_putstr_fd(": numeric argument required\n", 2);
	// 		ft_exit_code(2, ADD);
	// 	}
	// 	else if (cmd->args[1] && ft_isnumber(cmd->args))
	// }
	// else if (cmd->args[2])
	// {
	// 	ft_putstr_fd("minishell: exit: too many arguments", 2);
		
	// }
