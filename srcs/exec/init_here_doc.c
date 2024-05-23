/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:11:38 by eltouma           #+#    #+#             */
/*   Updated: 2024/05/22 19:28:12 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_heredoc	*ft_lstnew_heredoc(void)
{
	t_heredoc	*new_node;

	new_node = (t_heredoc *)malloc(sizeof(t_heredoc));
	if (!new_node)
		return (NULL);
	new_node->delimiter = NULL;
	new_node->name = NULL;
	new_node->read = 0;
	new_node->next = NULL;
	return (new_node);
}

t_heredoc	*ft_lstlast_heredoc(t_heredoc *node)
{
	if (!node)
		return (NULL);
	while (node->next != NULL)
		node = node->next;
	return (node);
}

void	ft_lstadd_back_heredoc(t_heredoc **here_doc)
{
	t_heredoc	*new_node;
	t_heredoc	*last_node;

	if (!here_doc)
		return ;
	last_node = ft_lstlast_heredoc(*here_doc);
	new_node = ft_lstnew_heredoc();
	if (!last_node)
		*here_doc = new_node;
	else
		last_node->next = new_node;
}
