/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_envvar1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:48:54 by bcai              #+#    #+#             */
/*   Updated: 2024/05/17 13:31:44 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_envvar	*g_env_vars = NULL;

void	init_envvars(char **envp)
{
	int		i;
	char	*key;
	char	*value;
	char	*equal;

	if (g_env_vars != NULL)
		return ;
	i = 0;
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

	new = malloc(sizeof(t_envvar) * 1);
	if (!new)
		return ;
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	free(key);
	free(value);
	new->is_exported = is_exported;
	new->next = NULL;
	if (!g_env_vars)
	{
		g_env_vars = new;
		return ;
	}
	temp = g_env_vars;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
}

void	update_envvars(char *key, char *value, int is_exported)
{
	int			modify;
	t_envvar	*temp;
	t_envvar	*target;

	modify = 0;
	temp = g_env_vars;
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

	temp = g_env_vars;
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
	return (g_env_vars);
}
