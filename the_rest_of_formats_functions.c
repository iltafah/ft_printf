/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formats2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 00:11:15 by iltafah           #+#    #+#             */
/*   Updated: 2019/12/17 11:33:06 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	i_format(t_variables *vars)
{
	d_format(vars);
	return ;
}

void	u_format(t_variables *vars)
{
	vars->u = 1;
	vars->unum = va_arg(vars->list, unsigned int);
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

void	x_format(t_variables *vars)
{
	vars->x = 1;
	vars->unum = va_arg(vars->list, unsigned int);
	fill_vars(vars);
	if (vars->minus_flag == 0)
		print_spaces(vars);
	print_zeros(vars);
	if (!(vars->point_flag == 1 && vars->unum == 0 && vars->precision == 0))
		print_hex(vars->unum, 'a', vars);
	if (vars->minus_flag == 1)
		print_spaces(vars);
	return ;
}

void	xu_format(t_variables *vars)
{
	vars->xu = 1;
	vars->unum = va_arg(vars->list, unsigned int);
	fill_vars(vars);
	if (vars->minus_flag == 0)
		print_spaces(vars);
	print_zeros(vars);
	if (!(vars->point_flag == 1 && vars->unum == 0 && vars->precision == 0))
		print_hex(vars->unum, 'A', vars);
	if (vars->minus_flag == 1)
		print_spaces(vars);
	return ;
}
