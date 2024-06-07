/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 13:05:12 by eprzybyl          #+#    #+#             */
/*   Updated: 2024/06/05 22:58:05 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_atype(char **start, char *end)
{
	int		type;
	t_gl	*gl;

	gl = get_gl();
	type = 'a';
	while (*start < end && **start != '"' && **start != 39)
	{
		if ((ft_strchr(gl->signs, **start) || ft_strchr(gl->spaces, **start))
			&& *(*start - 1) != '\\')
			break ;
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
	{
		printf("Missing closing quote\n");
		return (127);
	}
	return (type);
}

int	get_squotetype(char **start, char *end)
{
	int	type;

	type = **start;
	(*start)++;
	while (*start < end && **start != 39)
		(*start)++;
	if (**start != 39)
	{
		printf("Missing closing quote\n");
		return (127);
	}
	return (type);
}

int	get_ortype(char **start)
{
	int	type;

	type = '=';
	*start = *start + 2;
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
