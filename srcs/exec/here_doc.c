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
	while (tmp != NULL)
	{
		cmds->here_doc_count += 1;
		tmp = tmp->next;
	}
	return (cmds->here_doc_count);
}

void	ft_exec_here_doc(t_data *data, t_cmds *cmds)
{
//	t_redir	*tmp;
	char	*line;
	char	*delimiter;

//	tmp = cmds->redir;
	if (!cmds->cmd)
		cmds->here_doc = open("/dev/stdin", O_CREAT | O_TRUNC, 0755);
	else
		cmds->here_doc = open(cmds->cmd, O_WRONLY | O_CREAT | O_TRUNC, 0755);
	if (cmds->here_doc == -1)
		ft_handle_infile_error(data, cmds);
	ft_count_here_doc(cmds);
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
		delimiter = ft_strjoin(cmds->redir->path, "\n");
		while (1)
		{
			ft_putstr_fd("> ", 0);
			line = get_next_line(0);
			if (!line || !ft_strcmp(line, delimiter))
			{
				free(line);
				free(delimiter);
				cmds->here_doc_count -= 1;
				if (!cmds->redir->next)
					break ;
				free(cmds->redir->path);
				cmds->redir = cmds->redir->next;
				break ;
			}
			free(line);
		}
	}
//	cmds->redir = tmp;
//	ft_clear_redirlst(&cmds->redir, &ft_free_ptr);
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
