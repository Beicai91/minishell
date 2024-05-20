/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_envvar1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:48:54 by bcai              #+#    #+#             */
/*   Updated: 2024/05/18 21:57:14 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	resize(char *buffer, size_t *size)
{
	free(buffer);
	if (errno == ERANGE)
		(*size) = (*size) * 2;
	else
	{
		perror("getcmd");
		free_envvars();
		exit(1);
	}
}

void	fill_basic_envvars()
{
	char	*buffer;
	size_t	size;
	char	*cwd;
	
	size = 1024;
	while (1)
	{
		buffer = safe_malloc(size, CHAR, NULL);
		cwd = getcwd(buffer, size);
		if (cwd)
			break ;
		else
			resize(buffer, &size);
	}
	add_envvar(ft_strdup("PWD"), ft_strdup(cwd), 1);
	free(buffer);
	add_envvar(ft_strdup("PATH"), ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:."), 0);
	add_envvar(ft_strdup("SHLVL"), ft_strdup("1"), 1);
	add_envvar(ft_strdup("_"), ft_strdup("/usr/bin/env"), 1);
}

void	init_envvars(char **envp, int i)
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
		add_envvar(key, value, 1);
		i++;
	}
}

void	add_envvar(char *key, char *value, int is_exported)
{
	t_envvar	*new;
	t_envvar	*temp;
	t_gl		*gl;

	gl = get_gl();
	new = malloc(sizeof(t_envvar) * 1);
	if (!new)
		return ;
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	free(key);
	free(value);
	new->is_exported = is_exported;
	new->next = NULL;
	if (!gl->env_vars)
	{
		gl->env_vars = new;
		return ;
	}
	temp = gl->env_vars;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
}

void	update_envvars(char *key, char *value, int is_exported)
{
	int			modify;
	t_envvar	*temp;
	t_envvar	*target;
	t_gl		*gl;

	gl = get_gl();
	modify = 0;
	temp = gl->env_vars;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->key, key, cmplen(temp->key, key)) == 0)
		{
			modify = 1;
			target = temp;
		}
		temp = temp->next;
	}
	if (modify == 1)
		update_target(target, value, key, is_exported);
	else
		add_envvar(key, value, is_exported);
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

t_envvar	*getter(void)
{
	t_gl	*gl;

	gl = get_gl();
	return (gl->env_vars);
}
