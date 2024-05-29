
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_envvar1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:48:54 by bcai              #+#    #+#             */
/*   Updated: 2024/05/27 21:49:19 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	special_cases(char *key, char *value)
{
	if (key[0] == '!')
	{
		printf("minishell: %s=%s: event not found\n", key, value);
		return (1);
	}
	if (key[0] == '#')
		return (1);
	return (0);
}

int	check_key_validity(char *key, char *value, int export_flag)
{
	int	i;

	if (ft_isdigit(key[0]) || ft_strchr("~@%*^", key[0]))
	{
		if (export_flag == 1)
			printf("minishell: export:'%s=%s': not a valid identifier\n", key, value);
		else
			printf("minishell: '%s=%s': not a valid identifier\n", key, value);
		return (1);
	}
	if (special_cases(key, value) == 1)
		return (1);
	i = 0;
	while (key[++i])
	{
		if (!ft_isdigit(key[i]) && !ft_isalpha(key[i]) && key[i] != '_')
		{
			if (export_flag == 1)
				printf("minishell: export: '%s=%s': not a valid identifier\n", key, value);
			else
				printf("minishell: '%s=%s': not a valid identifier\n", key, value);
			return (1);
		}
	}
	return (0);
}

void	add_envvar(char *key, char *value, int is_exported)
{
	t_envvar	*new;
	t_envvar	*temp;
	t_gl		*gl;

	if (check_key_validity(key, value, is_exported) == 1)
		return ;
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