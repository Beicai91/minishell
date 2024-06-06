/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_envvar1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:48:54 by bcai              #+#    #+#             */
/*   Updated: 2024/05/30 10:28:15 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*itoa_free(char *value)
{
	char	*res;

	res = ft_itoa(ft_atoi(value) + 1);
	free(value);
	return (res);
}

void	init_envvars(char **envp, int i, t_m *m)
{
	char	*key;
	char	*value;
	char	*equal;
	t_gl	*gl;

	gl = get_gl();
	if (gl->env_vars != NULL)
		return ;
	if (!envp[i])
	{
		fill_basic_envvars();
		return ;
	}
	while (envp[i] != NULL)
	{
		equal = ft_strchr(envp[i], '=');
		key = ft_substr(envp[i], 0, equal - envp[i]);
		value = ft_substr(equal + 1, 0, ft_strlen(equal + 1));
		if (ft_strcmp(key, "SHLVL") == 0)
			value = itoa_free(value);
		if (ft_strcmp(key, "HOME") == 0)
			m->home_cpy = ft_strdup(value);
		add_envvar(key, value, 1);
		i++;
	}
}

t_envvar	*getter(void)
{
	t_gl	*gl;

	gl = get_gl();
	return (gl->env_vars);
}

void	minishell_envp(t_m *m)
{
	t_envvar	*temp;
	int			len;
	t_strvars	v;

	temp = getter();
	len = 0;
	while (temp != NULL)
	{
		len++;
		temp = temp->next;
	}
	m->minishell_envp = malloc(sizeof(char *) * (len + 1));
	if (!m->minishell_envp)
		return ;
	v.i = 0;
	temp = getter();
	while (temp != NULL)
	{
		v.first_part = ft_strjoin(temp->key, "=");
		m->minishell_envp[v.i] = ft_strjoin(v.first_part, temp->value);
		free(v.first_part);
		temp = temp->next;
		(v.i)++;
	}
	m->minishell_envp[v.i] = NULL;
}

void	remove_envvar(char *key)
{
	t_envvar	*temp;
	t_envvar	*after_target;
	t_envvar	*previous;
	t_gl		*gl;

	gl = get_gl();
	temp = gl->env_vars;
	while (temp != NULL && ft_strncmp(temp->key, key, cmplen(temp->key,
				key)) != 0)
	{
		previous = temp;
		temp = temp->next;
	}
	if (temp)
	{
		after_target = temp->next;
		previous->next = after_target;
		free(temp->key);
		temp->key = NULL;
		free(temp->value);
		temp->value = NULL;
		free(temp);
		temp = NULL;
	}
	return ;
}
