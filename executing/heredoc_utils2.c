/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:50:13 by bcai              #+#    #+#             */
/*   Updated: 2024/05/18 18:32:46 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_update(char **start, char *target, int heredoc_fd)
{
	while (*start < target)
	{
		write(heredoc_fd, *start, 1);
		(*start)++;
	}
	(*start)++;
}

static void	execute_cmdline_update(char **start, char *target, int heredoc_fd,
		t_heredoc *heredoc)
{
	char	*cmd_line;

	while (**start && **start != ')')
		(*start)++;
	if (!**start)
		handle_error("Parsing error: miss closing parenthesis",
			(t_cmd *)heredoc);
	cmd_line = ft_substr(target + 2, 0, *start - target - 2);
	embedded_cmdline(cmd_line, heredoc_fd, heredoc);
}

void	expand_env_cmd(char *start, char *target, int heredoc_fd,
		t_heredoc *heredoc)
{
	char	*var_name;
	char	*var_value;

	while (*start)
	{
		write_update(&start, target, heredoc_fd);
		if (*start == '(')
			execute_cmdline_update(&start, target, heredoc_fd, heredoc);
		else if (*start)
		{
			while (*start && *start != ' ')
				start++;
			var_name = ft_substr(target + 1, 0, start - target - 1);
			var_value = get_exported_envvar(var_name);
			free(var_name);
			write(heredoc_fd, var_value, ft_strlen(var_value));
			target = start;
			while (*target && (*target != '$' || (*target == '$' && (*(target
								+ 1) == ' ' || *(target + 1) == '\0'))))
				target++;
		}
	}
	write(heredoc_fd, "\n", 1);
}

void	embedded_cmdline(char *cmdline, int heredoc_fd, t_heredoc *heredoc)
{
	t_m		m;
	t_cmd	*cmd;
	int		fd_cpy;

	m.envp = heredoc->envp;
	init_envvars(heredoc->envp, 0);
	partial_reinit_m(&m);
	fd_cpy = dup(STDOUT_FILENO);
	if (dup2(heredoc_fd, STDOUT_FILENO) == -1)
	{
		close(fd_cpy);
		return ;
	}
	cmd = parsecmd(cmdline);
	if (cmd != NULL)
	{
		traverse_tree(cmd, &m);
		free_tree(cmd, &m);
	}
	free(cmdline);
	if (dup2(fd_cpy, STDOUT_FILENO) == -1)
	{
		close(fd_cpy);
		return ;
	}
}
