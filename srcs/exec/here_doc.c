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

int	ft_count_here_doc(t_cmds *cmds)
{
	t_redir	*tmp;

	tmp = cmds->redir;
	while (tmp != NULL && tmp->type == 2)
	{
		cmds->here_doc_count += 1;
		tmp = tmp->next;
	}
	return (cmds->here_doc_count);
}

void	ft_exec_here_doc(t_data *data, t_cmds *cmds)
{
	char	*line;
	char	*delimiter;

	if (!cmds->cmd)
	{
//		dprintf(2, "coucou, je n' ai pas de commande\n");
		cmds->here_doc = open("/dev/stdin", O_CREAT | O_TRUNC, 0755);
	}
	else
		cmds->here_doc = open(cmds->redir->path, O_WRONLY | O_CREAT | O_TRUNC, 0755);
	if (cmds->here_doc == -1)
		ft_handle_infile_error(data, cmds);
	cmds->here_doc_count = 1;
	delimiter = ft_strjoin(cmds->redir->path, "\n");
	while (1)
	{
		ft_putstr_fd("> ", 1);
		line = get_next_line(0);
		if (!line)
			break ;
		if (!ft_strcmp(line, delimiter))
			break ;
		ft_putstr_fd(line, cmds->here_doc);
		free(line);
	}
	free(line);
	free(delimiter);
	if (dup2(cmds->here_doc, 0) == -1)
		ft_handle_dup2_error(data, cmds);
	if (close(cmds->here_doc) == -1)
		ft_handle_infile_error(data, cmds);
}

void	ft_handle_here_doc(t_data *data, t_cmds *cmds)
{
//	dprintf(2, "je rentre ici\n");
	cmds->here_doc = open("/dev/stdin", O_RDONLY, 0755);
	if (cmds->here_doc == -1)
	{
//		dprintf(2, "je fail la\n");
		ft_handle_infile_error(data, cmds);
	}
	if (dup2(cmds->here_doc, 0) == -1)
		ft_handle_dup2_error(data, cmds);
	if (close(cmds->here_doc) == -1)
		ft_handle_close_error(data, cmds);

	cmds->i += 1;
	if (unlink(cmds->redir->path) == -1)
		free(cmds->redir->path);
	//dprintf(2, "je vais jusqu'ici\n");
}
