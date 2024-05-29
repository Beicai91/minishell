/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_readline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:46:27 by bcai              #+#    #+#             */
/*   Updated: 2024/05/22 10:04:43 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	t_gl			*gl;

	gl = get_gl();
	tcgetattr(STDIN_FILENO, &gl->orig_termios);
	raw = gl->orig_termios;
	raw.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}

int readline_helper(t_m *m, int return_pressed, t_gl *gl)
{
    if (return_pressed == 1 && m->one_ch[0] == '\004')
    {
        tcsetattr(STDIN_FILENO, TCSANOW, &gl->orig_termios);
        return (1);
    }
    else if (return_pressed == 0 && m->one_ch[0] == '\004')
    {
        return (0);
    }
    else if (m->one_ch[0] == '\177')
        m->line = delete_char(m->line);
    else
    {
        m->line = join_free(m->line, m->one_ch);
        write(STDOUT_FILENO, m->one_ch, 1);
    }
    return (0);
}

char    *ft_readline(char *prompt, t_m *m)
{
    t_gl    *gl;
    int     return_pressed;

    gl = get_gl();
    return_pressed = 1;
    m->one_ch = safe_malloc(2, CHAR, NULL);
    m->line = ft_strdup("");
    write(STDOUT_FILENO, prompt, ft_strlen(prompt));
    set_raw_mode();
    while (read(STDIN_FILENO, m->one_ch, 1) == 1 && ft_strncmp(m->one_ch, "\n",
            1) != 0 && g_sig_indicator == 0)
    {
        if (ft_isalpha(m->one_ch[0]) || ft_isdigit(m->one_ch[0])
            || m->one_ch[0] == ' ' || m->one_ch[0] == '\t')
            return_pressed = 0;
        m->one_ch[1] = '\0';
        if (readline_helper(m, return_pressed, gl) == 1)
            return (NULL);
    }
    write(STDOUT_FILENO, "\n", 1);
    tcsetattr(STDIN_FILENO, TCSANOW, &gl->orig_termios);
    free(m->one_ch);
    return (m->line);
}

/*
char	*ft_readline(char *prompt, t_m *m)
{
	t_gl	*gl;

	gl = get_gl();
	m->one_ch = safe_malloc(2, CHAR, NULL);
	m->line = ft_strdup("");
	write(STDOUT_FILENO, prompt, ft_strlen(prompt));
	set_raw_mode();
	while (read(STDIN_FILENO, m->one_ch, 1) == 1 && ft_strncmp(m->one_ch, "\n",
			1) != 0 && g_sig_indicator == 0)
	{
		m->one_ch[1] = '\0';
		if (m->one_ch[0] == '\004')
		{
			tcsetattr(STDIN_FILENO, TCSANOW, &gl->orig_termios);
			return (NULL);
		}
		if (m->one_ch[0] == '\177')
			m->line = delete_char(m->line);
		else
		{
			m->line = join_free(m->line, m->one_ch);
			write(STDOUT_FILENO, m->one_ch, 1);
		}
	}
	write(STDOUT_FILENO, "\n", 1);
	tcsetattr(STDIN_FILENO, TCSANOW, &gl->orig_termios);
	free(m->one_ch);
	return (m->line);
}*/
