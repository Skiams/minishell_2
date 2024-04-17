/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 20:28:40 by eltouma           #+#    #+#             */
/*   Updated: 2024/04/17 12:58:08 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(t_cmds *cmds)
{
	char	*working_dir;

	(void)cmds;
	working_dir = getcwd(NULL, 0);
	if (!working_dir)
	{
		perror(working_dir);
		exit(1);
	}
	ft_putstr_fd(working_dir, 1);
	ft_putstr_fd("\n", 1);
	free(working_dir);
	working_dir = NULL;
	return (0);
}
