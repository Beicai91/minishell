/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:30:54 by bcai              #+#    #+#             */
/*   Updated: 2024/06/05 22:34:31 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*parseredirs(t_cmd *subcmd, char **start, char *end)
{
	t_tkn	tkn;
	t_cmd	*cmd;

	tkn.s_tkn = NULL;
	tkn.e_tkn = NULL;
	cmd = subcmd;
	while (skipspace_peek(start, end, "<>") == true)
	{
		tkn.rdr = gettoken(start, end, &(tkn.s_tkn), &(tkn.e_tkn));
		tkn.fl = gettoken(start, end, &(tkn.s_tkn), &(tkn.e_tkn));
		if (tkn.rdr == 127 || tkn.fl == 127)
			return (NULL);
		if (ft_strchr("<>+", tkn.rdr) && tkn.fl != 39 && tkn.fl != 34)
			cmd = get_redircmd(cmd, tkn.s_tkn, tkn.e_tkn, tkn.rdr);
		else if (ft_strchr("<>+", tkn.rdr) && (tkn.fl == 39 || tkn.fl == 34))
		{
			cmd = get_redircmd(cmd, tkn.s_tkn + 1, tkn.e_tkn, tkn.rdr);
			(*start)++;
		}
		else if (tkn.rdr == 'h' && tkn.fl != 39 && tkn.fl != '"')
			cmd = (t_cmd *)hdinit(cmd, tkn.s_tkn, tkn.e_tkn - tkn.s_tkn + 1, 0);
		else if (tkn.rdr == 'h' && (tkn.fl == 39 || tkn.fl == '"'))
			cmd = quoted_delimiter(cmd, start, tkn.s_tkn + 1, tkn.e_tkn - 1);
	}
	return (cmd);
}

t_cmd	*get_redircmd(t_cmd *cmd, char *s_token, char *e_token, int redir_type)
{
	t_cmd	*res;

	res = NULL;
	if (redir_type == '<')
	{
		res = (t_cmd *)redircmd_init(cmd, s_token, e_token - s_token + 1);
		init_mode_fd((t_redircmd *)res, O_RDONLY, 0);
	}
	else if (redir_type == '>')
	{
		res = (t_cmd *)redircmd_init(cmd, s_token, e_token - s_token + 1);
		init_mode_fd((t_redircmd *)res, O_WRONLY | O_CREAT | O_TRUNC, 1);
	}
	else if (redir_type == '+')
	{
		res = (t_cmd *)redircmd_init(cmd, s_token, e_token - s_token + 1);
		init_mode_fd((t_redircmd *)res, O_WRONLY | O_CREAT | O_APPEND, 1);
	}
	return (res);
}

static t_cmd	*parseexec_error(int type, t_cmd *cmd, t_m *m)
{
	if (type == 127)
	{
		free_memory(cmd);
		return (NULL);
	}
	else if (type == 40)
	{
		free_memory(cmd);
		printf("minishell: syntax error near unexpected token\n");
		m->exit_status = 258;
		return (NULL);
	}
	return (NULL);
}

t_cmd	*parseexec(char **start, char *end, t_m *m)
{
	t_tkn		tkn;
	t_execcmd	*ecmd;
	t_cmd		*cmd;

	if (skipspace_peek(start, end, "("))
		return (parseblock(start, end, m));
	tkn.s_tkn = NULL;
	tkn.e_tkn = NULL;
	ecmd = execcmd_init(m);
	cmd = parseredirs((t_cmd *)ecmd, start, end);
	while (**start && skipspace_peek(start, end, "&|);") == false)
	{
		ecmd->tkn_type = gettoken(start, end, &(tkn.s_tkn), &(tkn.e_tkn));
		if (ecmd->tkn_type == 127 || ecmd->tkn_type == 40)
			return (parseexec_error(ecmd->tkn_type, cmd, m));
		else if (ecmd->tkn_type == 39)
			cmdargs_quote(ecmd, tkn.s_tkn + 1, tkn.e_tkn - 1, start);
		else if (ecmd->tkn_type == 34)
			cmdargs_quote(ecmd, tkn.s_tkn + 1, tkn.e_tkn - 1, start);
		else if (ecmd->tkn_type == 97)
			populate_cmdargs(ecmd, tkn.s_tkn, tkn.e_tkn - 1, cmd);
		cmd = parseredirs(cmd, start, end);
	}
	get_cmd_args(ecmd, cmd);
	return (cmd);
}

t_cmd	*parseblock(char **start, char *end, t_m *m)
{
	t_cmd	*cmd;
	char	*s_token;
	char	*e_token;

	s_token = NULL;
	e_token = NULL;
	gettoken(start, end, &s_token, &e_token);
	cmd = parselist(start, end, m);
	if (**start != ')')
	{
		handle_error("Missing closing parenthesis.", cmd);
		return (NULL);
	}
	gettoken(start, end, &s_token, &e_token);
	cmd = parseredirs(cmd, start, end);
	return (cmd);
}
