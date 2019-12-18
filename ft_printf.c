/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 00:01:13 by iltafah           #+#    #+#             */
/*   Updated: 2019/12/18 15:17:20 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	initialize_zero(t_variables *vars)
{
	vars->width = 0;
	vars->precision = 0;
	vars->unum = 0;
	vars->ptr = NULL;
	vars->zero_flag = 0;
	vars->minus_flag = 0;
	vars->point_flag = 0;
	vars->space_times = 0;
	vars->zero_times = 0;
	vars->arg_len = 0;
	vars->negative = 0;
	vars->c = 0;
	vars->d = 0;
	vars->i = 0;
	vars->u = 0;
	vars->s = 0;
	vars->p = 0;
	vars->x = 0;
	vars->xu = 0;
	vars->mod = 0;
	return ;
}

int		f_index(char f)
{
	int			i;
	static char	arr[9] = "cspdiuxX%";

	i = 0;
	while (arr[i])
	{
		if (arr[i] == f)
			break ;
		i++;
	}
	return (i);
}

int		chose_function(char *str, t_variables *vars)
{
	int					j;
	static t_pointer	format[9] = {c_format, s_format, p_format, d_format,
						i_format, u_format, x_format, xu_format, mod_format};

	j = 0;
	while (str[j])
	{
		if (is_format(str[j]))
		{
			initialize_zero(vars);
			fill_flags(str, vars);
			width_calc(str, vars);
			precision_calc(str, vars);
			format[f_index(str[j])](vars);
			return (j + 1);
		}
		j++;
	}
	return (j);
}

int		ft_printf(const char *str, ...)
{
	t_variables		vars;
	int				i;

	i = 0;
	va_start(vars.list, str);
	vars.n_printed = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%')
			i += chose_function((char*)str + i + 1, &vars) + 1;
		else
			ft_putchar(str[i++], &vars);
	}
	va_end(vars.list);
	return (vars.n_printed);
}
