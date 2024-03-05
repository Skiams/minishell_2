/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_address.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:09:58 by eltouma           #+#    #+#             */
/*   Updated: 2023/06/14 15:53:47 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_pointeur(unsigned long n)
{
	int		result;
	char	*symbols;

	symbols = "0123456789abcdef";
	if (n < 16)
		return (ft_putchar(symbols[n]));
	else
	{
		result = ft_print_pointeur(n / 16);
		result += ft_print_pointeur(n % 16);
		return (result);
	}
}

int	ft_print_address(uintptr_t n)
{
	if (n == 0)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	else
	{
		write(1, "0x", 2);
		return (ft_print_pointeur(n) + 2);
	}
}
