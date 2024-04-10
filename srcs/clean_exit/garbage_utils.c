/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:46:14 by ahayon            #+#    #+#             */
/*   Updated: 2024/04/10 18:46:34 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*ft_lstnew_malloc(size_t size)
{
	t_list	*temp;

	temp = malloc(sizeof(t_list));
	if (temp == NULL)
		return (NULL);
	temp->content = malloc(size);
	if (temp->content == NULL)
		return (free(temp), temp = NULL);
	temp->next = NULL;
	return (temp);
}

t_list	*ft_lstnew_add(void *addr)
{
	t_list	*temp;

	if (!addr)
		return (NULL);
	temp = malloc(sizeof(t_list));
	if (temp == NULL)
		return (free(addr), addr = NULL);
	temp->content = addr;
	temp->next = NULL;
	return (temp);
}