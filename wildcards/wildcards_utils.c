/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:52:26 by bcai              #+#    #+#             */
/*   Updated: 2024/05/22 17:16:15 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	merge_files_loop(t_m *m, char *input, int i, char *temp)
{
	int	a;

	a = 0;
	m->k = 0;
	while (input[i + m->k] != '\0')
	{
		if (i == m->i)
		{
			if (input[i] == '<' || input[i] == '>')
				m->k++;
			while (input[i + m->k] == ' ')
				m->k++;
			while (input[i + m->k] != ' ' && input[i + m->k] != '\0')
				m->k++;
			while (temp[a] != '\0')
			{
				m->new[m->j++] = temp[a++];
			}
		}
		m->new[m->j++] = input[i++ + m->k];
	}
	m->new[m->j] = '\0';
}

int	check_if_pattern(char *input, int i)
{
	while (input[i] != '\0' && i >= 0)
	{
		while (input[i] != ' ')
			i--;
		while (input[i] == ' ')
			i--;
		if (input[i] == '<' || input[i] == '>')
			return (i);
	}
	return (0);
}

char	*find_pattern(char *input, t_m *m)
{
	char	*pattern;

	pattern = (char *)malloc(sizeof(char) * ft_strlen(input));
	if (!pattern)
		return (NULL);
	m->pattern_new = pattern;
	m->i = 0;
	m->star = 0;
	f(input, m, pattern);
	if (m->star == 1)
		return (m->pattern_new);
	free(pattern);
	return (NULL);
}

char	*f(char *input, t_m *m, char *pattern)
{
	while (*input && *input != '\0')
	{
		if (*input == '<' || *input == '>')
		{
			set_up_signs(input, m);
			while (*(input + m->j) == ' ')
				m->j++;
			while (*(input + m->j) != ' ' && *(input + m->j) != '\0')
			{
				if (*(input + m->j) == '*')
					m->star = 1;
				*pattern = *(input + m->j++);
				pattern++;
			}
			*pattern = '\0';
			if (m->star == 1)
				return (m->pattern_new);
			pattern = m->pattern_new;
			m->j = 0;
		}
		m->i++;
		input++;
	}
	return (NULL);
}

void	set_up_signs(char *input, t_m *m)
{
	m->j++;
	if (*input == '<')
		m->sign = '<';
	if (*input == '>')
		m->sign = '>';
}
