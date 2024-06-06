/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:46:08 by bcai              #+#    #+#             */
/*   Updated: 2024/06/04 17:53:16 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	resize_or_free(char *buffer, t_m *m, size_t *size)
{
	free(buffer);
	if (errno == ERANGE)
		(*size) = (*size) * 2;
	else
	{
		perror("getcmd");
		free_tree(m->final_tree, m);
		lastfree_restore();
		free(m->home_cpy);
		exit(1);
	}
}

void	set_oldpwd(t_m *m, char *add_pwd)
{
	t_gl	*gl;
	t_list	*ptr;

	gl = get_gl();
	ptr = gl->oldpwd_list;
	if (gl->oldpwd_list == NULL || ft_strcmp((char *)ptr->content,
			add_pwd) != 0)
		build_files_list(&gl->oldpwd_list, add_pwd);
	if (gl->oldpwd_list->next != NULL)
	{
		update_envvars(ft_strdup("OLDPWD"),
			ft_strdup(gl->oldpwd_list->next->content), 1);
	}
	if (m->start == 1)
	{
		free(add_pwd);
		add_pwd = NULL;
		m->start = 2;
	}
}

void	update_pwd(t_m *m)
{
	char	*cwd;
	char	*buffer;
	size_t	size;

	size = 1024;
	while (1)
	{
		buffer = safe_malloc(size, CHAR, m->final_tree);
		cwd = getcwd(buffer, size);
		if (cwd)
		{
			free(buffer);
			break ;
		}
		else
			resize_or_free(buffer, m, &size);
	}
	update_envvars(ft_strdup("PWD"), ft_strdup(cwd), 1);
	set_oldpwd(m, cwd);
}

void	cd_back_case(t_m *m)
{
	t_gl	*gl;

	gl = get_gl();
	if (gl->oldpwd_list->next == NULL)
	{
		printf("cd: OLDPWD not set\n");
		return ;
	}
	update_envvars(ft_strdup("PWD"), ft_strdup(get_envvar("OLDPWD")->value), 1);
	if (chdir(gl->oldpwd_list->next->content) != 0)
		perror("cd: ");
	set_oldpwd(m, gl->oldpwd_list->next->content);
}

void	builtin_cd(t_cmd *cmd, t_m *m)
{
	char		**cmd_args;

	cmd_args = ((t_execcmd *)cmd)->cmd_args;
	if (cmd_args[1] == NULL || ft_strcmp(cmd_args[1], "~") == 0)
	{
		if (chdir(m->home_cpy) != 0)
			perror("cd: ");
	}
	else if (ft_strcmp(cmd_args[1], "-") == 0)
	{
		cd_back_case(m);
		return ;
	}
	else
	{
		if (chdir(cmd_args[1]) != 0)
		{
			perror("cd: ");
			m->exit_status = 1;
		}
	}
	update_pwd(m);
}
