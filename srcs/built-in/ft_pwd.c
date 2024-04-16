/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 20:28:40 by eltouma           #+#    #+#             */
/*   Updated: 2024/04/16 17:17:28 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(t_data *data)
{
	char	*working_dir;

	(void)data;
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
