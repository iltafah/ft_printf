/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 00:01:13 by iltafah           #+#    #+#             */
/*   Updated: 2019/12/10 23:31:56 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_variables
{
	va_list			list;
	va_list			copy;
	int				width;
	int				precision;
	int				digits;
	int				num;
	unsigned long	unum;
	int				zero_flag;
	int				minus_flag;
	int				point_flag;
	int				space_times;
	int				zero_times;
	int				n_printed;
	int				str_len;
	int				null;
}					t_variables;
/*
	int				c;
	int				s;
	int				p;
	int				d;
	int				i;
	int				u;
	int				x;
	int				X;
}					t_variables;
*/
int		f_index(char f)
{
	int		i;
	char	arr[9] = "cspdiuxX%";

	i = 0;
	while (arr[i])
	{
		if (arr[i] == f)
			break ;
		i++;
	}
	return (i);
}

void	ft_putchar(char c, t_variables *vars)
{
	write(1,&c,1);
	vars->n_printed += 1;
}

int		ft_strlen(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr(char *str, t_variables *vars)
{
	while (*str)
		ft_putchar(*str++, vars);
}

void	my_putstr(char *str, int n, t_variables *vars)
{
	while (*str && n--)
		ft_putchar(*str++, vars);
}

void	ft_putnbr(int nbr, t_variables *vars)
{
	unsigned int n;

	n = nbr >= 0 ? nbr : nbr * -1;
	if (nbr < 0)
		ft_putchar('-', vars);
	if (n >= 10)
	{
		ft_putnbr(n / 10, vars);
		ft_putchar((n % 10) + '0', vars);
	}
	else
		ft_putchar(n + '0', vars);
}
void	ft_putunbr(unsigned long n, t_variables *vars)
{
	if (n >= 10)
	{
		ft_putnbr(n / 10, vars);
		ft_putchar((n % 10) + '0', vars);
	}
	else
		ft_putchar(n + '0', vars);
}

void	print_hex(unsigned long num, char aA, t_variables *vars)
{
	int		digit;

	digit = 0;
	if (num >= 10)
	{
		if (num / 16 != 0)
			print_hex(num / 16, aA, vars);
		digit = num % 16;
		if (digit >= 10)
			ft_putchar((digit - 10) + aA, vars);
		else
			ft_putnbr(digit, vars);
	}
	else
		ft_putnbr(num, vars);
}

int		is_format(char c)
{
	return (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i' || c == 'u' || c == 'x' || c == 'X' || c == '%' || c == '\0');
}

int		is_flag(char c)
{
	return (c == '-' || c == '.' || c == '*');
}

int		my_atoi(char *str)
{
	int		num;

	num = 0;
	while (!is_format(*str) && !is_flag(*str))
	{
		num = (num * 10) + (*str - '0');
		str++;
	}
	return (num);
}

int		digit_calc(int n)
{
	int digit;

	digit = 0;
	if (n == 0)
	   return (1);	
	while (n != 0)
	{
		digit++;
		n /= 10;
	}
	return (digit);
}

int		udigit_calc(unsigned long n, int base)
{
	int digit;

	digit = 0;
	if (n == 0)
	   return (1);	
	while (n != 0)
	{
		digit++;
		n /= base;
	}
	return (digit);
}

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
}

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
}

void	calc_zeros(t_variables *vars)
{
	if (vars->precision > vars->digits)
		vars->zero_times = vars->precision - vars->digits;
	else
		vars->zero_times = 0;
}

void	calc_spaces(t_variables *vars)
{
	vars->space_times = vars->width - vars->zero_times - vars->digits;
	vars->space_times = vars->num < 0 ? vars->space_times - 1 : vars->space_times;
	if (vars->space_times < 0)
		vars->space_times = 0;
}

void	calc_spaces_s(t_variables *vars)
{
	if (vars->precision > vars->str_len)
		vars->precision = vars->str_len;
	if (vars->point_flag == 1 && vars->width > vars->precision && vars->precision >= 0)
		vars->space_times = vars->width - vars->precision;
	else
		vars->space_times = vars->width - vars->str_len;
	if (vars->space_times < 0)
		vars->space_times = 0;
}

void	fill_d(char *str, t_variables *vars)
{
	width_calc(str, vars);
	precision_calc(str, vars);
	vars->num = va_arg(vars->list, int);
	if (vars->num == 0 && vars->point_flag == 1)
		vars->digits = 0;
	else
		vars->digits = digit_calc(vars->num);
	calc_zeros(vars);
	calc_spaces(vars);
}

