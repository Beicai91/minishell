/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_envvars3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:03:16 by bcai              #+#    #+#             */
/*   Updated: 2024/05/22 10:06:26 by bcai             ###   ########.fr       */
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
