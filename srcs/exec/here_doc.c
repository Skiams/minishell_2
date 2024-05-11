/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skiam <skiam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 22:19:04 by eltouma           #+#    #+#             */
/*   Updated: 2024/05/08 16:58:50 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_count_here_doc(t_cmds *cmds)
{
	t_redir	*tmp;

	tmp = cmds->redir;
	while (tmp != NULL)
	{
		if (tmp->type == 2)
			cmds->here_doc_count += 1;
		tmp = tmp->next;
	}
	return (cmds->here_doc_count);
}

void	ft_is_max_here_doc_nb_reached(t_data *data, t_cmds *cmds)
{
	t_cmds	*tmp;

	tmp = cmds;
	while (cmds != NULL)
	{
		cmds->here_doc_count = ft_count_here_doc(cmds);
		if (cmds->here_doc_count > 16)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd("maximun here-doc count exceeded\n", 2);
			ft_exit_properly(data, cmds);
		}
		cmds = cmds->next;
	}
	cmds = tmp;
}

void	ft_restore_stdin(t_data *data, t_cmds *cmds)
{
	if (cmds->cmd && !ft_is_a_built_in(cmds->cmd))
	{
		ft_dup_stdin_stdout(data, cmds);
		ft_putstr_fd("> ", cmds->dev_stdin);
		ft_dup2_and_close_stdin_stdout(data, cmds);
	}
	else
		ft_putstr_fd("> ", cmds->dev_stdin);
}

// implementer les signaux
void	ft_exec_here_doc(t_data *data, t_cmds *cmds, t_redir *redir)
{
	char	*line;
	char	*delimiter;

	if (!cmds->cmd)
	{
		dprintf(2, "coucou, je n' ai pas de commande\n");
		cmds->infile = open("/dev/stdin", O_CREAT | O_TRUNC, 0755);
	}
	else
	{
		//del =	strjoin(".", delimiter);
		//name	= strjoin(del, itoa);
		//cmds->infile = open(name, O_RDONLY, 0755);
		cmds->infile = open(redir->path, O_WRONLY | O_CREAT | O_TRUNC, 0755);
	}
	if (cmds->infile == -1)
		ft_handle_infile_error(data, cmds);
	delimiter = ft_strjoin(redir->path, "\n");
	while (1)
	{
//		ft_restore_stdin(data, cmds);
		ft_putstr_fd("> ", 0);
		line = get_next_line(0);
		if (!line)
			break ;
		if (!ft_strcmp(line, delimiter))
			break ;
		ft_putstr_fd(line, cmds->infile);
		free(line);

	}
	free(line); 
	free(delimiter);
	if (close(cmds->infile) == -1)
		ft_handle_infile_error(data, cmds);
}

void	ft_handle_here_doc(t_data *data, t_cmds *cmds)
{
	//	dprintf(2, "je rentre ici\n");
	//del =	strjoin(".", delimiter);
	//name	= strjoin(del, itoa);
	//cmds->infile = open(name, O_RDONLY, 0755);
	cmds->infile = open(cmds->redir->path, O_RDONLY, 0755);
	if (cmds->infile == -1)
	{
		//		dprintf(2, "je fail la\n");
		ft_handle_infile_error(data, cmds);
	}
	if (dup2(cmds->infile, 0) == -1)
		ft_handle_dup2_error(data, cmds);
	if (close(cmds->infile) == -1)
		ft_handle_close_error(data, cmds);

	cmds->i += 1;
	//	if (unlink(cmds->redir->path) == -1)
	//		free(cmds->redir->path);
	//dprintf(2, "je vais jusqu'ici\n");
}
