/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:06:33 by bcai              #+#    #+#             */
/*   Updated: 2024/06/05 22:29:42 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_type(char **start, char *end)
{
	int	type;

	if (**start == '(' || **start == ')')
		type = get_blocktype(start);
	else if (**start == ';')
		type = **start;
	else if (**start == '|' && *(*start + 1) != '|')
		type = **start;
	else if (**start == 39)
		type = get_squotetype(start, end);
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
	int		type;
	t_gl	*gl;

	gl = get_gl();
	while (*start < end && ft_strchr(gl->spaces, **start) && **start != '"')
		(*start)++;
	*s_token = *start;
	type = get_type(start, end);
	*e_token = *start;
	while (*start < end && ft_strchr(gl->spaces, **start))
		(*start)++;
	return (type);
}

bool	skipspace_peek(char **start, char *end, char *check)
{
	t_gl	*gl;

	gl = get_gl();
	while (*start < end && ft_strchr(gl->spaces, **start))
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

t_cmd	*quoted_delimiter(t_cmd *cmd, char **start, char *s_token,
		char *e_token)
{
	t_heredoc	*res;

	res = hdinit(cmd, s_token, e_token - s_token + 2, 0);
	change_quotestat(&res);
	(*start)++;
	return ((t_cmd *)res);
}
