/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skiam <skiam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 22:19:04 by eltouma           #+#    #+#             */
/*   Updated: 2024/04/15 13:08:44 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exec_here_doc(t_data *data, t_cmds *cmds)
{
	char	*line;
	char	*delimiter;

	if (!cmds->cmd)
		cmds->here_doc = open("/dev/stdin", O_WRONLY | O_CREAT | O_TRUNC, 0755);
	else
		cmds->here_doc = open(cmds->cmd, O_WRONLY | O_CREAT | O_TRUNC, 0755);
	if (cmds->here_doc == -1)
		ft_handle_infile_error(cmds, data);
	cmds->is_here_doc = 1;
	delimiter = ft_strjoin(cmds->redir->path, "\n");
	while (1)
	{
		ft_putstr_fd("> ", 0);
		line = get_next_line(0);
		if (!ft_strcmp(line, delimiter))
			break ;
		ft_putstr_fd(line, cmds->here_doc);
		free(line);
	}
	free(line);
	free(delimiter);
	if (close(cmds->here_doc) == -1)
		ft_handle_infile_error(cmds, data);
}

void    ft_handle_here_doc(t_data *data, t_cmds *cmds)
{
	cmds->here_doc = open(cmds->cmd, O_RDONLY, 0755);
	if (cmds->here_doc == -1)
		ft_handle_infile_error(cmds, data);
	if (dup2(cmds->here_doc, 0) == -1)
		ft_handle_dup2_error(data, cmds);
	if (close(cmds->here_doc) == -1)
		ft_handle_close_error(cmds);
	cmds->i += 1;
	if (unlink(cmds->cmd) == -1)
	{
		free(cmds->cmd);
		ft_free_tab(cmds->cmd_path);
		ft_clean_all(data);
	}
}
