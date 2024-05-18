/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:57:04 by bcai              #+#    #+#             */
/*   Updated: 2024/05/18 18:12:57 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	g_spaces[] = " \t\r\n\v";
//char	g_signs[] = "<|>;()";

int	get_intype(char **start)
{
	int	type;

	type = **start;
	(*start)++;
	if (**start == '<')
	{
		type = 'h';
		(*start)++;
	}
	return (type);
}

int	get_outtype(char **start)
{
	int	type;

	type = **start;
	(*start)++;
	if (**start == '>')
	{
		type = '+';
		(*start)++;
	}
	return (type);
}

int	get_andtype(char **start)
{
	int	type;

	type = 0;
	(*start)++;
	if (**start == '&')
	{
		type = '&';
		(*start)++;
	}
	return (type);
}

int	get_atype(char **start, char *end)
{
	int		type;
	int		quote_num;
	t_gl	*gl;

	gl = get_gl();
	quote_num = 0;
	type = 'a';
	while (*start < end && !ft_strchr(gl->spaces, **start)
		&& !ft_strchr(gl->signs, **start))
	{
		printf("----73****\n");
		if (**start == '"' || **start == 39)
			quote_num++;
		(*start)++;
	}
	if (quote_num == 1)
	{
		while (*start < end && (**start != '"' || **start != 39))
			(*start)++;
	}
	return (type);
}

int	get_quotetype(char **start, char *end)
{
	int	type;

	type = **start;
	(*start)++;
	while (*start < end && **start != '"')
		(*start)++;
	if (**start != '"')
		handle_error("Missing closing quote\n", NULL);
	return (type);
}
