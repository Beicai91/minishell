/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 12:36:53 by eprzybyl          #+#    #+#             */
/*   Updated: 2024/05/24 16:31:26 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_gl	*init_gl_var(void)
{
	static t_gl		*gl;
	struct termios	orig_termios;

	if (gl)
		return (gl);
	gl = (t_gl *)malloc(sizeof(t_gl));
	if (!gl)
		return (NULL);
	tcgetattr(STDIN_FILENO, &orig_termios);
	gl->orig_termios = orig_termios;
	gl->spaces = ft_strdup(" \t\r\n\v");
	gl->signs = ft_strdup("<|>;()");
	gl->env_vars = NULL;
	gl->oldpwd_list = NULL;
	return (gl);
}

t_gl	*get_gl(void)
{
	static t_gl		*gl;

	if (!gl)
		gl = init_gl_var();
	return (gl);
}
