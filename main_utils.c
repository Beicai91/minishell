/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:48:32 by bcai              #+#    #+#             */
/*   Updated: 2024/05/18 22:08:27 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//struct termios	g_orig_termios;

void	initial_setup(t_m *m, char **envp)
{
	struct termios	new_termios;
	t_gl			*gl;

	init_global_var();
	gl = get_gl();
	m->envp = envp;
	m->exit_status = 0;
	m->position = ON_MAIN;
	init_envvars(envp, 0);
	tcgetattr(STDIN_FILENO, &gl->orig_termios);
	new_termios = gl->orig_termios;
	new_termios.c_lflag &= ~ECHOCTL;
	new_termios.c_cc[VERASE] = '\t';
	tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
}

void	partial_reinit_m(t_m *m)
{
	m->envp_path = NULL;
	m->path = NULL;
	m->heredoc_flag = 0;
	m->in = NULL;
	m->out = NULL;
	m->temp_list = NULL;
}

void	lastfree_restore(void)
{
	t_gl *gl;
	gl = get_gl();
	tcsetattr(STDIN_FILENO, TCSANOW, &gl->orig_termios);
	free_envvars();
	clear_history();
}

char	*expand_input_check(char *input, t_m *m)
{
	char	*temp;
	char	*original;

	original = input;
	while (*input != '\0')
	{
		if (*input == '<' || *input == '>')
		{
			m->j = 0;
			temp = find_pattern(original, m);
			if (temp != NULL)
			{
				temp = open_cd_in_out(temp, m);
				if (temp == NULL)
					return (NULL);
				original = merge_files_input(temp, original, m);
				input = original;
			}
			else
				return (original);
		}
		input++;
	}
	return (original);
}

char	*merge_files_input(char *t, char *in, t_m *m)
{
	int	i;

	i = 0;
	m->j = -1;
	m->k = -1;
	m->new = (char *)malloc(sizeof(char) * (ft_strlen(t) + ft_strlen(in)) + 1);
	if (m->new == NULL)
		return (NULL);
	while (in[i] != '\0' && in[i] != '>' && in[i] != '<')
		m->new[++m->j] = in[i++];
	while (t[++m->k] != '\0')
		m->new[++m->j] = t[m->k];
	while (in[i] != '\0')
	{
		if (i == m->i)
		{
			merge_files_loop(m, in, i);
			free(t);
			free(in);
			return (m->new);
		}
		m->new[m->j++] = in[i++];
	}
	return (m->new);
}
