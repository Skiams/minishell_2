/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <eltouma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:14:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/04/26 14:42:47 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	ft_handle_redir(t_data *data, t_cmds *cmds)
{
	if (cmds->redir->type == 3)
	{
//		ft_putstr_fd("Je suis apres le fork(), numero 3\n", 1);
		cmds->infile = open(cmds->redir->path, O_RDONLY, 0755);
		if (cmds->infile == -1)
			ft_handle_infile_error(cmds->redir->path, cmds, data);
		if (dup2(cmds->infile, 0) == -1)
			ft_handle_dup2_error(cmds);
		if (close(cmds->infile) == -1)
			ft_handle_close_error(cmds);
	}
	if (cmds->redir->type == 4)
	{	
//		ft_putstr_fd("Je suis apres le fork(), numero 4\n", 1);
		cmds->outfile = open(cmds->redir->path, O_WRONLY | O_CREAT | O_TRUNC, 0755);
		if (cmds->outfile == -1)
			ft_handle_outfile_error(cmds->redir->path, cmds, data);
		if (dup2(cmds->outfile, 1) == -1)
			ft_handle_dup2_error(cmds);
		if (close(cmds->outfile) == -1)
			ft_handle_close_error(cmds);
	}

}
