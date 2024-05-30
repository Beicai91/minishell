/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:07:19 by bcai              #+#    #+#             */
/*   Updated: 2024/05/30 13:42:21 by bcai             ###   ########.fr       */
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
	{
		printf("Invalid command line\n");
		m->exit_status = 127;
	}
	return (cmd);
}

t_cmd	*parselist(char **start, char *end, t_m *m)
{
	t_cmd	*cmd;
	t_cmd	*right_cmd;
	//char	*s_token;
	//char	*e_token;

	cmd = parse_and_or(start, end, m);
	if (**start == ';')
	{
		if (cmd == NULL)
		{
			printf("Left: Invalide command line\n");
			return (NULL);
		}
		(*start)++;
		//test
		//printf("in right part fo parselist start %c after start %c\n", **start, *(*start + 1));
		//
		//gettoken(start, end, &s_token, &e_token);
		right_cmd = parselist(start, end, m);
		if (right_cmd == NULL)
		{
			//printf("Right: Invalid command line\n");
			return (NULL);
		}
		cmd = (t_cmd *)listcmd_init(cmd, right_cmd);
	}
	return (cmd);
}

t_cmd	*parse_and_or(char **start, char *end, t_m *m)
{
	t_cmd	*cmd;
	t_cmd	*right_cmd;
	char	*s_token;
	char	*e_token;

	cmd = parsepipe(start, end, m);
	if (**start == '&' && *(*start + 1) == '&')
	{
		gettoken(start, end, &s_token, &e_token);
		right_cmd = parse_and_or(start, end, m);
		cmd = (t_cmd *)andcmd_init(cmd, right_cmd);
	}
	else if (**start == '|' && *(*start + 1) == '|')
	{
		gettoken(start, end, &s_token, &e_token);
		right_cmd = parse_and_or(start, end, m);
		cmd = (t_cmd *)orcmd_init(cmd, right_cmd);
	}
	else if (**start == '&' && *(*start + 1) != '&')
	{
		free_memory(cmd);
		return (NULL);
	}
	//test
	//if (cmd == NULL)
		//printf("after parsepipe, return NULL\n");
	//
	return (cmd);
}

t_cmd	*parsepipe(char **start, char *end, t_m *m)
{
	t_cmd	*cmd;
	t_cmd	*right_cmd;
	char	*s_token;
	char	*e_token;

	cmd = parseexec(start, end, m);
	//test
	//if (cmd != NULL)
		//printf("After parseexec cmd not NULL, start %c\n", **start);
	//

	if (**start == '|' && *(*start + 1) != '|')
	{
		if (((t_execcmd *)cmd)->cmdargs == NULL)
			return (NULL);
		gettoken(start, end, &s_token, &e_token);
		//test
		//printf("after gettoken start %c\n", **start);
		//
		if (*start == end)
		{
			//test
			//printf("detected incomplete pipe\n");
			//
			free_memory(cmd);
			return (NULL);
		}
		right_cmd = parsepipe(start, end, m);
		cmd = (t_cmd *)pipecmd_init(cmd, right_cmd);
	}
	//test
	//if (cmd != NULL)
		//printf("After parseexec, start %c\n", **start);
	//
	return (cmd);
}
