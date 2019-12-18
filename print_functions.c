/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 15:12:14 by iltafah           #+#    #+#             */
/*   Updated: 2019/12/18 15:13:27 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_spaces(t_variables *vars)
{
	while (vars->space_times--)
		ft_putchar(' ', vars);
	return ;
}

void	print_zeros(t_variables *vars)
{
	if (vars->negative == 1)
		ft_putchar('-', vars);
	while (vars->zero_times--)
		ft_putchar('0', vars);
	return ;
}

void	ft_putunbr(unsigned long n, t_variables *vars)
{
	if (n >= 10)
	{
		ft_putunbr(n / 10, vars);
		ft_putchar((n % 10) + '0', vars);
	}
	else
		ft_putchar(n + '0', vars);
	return ;
}

void	print_hex(unsigned long num, char l_u, t_variables *vars)
{
	int		digit;

	digit = 0;
	if (num >= 10)
	{
		if (num / 16 != 0)
			print_hex(num / 16, l_u, vars);
		digit = num % 16;
		if (digit >= 10)
			ft_putchar((digit - 10) + l_u, vars);
		else
			ft_putchar(digit + '0', vars);
	}
	else
		ft_putchar(num + '0', vars);
	return ;
}
