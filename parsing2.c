/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:30:54 by bcai              #+#    #+#             */
/*   Updated: 2024/05/17 13:15:41 by eprzybyl         ###   ########.fr       */
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
		tkn.redir = gettoken(start, end, &(tkn.s_tkn), &(tkn.e_tkn));
		tkn.file = gettoken(start, end, &(tkn.s_tkn), &(tkn.e_tkn));
		if (tkn.file == 127)
			return (NULL);
		if (ft_strchr("<>+", tkn.redir) && tkn.file != 39 && tkn.file != 34)
			cmd = get_redircmd(cmd, tkn.s_tkn, tkn.e_tkn, tkn.redir);
		else if (ft_strchr("<>+", tkn.redir) && (tkn.file == 39 || tkn.file == 34))
		{
			cmd = get_redircmd(cmd, tkn.s_tkn + 1, tkn.e_tkn, tkn.redir);
			(*start)++;
		}
		else if (tkn.redir == 'h' && tkn.file != 39 && tkn.file != '"')
			cmd = (t_cmd *)heredoc_init(cmd, tkn.s_tkn, tkn.e_tkn - tkn.s_tkn + 1, 0);
		else if (tkn.redir == 'h' && (tkn.file == 39 || tkn.file == '"'))
			cmd = handle_quoted_delimiter(cmd, start, tkn.s_tkn + 1, tkn.e_tkn - 1);
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

static t_cmd	*parseexec_error(int type, t_cmd *cmd)
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
		return (NULL);
	}
	return (NULL);
}

t_cmd	*parseexec(char **start, char *end)
{
	char		*s_tkn;//use t_tkn struct
	char		*e_tkn;
	t_execcmd	*ecmd;
	t_cmd		*cmd;

	if (skipspace_peek(start, end, "("))
		return (parseblock(start, end));
	s_tkn = NULL;
	e_tkn = NULL;
	ecmd = execcmd_init();
	cmd = parseredirs((t_cmd *)ecmd, start, end);
	while (**start && skipspace_peek(start, end, "&|);") == false)
	{
		ecmd->tkn_type = gettoken(start, end, &s_tkn, &e_tkn);
		if (ecmd->tkn_type == 127 || ecmd->tkn_type == 40)
			return (parseexec_error(ecmd->type, cmd));
		else if (ecmd->tkn_type == 39)
			cmdargs_quote(ecmd, s_tkn + 1, e_tkn - 1, start);
		else if (ecmd->tkn_type == 34)
			cmdargs_quote(ecmd, s_tkn + 1, e_tkn - 1, start);
		else if (ecmd->tkn_type == 97)
			populate_cmdargs(ecmd, s_tkn, e_tkn, cmd);
		cmd = parseredirs(cmd, start, end);
	}
	get_cmd_args(ecmd, cmd);
	return (cmd);
}

t_cmd	*parseblock(char **start, char *end)
{
	t_cmd	*cmd;
	char	*s_token;
	char	*e_token;

	s_token = NULL;
	e_token = NULL;
	gettoken(start, end, &s_token, &e_token);
	cmd = parselist(start, end);
	if (**start != ')')
		handle_error("Missing closing parenthesis.", cmd);
	gettoken(start, end, &s_token, &e_token);
	cmd = parseredirs(cmd, start, end);
	return (cmd);
}
