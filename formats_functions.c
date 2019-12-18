/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formats1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 00:09:46 by iltafah           #+#    #+#             */
/*   Updated: 2019/12/17 11:33:04 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	c_format(t_variables *vars)
{
	vars->c = 1;
	fill_vars(vars);
	if (vars->minus_flag == 0)
		print_spaces(vars);
	print_zeros(vars);
	ft_putchar(va_arg(vars->list, int), vars);
	if (vars->minus_flag == 1)
		print_spaces(vars);
	return ;
}

void	mod_format(t_variables *vars)
{
	vars->mod = 1;
	fill_vars(vars);
	if (vars->minus_flag == 0)
		print_spaces(vars);
	print_zeros(vars);
	ft_putchar(('%'), vars);
	if (vars->minus_flag == 1)
		print_spaces(vars);
	return ;
}

void	s_format(t_variables *vars)
{
	static char null[6] = "(null)";

	vars->s = 1;
	vars->ptr = va_arg(vars->list, char*);
	if (vars->ptr == NULL)
		vars->ptr = null;
	fill_vars(vars);
	if (vars->minus_flag == 0)
		print_spaces(vars);
	print_zeros(vars);
	my_putstr(vars->ptr, vars->arg_len, vars);
	if (vars->minus_flag == 1)
		print_spaces(vars);
	return ;
}

void	p_format(t_variables *vars)
{
	vars->p = 1;
	vars->unum = va_arg(vars->list, unsigned long);
	vars->width -= 2;
	fill_vars(vars);
	if (vars->minus_flag == 0)
		print_spaces(vars);
	my_putstr("0x", 2, vars);
	print_zeros(vars);
	if (!(vars->point_flag == 1 && vars->unum == 0 && vars->precision == 0))
		print_hex(vars->unum, 'a', vars);
	if (vars->minus_flag == 1)
		print_spaces(vars);
	return ;
}

void	d_format(t_variables *vars)
{
	int		num;

	vars->d = 1;
	num = va_arg(vars->list, int);
	vars->negative = num < 0 ? 1 : 0;
	vars->unum = vars->negative == 1 ? -(long)num : num;
	fill_vars(vars);
	if (vars->minus_flag == 0)
		print_spaces(vars);
	print_zeros(vars);
	if (!(vars->point_flag == 1 && vars->unum == 0 && vars->precision == 0))
		ft_putunbr(vars->unum, vars);
	if (vars->minus_flag == 1)
		print_spaces(vars);
	return ;
}
