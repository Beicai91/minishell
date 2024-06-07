/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdstruct_init1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:55:41 by bcai              #+#    #+#             */
/*   Updated: 2024/06/05 22:26:13 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_execcmd	*execcmd_init(t_m *m)
{
	t_execcmd	*execcmd;

	execcmd = (t_execcmd *)safe_malloc(1, EXEC, NULL);
	execcmd->type = EXEC;
	execcmd->cmd_args = NULL;
	execcmd->cmdargs = NULL;
	execcmd->path_prob = 0;
	execcmd->qflags = NULL;
	execcmd->cqflags = NULL;
	execcmd->m = m;
	return (execcmd);
}

t_redircmd	*redircmd_init(t_cmd *subcmd, char *s_token, size_t size)
{
	int			escape_flag;
	size_t		i;
	t_redircmd	*redircmd;

	redircmd = (t_redircmd *)safe_malloc(1, REDIR, subcmd);
	redircmd->type = REDIR;
	redircmd->cmd = subcmd;
	escape_flag = 0;
	i = 0;
	while (i < size)
	{
		if (s_token[i] == '\\')
			escape_flag = 1;
		i++;
	}
	if (escape_flag == 1)
		redircmd->file = safe_malloc(size - 1, CHAR, (t_cmd *)redircmd);
	else
		redircmd->file = safe_malloc(size, CHAR, (t_cmd *)redircmd);
	ft_strlcpy_special(redircmd->file, s_token, size);
	return (redircmd);
}

void	init_mode_fd(t_redircmd *rcmd, int mode, int fd)
{
	rcmd->mode = mode;
	rcmd->fd = fd;
}

t_heredoc	*hdinit(t_cmd *subcmd, char *s_token, size_t size, int fd)
{
	t_heredoc	*heredoc;

	heredoc = (t_heredoc *)safe_malloc(1, HEREDOC, subcmd);
	heredoc->type = HEREDOC;
	heredoc->cmd = subcmd;
	heredoc->delimiter = safe_malloc(size, CHAR, (t_cmd *)heredoc);
	ft_strlcpy(heredoc->delimiter, s_token, size);
	heredoc->fd = fd;
	heredoc->is_quoted = 0;
	heredoc->tmp_file = NULL;
	return (heredoc);
}
