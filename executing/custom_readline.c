/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_readline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:46:27 by bcai              #+#    #+#             */
/*   Updated: 2024/05/18 21:22:27 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct termios	g_orig_termios;

char	*delete_char(char *line)
{
	char	*temp;

	temp = line;
	if (ft_strlen(line) > 0)
	{
		temp = ft_substr(line, 0, ft_strlen(line) - 1);
		free(line);
		write(STDOUT_FILENO, "\b \b", 3);
	}
	return (temp);
}

void	clean_exit(char *one_char, t_m *m)
{
	free(one_char);
	unlink("heredoc_tmp");
	free_list(&(m->in));
	free_list(&(m->out));
	free(m->input);
	free_tree(m->final_tree, m);
	free_envvars();
	lastfree_restore();
	exit(1);
}

void	set_raw_mode(void)
{
	struct termios	raw;

	tcgetattr(STDIN_FILENO, &g_orig_termios);
	raw = g_orig_termios;
	raw.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}

char	*ft_readline(char *prompt, t_m *m)
{
	char	*line;
	char	*one_char;

	one_char = safe_malloc(2, CHAR, NULL);
	line = ft_strdup("");
	write(STDOUT_FILENO, prompt, ft_strlen(prompt));
	set_raw_mode();
	while (read(STDIN_FILENO, one_char, 1) == 1 && ft_strncmp(one_char, "\n",
			1) != 0 && g_sig_indicator == 0)
	{
		one_char[1] = '\0';
		if (one_char[0] == '\004')
			clean_exit(one_char, m);
		if (one_char[0] == '\177')
			line = delete_char(line);
		else
		{
			line = join_free(line, one_char);
			write(STDOUT_FILENO, one_char, 1);
		}
	}
	write(STDOUT_FILENO, "\n", 1);
	tcsetattr(STDIN_FILENO, TCSANOW, &g_orig_termios);
	free(one_char);
	return (line);
}
