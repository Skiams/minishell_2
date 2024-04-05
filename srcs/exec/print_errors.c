/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skiam <skiam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 19:31:34 by eltouma           #+#    #+#             */
/*   Updated: 2024/04/05 19:39:08 by skiam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_putstr_fd(char *str, int fd)
{
	if (!str)
		return ;
	write(fd, str, ft_strlen(str));
}

void	ft_print_header(void)
{
	ft_printf(2, "\n\e[2m ####################################\e[0m");
	ft_printf(2, "\e[2m####################################\n\n\e[0m");
}

void	ft_print_footer(void)
{
	ft_print_header();
	exit(EXIT_FAILURE);
}

void	ft_print_missing_param(void)
{
	ft_print_header();
	ft_printf(2, "\033[%dm\e[1m%s\e\033[0m", 31, WARNING);
	ft_printf(2, " It seems something went wrong.\n");
	ft_printf(2, " You must enter at least 4 parameters (5 if here_doc).");
	ft_printf(2, " See the examples below:\n");
	ft_printf(2, " \tWithout here_doc:\n");
	ft_printf(2, "\t\033[%dm\e[1m%s\e\033[0m", 32, ARROW);
	ft_printf(2, " \033[%dm./pipex_bonus\033[0m infile");
	ft_printf(2, " cmd1 cmd2 cmd3 ... outfile\n", 33);
	ft_printf(2, " \tWith here_doc:\n");
	ft_printf(2, "\t\033[%dm\e[1m%s\e\033[0m", 32, ARROW);
	ft_printf(2, " \033[%dm./pipex_bonus\033[0m here_doc delimiter");
	ft_printf(2, " cmd1 cmd2 cmd3 ... outfile\n", 33);
	ft_print_footer();
}
