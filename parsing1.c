/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:07:19 by bcai              #+#    #+#             */
/*   Updated: 2024/06/05 23:03:49 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*parsecmd(char *input, t_m *m)
{
	t_cmd	*cmd;
	char	*start;
	char	*end;

	start = input;
	if (ft_strlen(input) == 0)
		return (NULL);
	end = input + ft_strlen(input);
	cmd = parselist(&start, end, m);
	if (cmd == NULL)
		m->exit_status = 258;
	return (cmd);
}

t_cmd	*parselist(char **start, char *end, t_m *m)
{
	t_cmd	*cmd;
	t_cmd	*right_cmd;

	cmd = parse_and_or(start, end, m);
	if (**start == ';')
	{
		if (cmd == NULL)
			return (NULL);
		(*start)++;
		right_cmd = parselist(start, end, m);
		if (right_cmd == NULL)
			return (NULL);
		cmd = (t_cmd *)listcmd_init(cmd, right_cmd);
		if (right_cmd == NULL)
			return (NULL);
	}
	return (cmd);
}

t_cmd	*handle_orcmd(char **start, char *end, t_m *m, t_cmd *left_cmd)
{
	t_cmd	*cmd;
	t_cmd	*right_cmd;
	char	*s_token;
	char	*e_token;

	gettoken(start, end, &s_token, &e_token);
	right_cmd = parse_and_or(start, end, m);
	cmd = (t_cmd *)orcmd_init(left_cmd, right_cmd);
	if (right_cmd == NULL)
		return (NULL);
	return (cmd);
}

t_cmd	*handle_andcmd(char **start, char *end, t_m *m, t_cmd *left_cmd)
{
	t_cmd	*cmd;
	t_cmd	*right_cmd;
	char	*s_token;
	char	*e_token;

	gettoken(start, end, &s_token, &e_token);
	right_cmd = parse_and_or(start, end, m);
	cmd = (t_cmd *)andcmd_init(left_cmd, right_cmd);
	if (right_cmd == NULL)
		return (NULL);
	return (cmd);
}

t_cmd	*parse_and_or(char **start, char *end, t_m *m)
{
	t_cmd	*cmd;

	cmd = parsepipe(start, end, m);
	if (cmd == NULL)
		return (NULL);
	if (**start == '&' && *(*start + 1) == '&' && *(*start + 2) != '\0')
		return (handle_andcmd(start, end, m, cmd));
	else if (**start == '|' && *(*start + 1) == '|' && *(*start + 2) != '\0')
		return (handle_orcmd(start, end, m, cmd));
	else if ((**start == '&' && *(*start + 1) == '&' && *(*start + 2) == '\0')
		|| (**start == '|' && *(*start + 1) == '|' && *(*start + 2) == '\0'))
	{
		printf("minishell: syntaxt error: unexpected end of file\n");
		free_memory(cmd);
		return (NULL);
	}
	else if (**start == '&' && *(*start + 1) != '&')
	{
		printf("minishell: syntax error: unexpected token &\n");
		free_memory(cmd);
		return (NULL);
	}
	return (cmd);
}
