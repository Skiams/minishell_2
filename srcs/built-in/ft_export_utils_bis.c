/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils_bis.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skiam <skiam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:40:21 by skiam             #+#    #+#             */
/*   Updated: 2024/05/06 18:14:04 by skiam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env *ft_create_export_env(t_data *data)
{
    t_env   *tmp;
    char    *exp_var;
    char    *exp_value;
    
    tmp = data->env;
    while (tmp)
    {
        if (!(exp_var = ft_strdup(tmp->var)))
            return (ft_exit_code(12, ADD), NULL);
        if (!(exp_value = ft_strdup(tmp->value)))
            return (ft_exit_code(12, ADD), NULL);
        if (!ft_lstinit_env(&data->env_export, exp_var, exp_value))
            return (ft_exit_code(12, ADD), NULL);
        tmp = tmp->next;
    }
    return (data->env_export);
}
