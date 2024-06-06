/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_envvar4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:03:16 by bcai              #+#    #+#             */
/*   Updated: 2024/06/06 09:23:50 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	fill_basic_envvars(void)
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
	add_envvar(ft_strdup("PATH"), \
		ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:."), 0);
	add_envvar(ft_strdup("SHLVL"), ft_strdup("1"), 1);
	add_envvar(ft_strdup("_"), ft_strdup("/usr/bin/env"), 1);
}

int	update_envvars(char *key, char *value, int is_exported)
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
	{
		update_target(target, value, key, is_exported);
		return (0);
	}
	else
		return (add_envvar(key, value, is_exported));
}
