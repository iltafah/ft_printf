/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filling_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 15:17:47 by iltafah           #+#    #+#             */
/*   Updated: 2019/12/18 15:19:03 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	fill_flags(char *str, t_variables *vars)
{
	int	n;

	n = 0;
	while (!is_format(*str))
	{
		if (*str >= '1' && *str <= '9')
			n = 1;
		else if (vars->point_flag == 0 && *str == '.')
			vars->point_flag = 1;
		else if (n == 0 && vars->zero_flag == 0 && *str == '0')
			vars->zero_flag = 1;
		else if (vars->minus_flag == 0 && *str == '-')
			vars->minus_flag = 1;
		str++;
	}
	if (vars->zero_flag == 1 && vars->minus_flag == 1)
		vars->zero_flag = 0;
	return ;
}

void	fill_vars(t_variables *vars)
{
	if (vars->d == 1 || vars->i == 1 || vars->u == 1)
		vars->arg_len = udigit_calc(vars->unum, 10, vars);
	else if (vars->x == 1 || vars->xu == 1 || vars->p == 1)
		vars->arg_len = udigit_calc(vars->unum, 16, vars);
	else if (vars->c == 1 || vars->mod == 1)
		vars->arg_len = 1;
	else if (vars->s == 1)
	{
		vars->arg_len = ft_strlen(vars->ptr);
		if (vars->point_flag == 1)
			if (vars->precision < vars->arg_len)
				vars->arg_len = vars->precision;
	}
	calc_zeros(vars);
	calc_spaces(vars);
	return ;
}