void	fill_x(char *str, t_variables *vars)
{
	width_calc(str, vars);
	precision_calc(str, vars);
	vars->unum = va_arg(vars->list, unsigned long);
	if (vars->unum == 0 && vars->point_flag == 1)
		vars->digits = 0;
	else
		vars->digits = udigit_calc(vars->unum, 16);
	calc_zeros(vars);
	calc_spaces(vars);

}

void	fill_u(char *str, t_variables *vars)
{
	width_calc(str, vars);
	precision_calc(str, vars);
	vars->unum = va_arg(vars->list, unsigned int);
	if (vars->unum == 0 && vars->point_flag == 1)
		vars->digits = 0;
	else
		vars->digits = udigit_calc(vars->unum, 10);
	calc_zeros(vars);
	calc_spaces(vars);
}

void	fill_c(char *str, t_variables *vars)
{
	width_calc(str, vars);
	vars->digits += 1;
	calc_spaces(vars);
}

void	fill_p(char *str, t_variables *vars)
{
	vars->unum = va_arg(vars->list, unsigned long);
	width_calc(str, vars);
	vars->digits = udigit_calc(vars->unum, 16) + 2;
	calc_spaces(vars);
}

void	fill_s(char *str, t_variables *vars)
{
	width_calc(str, vars);
	precision_calc(str, vars);
	va_copy(vars->copy, vars->list);
	if (va_arg(vars->copy, char*) == NULL)
		vars->null = 1;
	va_copy(vars->copy, vars->list);
	vars->str_len = vars->null == 1 ? 6 : ft_strlen(va_arg(vars->copy, char*));
	calc_spaces_s(vars);

}

void	print_spaces_zeros(t_variables *vars)
{
	if (vars->num < 0 && vars->zero_flag == 1 && vars->point_flag == 0)
	{
		ft_putchar('-', vars);
		vars->num *= -1;
	}
	if (vars->zero_flag == 1 && vars->point_flag == 0)
		while (vars->space_times--)
		{
			ft_putchar('0', vars);
		}
	else
		while (vars->space_times--)
			ft_putchar(' ', vars);
}

void	print_zeros(t_variables *vars)
{
	if (vars->num < 0 && (vars->zero_flag == 1 || vars->point_flag == 1))
	{
		ft_putchar('-', vars);
		vars->num *= -1;
	}
	while (vars->zero_times--)
		ft_putchar('0', vars);
}

void	c_format(char *str, t_variables *vars)
{
	fill_flags(str, vars);
	fill_c(str, vars);
	if (vars->minus_flag == 0)
		print_spaces_zeros(vars);
	ft_putchar(va_arg(vars->list, int), vars);
	if (vars->minus_flag == 1)
		print_spaces_zeros(vars);
	return ;
}

void	mod_format(char *str, t_variables *vars)
{
	fill_flags(str, vars);
	fill_c(str, vars);
	if (vars->minus_flag == 0)
		print_spaces_zeros(vars);
	ft_putchar(('%'), vars);
	if (vars->minus_flag == 1)
		print_spaces_zeros(vars);
	return ;
}

void	s_format(char *str, t_variables *vars)
{
	fill_flags(str, vars);
	fill_s(str, vars);
	if (vars->minus_flag == 0)
		print_spaces_zeros(vars);
	if (vars->point_flag == 1)
	{
		if (vars->null == 1)
			my_putstr("(null)", vars->precision, vars);
		else
			my_putstr(va_arg(vars->list, char *), vars->precision, vars);
	}
	else
	{
		if (vars->null == 1)
			my_putstr("(null)", 6, vars);
		else
			my_putstr(va_arg(vars->list, char*), vars->str_len, vars);
	}
	if (vars->minus_flag == 1)
		print_spaces_zeros(vars);
	return ;
}

void	p_format(char *str, t_variables *vars)
{
	fill_flags(str, vars);
	fill_p(str, vars);
	if (vars->minus_flag == 0)
		print_spaces_zeros(vars);
	my_putstr("0x", 2, vars);
	print_hex(vars->unum, 'a', vars);
	if (vars->minus_flag == 1)
		print_spaces_zeros(vars);
	return ;
}

void	d_format(char *str, t_variables *vars)
{
	fill_flags(str, vars);
	if (vars->minus_flag == 1)
		vars->zero_flag = 0;
	fill_d(str, vars);
	if (vars->minus_flag == 0)
		print_spaces_zeros(vars);
	print_zeros(vars);
	if (!(vars->point_flag == 1 && vars->num == 0))
		ft_putnbr(vars->num, vars);
	if (vars->minus_flag == 1 && vars->zero_flag == 0)
		print_spaces_zeros(vars);
	return ;
}

