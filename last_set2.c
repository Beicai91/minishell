/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_set2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 13:08:01 by eprzybyl          #+#    #+#             */
/*   Updated: 2024/05/30 18:04:36 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_newstr(char *temp, char *e_cpy, t_m *m, char *first_part)
{
	t_strvars	v;

	if (*(temp + 1) == '?')
	{
		v.var_value = ft_itoa(m->exit_status);
		v.new = minishell_strjoin(first_part, v.var_value, NULL);
		free(v.var_value);
		v.rest = m_sub(temp + 2, 0, e_cpy - temp - 1, NULL);
	}
	else
	{
		get_strlen(temp, &(v.i));
		v.var_value = getvalue_freename(ft_substr(temp, 1, v.i));
		v.new = minishell_strjoin(first_part, v.var_value, NULL);
		if (*(v.var_value) == '\0')
			free(v.var_value);
		if (!*temp)
			v.rest = strdup("");
		else
			v.rest = m_sub(temp + v.i + 1, 0, e_cpy - temp - v.i, NULL);
	}
	free(first_part);
	v.new = join_free_all(v.new, v.rest, NULL);
	return (v.new);
}

void	update_temp(char **temp)
{
	while (**temp && (**temp != '$' || (**temp == '$' && (*(*temp
						+ 1) == ' ' || *(*temp + 1) == '\0' || *(*temp
						+ 1) == '"' || *(*temp + 1) == '$'))))
		(*temp)++;
}

char	*replace_dollar(char *original, t_m *m)
{
	char	*temp;
	char	*s_cpy;
	char	*e_cpy;
	char	*first_part;
	char	*new;

	new = NULL;
	temp = original;
	s_cpy = temp;
	e_cpy = temp + ft_strlen(temp) - 1;
	while (*temp && *(temp + 1))
	{
		update_temp(&temp);
		first_part = m_sub(s_cpy, 0, temp - s_cpy, NULL);
		new = get_newstr(temp, e_cpy, m, first_part);
		temp = new;
		update_temp(&temp);
		s_cpy = new;
		e_cpy = new + ft_strlen(new) - 1;
	}
	if (!new)
		new = ft_strdup(original);
	return (new);
}
