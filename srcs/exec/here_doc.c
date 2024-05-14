/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skiam <skiam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 22:19:04 by eltouma           #+#    #+#             */
/*   Updated: 2024/05/14 21:47:03 by eltouma          ###   ########.fr       */
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
		cmds->tmp_file = ft_strjoin(".", redir->path);
		cmds->index = ft_itoa(cmds->here_doc_count);
		cmds->name = ft_strjoin(cmds->tmp_file, cmds->index);
		dprintf(2, "cmds->name = %s\n", cmds->name);
		cmds->infile = open(cmds->name, O_WRONLY | O_CREAT | O_TRUNC, 0755);
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
	if (cmds->cmd)
	{
		free(cmds->tmp_file);
		free(cmds->index);
		free(cmds->name);
	}
	if (close(cmds->infile) == -1)
		ft_handle_infile_error(data, cmds);
}

void	ft_open_here_doc(t_data *data, t_cmds *cmds)
{
	cmds->tmp_file = ft_strjoin(".", cmds->redir->path);
	cmds->index = ft_itoa(cmds->here_doc_count);
	cmds->name = ft_strjoin(cmds->tmp_file, cmds->index);
	dprintf(2, "Dans handle_here_doc cmds->name = %s\n", cmds->name);
	cmds->infile = open(cmds->name, O_RDONLY, 0755);
	if (cmds->infile == -1)
		ft_handle_infile_error(data, cmds);
	if (dup2(cmds->infile, 0) == -1)
		ft_handle_dup2_error(data, cmds);
	if (close(cmds->infile) == -1)
		ft_handle_close_error(data, cmds);
	free(cmds->tmp_file);
	free(cmds->index);
//	free(cmds->name);
}
