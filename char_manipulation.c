/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_manipulation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 15:04:39 by iltafah           #+#    #+#             */
/*   Updated: 2019/12/18 15:09:29 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(char c, t_variables *vars)
{
	write(1, &c, 1);
	vars->n_printed += 1;
	return ;
}

void	my_putstr(char *str, int n, t_variables *vars)
{
	while (*str && n--)
		ft_putchar(*str++, vars);
	return ;
}

int		ft_strlen(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int		is_format(char c)
{
	return (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i' ||
			c == 'u' || c == 'x' || c == 'X' || c == '%' || c == '\0');
}

int		my_atoi(char *str)
{
	int		num;

	num = 0;
	while (*str >= '0' && *str <= '9')
	{
		num = (num * 10) + (*str - '0');
		str++;
	}
	return (num);
}
