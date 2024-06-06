/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:49:26 by bcai              #+#    #+#             */
/*   Updated: 2024/06/06 09:35:07 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

volatile sig_atomic_t	g_sig_indicator = 0;

int	event(void)
{
	return (0);
}

void	no_line_expansion(t_heredoc *hd, int heredoc_fd, t_m *m)
{
	char				*line;
	struct sigaction	sa;

	signal_tracking(&sa, m);
	rl_event_hook = event;
	while (1)
	{
		line = readline("heredoc>");
		if (g_sig_indicator != 0)
		{
			free(line);
			break ;
		}
		if (!line)
			break ;
		if (ft_strcmp(line, hd->delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(heredoc_fd, line, ft_strlen(line));
		write(heredoc_fd, "\n", 1);
		free(line);
		line = NULL;
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
	rl_event_hook = event;
	while (1)
	{
		line = readline("heredoc>");
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
	}
}
