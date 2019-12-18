/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 14:47:21 by iltafah           #+#    #+#             */
/*   Updated: 2019/12/18 15:09:48 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	width_calc(char *str, t_variables *vars)
{
	while (!is_format(*str))
	{
		if (*str == '.')
			return ;
		else if (*str == '*')
		{
			vars->width = va_arg(vars->list, int);
			if (vars->width < 0)
			{
				vars->width *= -1;
				vars->minus_flag = 1;
				vars->zero_flag = 0;
			}
			return ;
		}
		else if (*str >= '1' && *str <= '9')
		{
			vars->width = my_atoi(str);
			return ;
		}
		str++;
	}
	return ;
}

void	precision_calc(char *str, t_variables *vars)
{
	while (!is_format(*str))
	{
		if (*str == '.')
		{
			while (!is_format(*str))
			{
				if (*str == '*')
				{
					vars->precision = va_arg(vars->list, int);
					if (vars->precision < 0)
						vars->point_flag = 0;
					return ;
				}
				else if (*str >= '1' && *str <= '9')
				{
					vars->precision = my_atoi(str);
					return ;
				}
				str++;
			}
			return ;
		}
		str++;
	}
	return ;
}

int		udigit_calc(unsigned long n, int base, t_variables *vars)
{
	int digit;

	digit = 0;
	if (n == 0 && !(vars->point_flag == 1 && vars->precision == 0))
		return (1);
	while (n != 0)
	{
		digit++;
		n /= base;
	}
	return (digit);
}

void	calc_zeros(t_variables *vars)
{
	if (vars->point_flag == 1 && vars->s == 0 && vars->c == 0 && vars->mod == 0)
	{
		if (vars->precision > vars->arg_len)
			vars->zero_times = vars->precision - vars->arg_len;
	}
	else if (vars->zero_flag == 1)
	{
		if (vars->width > vars->arg_len)
			vars->zero_times = vars->width - vars->arg_len - vars->negative;
	}
	return ;
}

void	calc_spaces(t_variables *vars)
{
	vars->space_times = vars->width - vars->zero_times;
	vars->space_times = vars->space_times - vars->arg_len - vars->negative;
	vars->space_times = vars->space_times < 0 ? 0 : vars->space_times;
	return ;
}
