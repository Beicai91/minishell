/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:06:33 by bcai              #+#    #+#             */
/*   Updated: 2024/05/17 13:02:58 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		g_whitespace[] = " \t\r\n\v";

int	get_type(char **start, char *end)
{
	int	type;

	if ((**start == '|' && *(*start + 1) != '|') || **start == ';'
		|| **start == '(' || **start == ')')
	{
		type = **start;
		(*start)++;
	}
	else if (**start == 39)
		type = **start;
	else if (**start == '"')
		type = get_quotetype(start, end);
	else if (**start == '<')
		type = get_intype(start);
	else if (**start == '>')
		type = get_outtype(start);
	else if (**start == '&')
		type = get_andtype(start);
	else if (**start == '|' && *(*start + 1) == '|')
		type = get_ortype(start);
	else
		type = get_atype(start, end);
	return (type);
}

int	gettoken(char **start, char *end, char **s_token, char **e_token)
{
	int	type;

	while (*start < end && ft_strchr(g_whitespace, **start))
		(*start)++;
	*s_token = *start;
	type = get_type(start, end);
	*e_token = *start;
	while (*start < end && ft_strchr(g_whitespace, **start))
		(*start)++;
	return (type);
}

bool	skipspace_peek(char **start, char *end, char *check)
{
	while (*start < end && ft_strchr(g_whitespace, **start))
		(*start)++;
	if (**start && ft_strchr(check, **start))
		return (true);
	else
		return (false);
}

static void	change_quotestat(t_heredoc **heredoc)
{
	(*heredoc)->is_quoted = 1;
	return ;
}

t_cmd	*handle_quoted_delimiter(t_cmd *cmd, char **start, char *end,
		int file_type)
{
	char		*s_token;
	char		*e_token;
	t_heredoc	*res;

	(*start)++;
	s_token = *start;
	while (**start && file_type == 39 && **start != 39)
		(*start)++;
	while (**start && file_type == '"' && **start != '"')
		(*start)++;
	if (!**start)
		handle_error("Missing closing quote for delimiter\n", cmd);
	e_token = *start - 1;
	res = heredoc_init(cmd, s_token, e_token - s_token + 2, 0);
	change_quotestat(&res);
	(*start)++;
	skipspace_peek(start, end, NULL);
	return ((t_cmd *)res);
}
