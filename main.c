/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:04:02 by bcai              #+#    #+#             */
/*   Updated: 2024/06/06 13:40:16 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lastset_run(t_m *m)
{
	last_set(m->final_tree, m);
	runcmd(m->final_tree, m);
}

int	main(int argc, char **argv, char **envp)
{
	t_m					m;
	struct sigaction	sa;

	(void)argc;
	(void)argv;
	initial_setup(&m, envp);
	while (1)
	{
		signal_tracking(&sa, &m);
		m.input = readline("minishell$ ");
		if (!m.input)
		{
			lastfree_restore();
			free(m.home_cpy);
			exit(1);
		}
		add_history(m.input);
		update_history_file(&m);
		m.input = expand_input_check(m.input, &m);
		partial_reinit_m(&m);
		m.final_tree = parsecmd(m.input, &m);
		if (m.final_tree != NULL)
			lastset_run(&m);
		free(m.input);
	}
}
