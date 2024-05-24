/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:07:19 by bcai              #+#    #+#             */
/*   Updated: 2024/05/17 11:07:29 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*parsecmd(char *input)
{
	t_cmd	*cmd;
	char	*start;
	char	*end;

	start = input;
	if (ft_strlen(input) == 0)
		return (NULL);
	end = input + ft_strlen(input);
	cmd = parselist(&start, end);
	if (start != end)
	{
		handle_error("Invalid command line.", cmd);
		return (NULL);
	}
	return (cmd);
}

t_cmd	*parselist(char **start, char *end)
{
	t_cmd	*cmd;
	t_cmd	*right_cmd;
	char	*s_token;
	char	*e_token;

	cmd = parse_and_or(start, end);
	if (**start == ';')
	{
		gettoken(start, end, &s_token, &e_token);
		right_cmd = parselist(start, end);
		cmd = (t_cmd *)listcmd_init(cmd, right_cmd);
	}
	return (cmd);
}

t_cmd	*parse_and_or(char **start, char *end)
{
	t_cmd	*cmd;
	t_cmd	*right_cmd;
	char	*s_token;
	char	*e_token;

	cmd = parsepipe(start, end);
	if (**start == '&' && *(*start + 1) == '&')
	{
		gettoken(start, end, &s_token, &e_token);
		right_cmd = parse_and_or(start, end);
		cmd = (t_cmd *)andcmd_init(cmd, right_cmd);
	}
	else if (**start == '|' && *(*start + 1) == '|')
	{
		gettoken(start, end, &s_token, &e_token);
		right_cmd = parse_and_or(start, end);
		cmd = (t_cmd *)orcmd_init(cmd, right_cmd);
	}
	return (cmd);
}

t_cmd	*parsepipe(char **start, char *end)
{
	t_cmd	*cmd;
	t_cmd	*right_cmd;
	char	*s_token;
	char	*e_token;

	cmd = parseexec(start, end);
	if (**start == '|' && *(*start + 1) != '|')
	{
		gettoken(start, end, &s_token, &e_token);
		right_cmd = parsepipe(start, end);
		cmd = (t_cmd *)pipecmd_init(cmd, right_cmd);
	}
	return (cmd);
}
