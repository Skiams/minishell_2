/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skiam <skiam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 12:59:18 by skiam             #+#    #+#             */
/*   Updated: 2024/03/27 21:34:25 by skiam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_env(t_data *data)
{
    t_env   *env;

    env = data->env;
    while (env)
    {
        ft_putstr_fd(env->var, 1);
        ft_putstr_fd("=", 1);
        ft_putstr_fd(env->value, 1);
        ft_putstr_fd("\n", 1);
        env = env->next;
    }
    return(ft_exit_code(0, ADD));
}