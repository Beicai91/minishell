/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdstruct_init1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:55:41 by bcai              #+#    #+#             */
/*   Updated: 2024/05/17 11:26:48 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_execcmd	*execcmd_init(void)
{
	t_execcmd	*execcmd;

	execcmd = (t_execcmd *)safe_malloc(1, EXEC, NULL);
	execcmd->type = EXEC;
	execcmd->cmd_args = NULL;
	execcmd->cmdargs = NULL;
	execcmd->path_prob = 0;
	execcmd->qflags = NULL;
	return (execcmd);
}

t_redircmd	*redircmd_init(t_cmd *subcmd, char *s_token, size_t size)
{
	t_redircmd	*redircmd;

	redircmd = (t_redircmd *)safe_malloc(1, REDIR, subcmd);
	redircmd->type = REDIR;
	redircmd->cmd = subcmd;
	redircmd->file = safe_malloc(size, CHAR, (t_cmd *)redircmd);
	ft_strlcpy(redircmd->file, s_token, size);
	return (redircmd);
}

void	init_mode_fd(t_redircmd *rcmd, int mode, int fd)
{
	rcmd->mode = mode;
	rcmd->fd = fd;
}

t_heredoc	*heredoc_init(t_cmd *subcmd, char *s_token, size_t size, int fd)
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
