/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:49:26 by bcai              #+#    #+#             */
/*   Updated: 2024/05/17 12:45:14 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig_indicator = 0;

void	no_line_expansion(t_heredoc *heredoc, int heredoc_fd, t_m *m)
{
	char				*line;
	struct sigaction	sa;

	signal_tracking(&sa, m);
	line = ft_readline("heredoc>", m);
	while ((line) != NULL)
	{
		if (g_sig_indicator != 0)
		{
			free(line);
			break ;
		}
		if (ft_strncmp(line, heredoc->delimiter,
				ft_strlen(heredoc->delimiter)) == 0)
		{
			free(line);
			break ;
		}
		write(heredoc_fd, line, ft_strlen(line));
		write(heredoc_fd, "\n", 1);
		free(line);
		line = NULL;
		line = ft_readline("heredoc>", m);
	}
}

static char	*get_target(char *line, int *env_cmd)
{
	char	*temp;
	char	*target;

	target = NULL;
	temp = line;
	while (*temp)
	{
		if (*temp == '$' && *(temp + 1) != ' ' && *(temp + 1) != '\0')
		{
			*env_cmd = 1;
			target = temp;
			break ;
		}
		temp++;
	}
	return (target);
}

static void	write_line(int heredoc_fd, char *line)
{
	write(heredoc_fd, line, ft_strlen(line));
	write(heredoc_fd, "\n", 1);
}

void	expand_line(t_heredoc *heredoc, int heredoc_fd, t_m *m)
{
	char				*line;
	int					env_cmd;
	char				*target;
	struct sigaction	sa;

	env_cmd = 0;
	signal_tracking(&sa, m);
	line = ft_readline("heredoc>", m);
	while (line != NULL)
	{
		if (g_sig_indicator != 0 || ft_strncmp(line, heredoc->delimiter,
				ft_strlen(heredoc->delimiter)) == 0)
		{
			free(line);
			break ;
		}
		target = get_target(line, &env_cmd);
		if (env_cmd == 0)
			write_line(heredoc_fd, line);
		else
			expand_env_cmd(line, target, heredoc_fd, heredoc);
		free(line);
		line = NULL;
		line = ft_readline("heredoc>", m);
	}
}
