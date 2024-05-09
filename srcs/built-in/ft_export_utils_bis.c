/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils_bis.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:40:21 by skiam             #+#    #+#             */
/*   Updated: 2024/05/09 14:43:42 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env *ft_create_export_env(t_data *data)
{
    t_env   *tmp;
    char    *exp_var;
    char    *exp_value;
    
    data->env_export = NULL;
    tmp = data->env;
    while (tmp)
    {
        if (!(exp_var = ft_strdup(tmp->var)))
            return (ft_exit_code(12, ADD), NULL);
        dprintf(2, "tmp->var = %s\n", tmp->var);
        dprintf(2, "tmp->value = %s\n", tmp->value);
        if (tmp->value)
        {
            if (!(exp_value = ft_strdup(tmp->value)))
                return (ft_exit_code(12, ADD), NULL);
            dprintf(2, "exp_value = %s\n", exp_value);
        }
        else
            exp_value = NULL;
        if (!ft_lstinit_env(&data->env_export, exp_var, exp_value))
            return (ft_exit_code(12, ADD), NULL);
        tmp = tmp->next;
    }
    return (data->env_export);
}
