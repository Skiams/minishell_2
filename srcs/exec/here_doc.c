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
	dprintf(2, "on est dans exec_here_doc\n");
	char	*line;
	char	*delimiter;

	if (!cmds->cmd)
		cmds->here_doc = open("/dev/stdin", O_CREAT | O_TRUNC, 0755);
	else
		cmds->here_doc = open(cmds->cmd, O_WRONLY | O_CREAT | O_TRUNC, 0755);
	dprintf(2, "cmds->cmd %s\n", cmds->cmd);
	dprintf(2, "cmds->here_doc %d\n", cmds->here_doc);
	if (cmds->here_doc == -1)
	{
		dprintf(2, "je suis egal a -1\n");
		ft_handle_infile_error(data, cmds);
	}
	ft_count_here_doc(cmds);
	dprintf(2, "Au depart, il y a %d here_doc\n", cmds->here_doc_count);
	if (cmds->here_doc_count > 16)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("maximum number of online documents ", 2);
		ft_putstr_fd("(\"here document\") exceeded\n", 2);
		if (close(cmds->here_doc) == -1)
			ft_handle_infile_error(data, cmds);
		return ;
	}
	while (cmds->here_doc_count > 0)
	{
		dprintf(2, "on est dans le 1er while de exec_here_doc\n");
		delimiter = ft_strjoin(cmds->redir->path, "\n");
		while (1)
		{
//			dprintf(2, "Il y a %d here_doc\n", cmds->here_doc_count);
			ft_putstr_fd("> ", 0);
			line = get_next_line(0);
			if (!ft_strcmp(line, delimiter))
			{
				free(line);
				free(delimiter);
				cmds->here_doc_count -= 1;
				cmds->redir->next ? dprintf(2, "Le next est %s\n", cmds->redir->next->path) : dprintf(2, "null\n");
				if (!cmds->redir->next)
					break ;
				if (cmds->redir->next && cmds->redir->next->type == 2)
				{
					dprintf(2, "Il y a une prochaine redir qui est un here_doc\n");
					cmds->redir = cmds->redir->next;
					break ;
				}
				if (cmds->redir->next->type != 2)
				{
					dprintf(2, "je suis differente de 2\n");
					cmds->redir = cmds->redir->next;
				}
				break ;
			}
			free(line);
		}
	}
	dprintf(2, "je suis sorti de tous les while dans handle_here_doc()\n");
	if (close(cmds->here_doc) == -1)
		ft_handle_infile_error(data, cmds);
}

void	ft_handle_here_doc(t_data *data, t_cmds *cmds)
{
	cmds->here_doc = open(cmds->cmd, O_RDONLY, 0755);
	if (cmds->here_doc == -1)
		ft_handle_infile_error(data, cmds);
	if (dup2(cmds->here_doc, 0) == -1)
		ft_handle_dup2_error(data, cmds);
	if (close(cmds->here_doc) == -1)
		ft_handle_close_error(data, cmds);
	cmds->i += 1;
	if (unlink(cmds->cmd) == -1)
	{
		free(cmds->cmd);
		ft_free_tab(cmds->cmd_path);
		ft_clean_all(data);
	}
}
