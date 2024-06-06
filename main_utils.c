/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:48:32 by bcai              #+#    #+#             */
/*   Updated: 2024/06/04 18:46:36 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initial_setup(t_m *m, char **envp)
{
	struct termios	new_termios;
	t_gl			*gl;

	gl = get_gl();
	m->envp = envp;
	m->exit_status = 0;
	m->position = ON_MAIN;
	m->line = NULL;
	m->export_hidden = 0;
	m->pipe_left_flag = 0;
	m->pipe_right_flag = 0;
	m->redir_out = 0;
	init_envvars(envp, 0, m);
	tcgetattr(STDIN_FILENO, &gl->orig_termios);
	new_termios = gl->orig_termios;
	new_termios.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
	update_working_history(m);
	update_envvars(ft_strdup("OLDPWD"), ft_strdup("  "), 1);
	m->start = 0;
}

void	partial_reinit_m(t_m *m)
{
	m->envp_path = NULL;
	m->path = NULL;
	m->heredoc_flag = 0;
	m->in = NULL;
	m->out = NULL;
	m->temp_list = NULL;
	m->stop_executing = 0;
}

void	lastfree_restore(void)
{
	t_gl	*gl;

	gl = get_gl();
	tcsetattr(STDIN_FILENO, TCSANOW, &gl->orig_termios);
	free_envvars();
	clear_history();
	free(gl->signs);
	free(gl->spaces);
	free_t_list(&gl->oldpwd_list);
	free(gl);
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
					return (original);
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
	m->j = 0;
	m->k = 0;
	m->new = (char *)malloc(sizeof(char) * (ft_strlen(t) + ft_strlen(in)) + 1);
	if (m->new == NULL)
		return (NULL);
	while (in[i] != '\0')
	{
		if (in[i] == '<' || in[i] == '>')
		{
			merge_files_loop(m, in, i, t);
			free(t);
			free(in);
			return (m->new);
		}
		m->new[m->j++] = in[i++];
	}
	return (m->new);
}
