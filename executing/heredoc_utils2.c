/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:50:13 by bcai              #+#    #+#             */
/*   Updated: 2024/05/22 13:16:29 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			while (*start && *start != ' ' && *start != '$')
				start++;
			var_name = ft_substr(target + 1, 0, start - target - 1);
			var_value = get_current_envvar(var_name);
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

	m.envp = heredoc->envp;
	init_envvars(heredoc->envp, 0);
	partial_reinit_m(&m);
	m.outcpy_emb = dup(STDOUT_FILENO);
	if (dup2(heredoc_fd, STDOUT_FILENO) == -1)
	{
		close(m.outcpy_emb);
		return ;
	}
	cmd = parsecmd(cmdline);
	last_set(cmd, &m);
	if (cmd != NULL)
	{
		traverse_tree(cmd, &m);
		free_tree(cmd, &m);
	}
	free(cmdline);
	if (dup2(m.outcpy_emb, STDOUT_FILENO) == -1)
	{
		close(m.outcpy_emb);
		return ;
	}
}
