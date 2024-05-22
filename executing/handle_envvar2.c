/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_envvar2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:49:11 by bcai              #+#    #+#             */
/*   Updated: 2024/05/22 10:05:05 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cmplen(char *lst_key, char *key)
{
	int	cmp_len;

	if (ft_strlen(lst_key) > ft_strlen(key))
		cmp_len = ft_strlen(lst_key);
	else
		cmp_len = ft_strlen(key);
	return (cmp_len);
}

void	update_target(t_envvar *target, char *value, char *key, int is_exported)
{
	free(target->value);
	target->value = NULL;
	target->value = ft_strdup(value);
	target->is_exported = is_exported;
	free(value);
	free(key);
}

t_envvar	*get_envvar(char *key)
{
	t_envvar	*temp;

	temp = getter();
	while (temp != NULL)
	{
		if (ft_strncmp(temp->key, key, cmplen(temp->key, key)) == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

void	print_envvars(void)
{
	t_envvar	*temp;

	temp = getter();
	while (temp)
	{
		if (temp->is_exported == 1)
			printf("%s=%s\n", temp->key, temp->value);
		temp = temp->next;
	}
}

void	free_envvars(void)
{
	t_envvar	*envvars;
	t_envvar	*temp;

	envvars = getter();
	while (envvars)
	{
		temp = envvars;
		envvars = envvars->next;
		free(temp->key);
		temp->key = NULL;
		free(temp->value);
		temp->value = NULL;
		free(temp);
		temp = NULL;
	}
}
