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
	char	*s_token;//make a structure of se_tkn
	char	*e_token;
	t_cmd	*cmd;
	int		redir_type;
	int		file_type;

	s_token = NULL;
	e_token = NULL;
	cmd = subcmd;
	while (skipspace_peek(start, end, "<>") == true)
	{
		redir_type = gettoken(start, end, &s_token, &e_token);
		file_type = gettoken(start, end, &s_token, &e_token);
		//test
		printf("after gettoken to get file_type\nstart %c\nletter before start %c\ns_token %c\n e_token %c\n", **start, *(*start - 1), *s_token, *e_token);
		printf("redirtype %d, file_type %d\n", redir_type, file_type);
		//
		if (file_type == 127)
			return (NULL);
			//handle_error("Missing or invalid infile or outfile.", cmd);
		if (ft_strchr("<>+", redir_type) && file_type != 39 && file_type != 34)
			cmd = get_redircmd(cmd, s_token, e_token, redir_type);
		else if (ft_strchr("<>+", redir_type) && (file_type == 39 || file_type == 34))
		{
			cmd = get_redircmd(cmd, s_token + 1, e_token, redir_type);
			(*start)++;
		}
		else if (redir_type == 'h' && file_type != 39 && file_type != '"')
			cmd = (t_cmd *)heredoc_init(cmd, s_token, e_token - s_token + 1, 0);
		else if (redir_type == 'h' && (file_type == 39 || file_type == '"'))
			cmd = handle_quoted_delimiter(cmd, start, s_token + 1, e_token - 1);
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

t_cmd	*parseexec(char **start, char *end)
{
	char		*s_tkn;
	char		*e_tkn;
	t_execcmd	*execcmd;
	t_cmd		*cmd;
	int			type;

	if (skipspace_peek(start, end, "("))
		return (parseblock(start, end));
	s_tkn = NULL;
	e_tkn = NULL;
	execcmd = execcmd_init();
	cmd = parseredirs((t_cmd *)execcmd, start, end);
	while (**start && skipspace_peek(start, end, "&|);") == false)
	{
		//test
		printf("Before gettoken\nstart %c\n", **start);
		//
		type = gettoken(start, end, &s_tkn, &e_tkn);
		//test
		printf("After gettoken\nstart %c, letter before %c\ns_token %c\ne_token%c\n", **start, *(*start - 1), *s_tkn, *e_tkn);
		printf("type %d\n", type);
		//
		if (type == 127)
		{
			free_memory((t_cmd *)execcmd);
			return (NULL);
		}
		else if (type == 40)
		{
			free_memory((t_cmd *)execcmd);
			printf("minishell: syntax error near unexpected token\n");
			return (NULL);
		}
		else if (type == 39)
			cmdargs_quote(&execcmd->cmdargs, s_tkn + 1, e_tkn - 1, start);
			//single_quoted_args(&execcmd->cmdargs, execcmd, start, cmd);
		else if (type == 34)
			cmdargs_quote(&execcmd->cmdargs, s_tkn + 1, e_tkn - 1, start);
		else if (type == 97)
		{
			//test
			printf("Ready to populate not quoted cmdargs\n");
			//
			populate_cmdargs(&execcmd->cmdargs, s_tkn, e_tkn, cmd);
		}
		cmd = parseredirs(cmd, start, end);
	}
	get_cmd_args(execcmd, cmd);
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
