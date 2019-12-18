/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 00:04:44 by iltafah           #+#    #+#             */
/*   Updated: 2019/12/17 09:02:07 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

typedef struct		s_variables
{
	va_list			list;
	int				width;
	int				precision;
	unsigned long	unum;
	char			*ptr;
	int				zero_flag;
	int				minus_flag;
	int				point_flag;
	int				space_times;
	int				zero_times;
	int				n_printed;
	int				arg_len;
	int				negative;
	int				c;
	int				d;
	int				i;
	int				u;
	int				s;
	int				p;
	int				x;
	int				xu;
	int				mod;
}					t_variables;

typedef void		(*t_pointer)(t_variables*);

int					ft_printf(const char *str, ...);
int					chose_function(char *str, t_variables *vars);
void				precision_calc(char *str, t_variables *vars);
void				width_calc(char *str, t_variables *vars);
int					f_index(char f);
void				c_format(t_variables *vars);
void				mod_format(t_variables *vars);
void				s_format(t_variables *vars);
void				p_format(t_variables *vars);
void				d_format(t_variables *vars);
void				i_format(t_variables *vars);
void				u_format(t_variables *vars);
void				x_format(t_variables *vars);
void				xu_format(t_variables *vars);
void				ft_putchar(char c, t_variables *vars);
int					ft_strlen(char *str);
void				my_putstr(char *str, int n, t_variables *vars);
void				initialize_zero(t_variables *vars);
void				fill_flags(char *str, t_variables *vars);
void				ft_putunbr(unsigned long n, t_variables *vars);
void				print_hex(unsigned long num, char l_u, t_variables *vars);
int					udigit_calc(unsigned long n, int base, t_variables *vars);
int					is_format(char c);
int					my_atoi(char *str);
void				calc_zeros(t_variables *vars);
void				calc_spaces(t_variables *vars);
void				fill_vars(t_variables *vars);
void				print_spaces(t_variables *vars);
void				print_zeros(t_variables *vars);

#endif