void	i_format(char *str, t_variables *vars)
{
	d_format(str, vars);
	return ;
}

void	u_format(char *str, t_variables *vars)
{
	fill_flags(str, vars);
	fill_u(str, vars);
	if (vars->minus_flag == 0)
		print_spaces_zeros(vars);
	print_zeros(vars);
	if (!(vars->point_flag == 1 && vars->unum == 0))
		ft_putunbr(vars->unum, vars);
	if (vars->minus_flag == 1 && vars->zero_flag == 0)
		print_spaces_zeros(vars);
	return ;
}

void	x_format(char *str, t_variables *vars)
{
	fill_flags(str, vars);
	fill_x(str, vars);
	if (vars->minus_flag == 0)
		print_spaces_zeros(vars);
	print_zeros(vars);
	if (!(vars->point_flag == 1 && vars->unum == 0))
		print_hex(vars->unum, 'a', vars);
	if (vars->minus_flag == 1 && vars->zero_flag == 0)
		print_spaces_zeros(vars);	
	return ;
}

void	X_format(char *str, t_variables *vars)
{
	fill_flags(str, vars);
	fill_x(str, vars);
	if (vars->minus_flag == 0)
		print_spaces_zeros(vars);
	print_zeros(vars);
	if (!(vars->point_flag == 1 && vars->unum == 0))
		print_hex(vars->unum, 'A', vars);
	if (vars->minus_flag == 1 && vars->zero_flag == 0)
		print_spaces_zeros(vars);
	return ;
}

void (*_format[9])(char *, t_variables*) = {c_format, s_format, p_format, d_format, i_format, u_format, x_format, X_format, mod_format};


void	initialize_zero(t_variables *vars)
{
	vars->width = 0;
	vars->precision = 0;
	vars->digits = 0;
	vars->num = 0;
	vars->unum = 0;
	vars->zero_flag = 0;
	vars->minus_flag = 0;
	vars->point_flag = 0;
	vars->space_times = 0;
	vars->zero_times = 0;
	vars->str_len = 0;
	vars->null = 0;
	/*vars->c = 0;
	vars->s = 0;
	vars->p = 0;
	vars->d = 0;
	vars->i = 0;
	vars->u = 0;
	vars->x = 0;
	vars->X = 0;
*/
	return ;
}



int		ft_printf(const char *str, ...)
{
	t_variables vars;
	int		i;
	int		j;

	i = 0;
	va_start(vars.list, str);
	vars.n_printed = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			i++;
			j = i;
			while(str[j])
			{
				if (is_format(str[j]))
				{
					initialize_zero(&vars);
					_format[f_index(str[j])]((char*)(str + i), &vars);
					break ;
				}
				j++;
			}
			if (str[j])
				i = j + 1;
		}
		else
			ft_putchar(str[i++], &vars);
	}
	va_end(vars.list);
	return (vars.n_printed);
}

/*
ft_printf("|%*.*d|\n", -12, 5, -10);
    printf("|%*.*d|\n", -12, 5, -10);
	    printf("|%+.5d|\n", 12);
		    ft_printf("|%+.5d|\n", 12);
			    ft_printf("|%-12.5d|\n", 10);
				    printf("|%-12.5d|\n", 10);
   */


// "|%15.10s|\n",NULL
//"|%%alloha ma d friend %s|\n","nice"

/*

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// "|%15.10s|\n",NULL
//"|%%alloha ma d friend %s|\n","nice"
//"|%10p%|\n",(void*)100                                                            /// need to test it ///

#define test  "|%s|\n","hello" //"|%.10x|\n",21
#define test2 "<%d>\n"

int main()
{
	char *str = strdup("hello");
	char *str2 = strdup("world");
	int a;
	int b;
	
	a = printf(test);
	b = ft_printf(test);
	printf(test2,a);
	ft_printf(test2,b);
	//printf("|%*d|\n",6,9);
	//ft_printf("|%*d|\n",6,9);
	//ft_printf("|%-10c|\n",a);
	//printf("%i%d. this is one char : |%c| nice \n%s %s\naddress = %p\n%u == %x == %X\n",0,1,a+1,str,str2,ptr,30,30,30);
	//ft_printf("----------------------------\n");
	//ft_printf("%i%d. this is one char : |%c| nice \n%s %s\naddress = %p\n%u == %x == %X\n",0,2,a+1,str,str2,ptr,30,30,30);
	
	//ft_printf2();
	//ft_printf("this is my printf : \nnumbers: %d \n %d \n %d\n%s %s\n%c\n%c",10,x,0,str,str2,a,b);
}*/
