/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_basic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 12:01:30 by bcai              #+#    #+#             */
/*   Updated: 2024/04/07 20:46:29 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	printf_check(va_list ptr, char c, int *error)
{
	int	print_len;

	print_len = 0;
	if (c == 'd' || c == 'i')
		print_len = ft_putd(va_arg(ptr, int), error);
	else if (c == 'u')
		print_len = ft_putun_fd(va_arg(ptr, unsigned int), 1, error);
	else if (c == 'c')
		print_len = ft_putchar_len((char)va_arg(ptr, int), 1, error);
	else if (c == 's')
		print_len = ft_putstr_len(va_arg(ptr, char *), 1, error);
	else if (c == 'p')
		print_len = ft_putptr_fd((unsigned long long)va_arg(ptr, void *), 1,
				error);
	else if (c == 'x' || c == 'X')
		print_len = ft_puthn_fd((unsigned int)va_arg(ptr, int), 1, c, error);
	else if (c == '%')
	{
		*error = write(1, "%", 1);
		print_len = 1;
	}
	return (print_len);
}

static int	check_error(int error, int print_len)
{
	if (error == -1)
		return (-1);
	else
		return (print_len);
}

int	ft_printf(const char *format, ...)
{
	va_list	ptr;
	int		i;
	int		print_len;
	int		error;

	error = 0;
	va_start(ptr, format);
	i = 0;
	print_len = 0;
	while (format[i] && error != -1)
	{
		if (format[i] == '%' && ft_strchr("diucspxX%", format[i + 1]))
		{
			i++;
			print_len += printf_check(ptr, format[i++], &error);
		}
		if ((format[i] && format[i] != '%') || (format[i] == '%'
				&& !ft_strchr("diucspxX%", format[i + 1])))
		{
			error = write(1, &format[i++], 1);
			print_len++;
		}
	}
	va_end(ptr);
	return (check_error(error, print_len));
}
/*
int	main(void)
{
	char			s[] = "moray";
	char			c;
	int				num;
	int				num2;
	int				num3;
	unsigned int	uint;
	int				print_len;
	int				print_len2;

	c = 'm';
	num = 27;
	num2 = 36475873;
	num3 = -274657;
	uint = 4294967295;
	print_len = ft_printf_basic("The string is %s, the character is %c, \
			the number is %d.the unsigned int is %u, num3 is %i %%\n", s, c, \
			num, uint, num3);
	print_len2 = printf("The string is %s, the character is %c, \
			the number is%d.the unsigned int is %u, num3 is %i %%\n", s, c, \
			num, uint, num3);
	printf("%d chars are printed\n", print_len);
	printf("%d chars are printed with the official printf\n", print_len2);
	ft_printf_basic("num2's hexidecimal value is %x\n", num2);
	ft_printf_basic("num2's hexidecimal value in uppercase is %X\n", num2);
	ft_printf_basic("The number's  memory address is %p.\n", &num);
	printf(" The number's memory address is %p.\n", &num);
	return (0);
}*/