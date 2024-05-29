/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:08:48 by bcai              #+#    #+#             */
/*   Updated: 2024/05/22 13:31:03 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_sig_set(struct sigaction *sa)
{
	sigemptyset(&(sa->sa_mask));
	sa->sa_flags = SA_SIGINFO;
	sa->sa_sigaction = handle_sigint;
	sigaction(SIGINT, sa, NULL);
	sigemptyset(&(sa->sa_mask));
	sa->sa_flags = 0;
	sa->sa_handler = SIG_IGN;
	sigaction(SIGQUIT, sa, NULL);
}

void	heredoc_sig_set(struct sigaction *sa)
{
	sigemptyset(&(sa->sa_mask));
	sa->sa_flags = SA_SIGINFO;
	sa->sa_sigaction = handle_sigint_heredoc;
	sigaction(SIGINT, sa, NULL);
	sigemptyset(&(sa->sa_mask));
	sa->sa_flags = 0;
	sa->sa_handler = SIG_IGN;
	sigaction(SIGQUIT, sa, NULL);
}

void	exec_sig_set(struct sigaction *sa)
{
	sigemptyset(&(sa->sa_mask));
	sa->sa_flags = SA_SIGINFO;
	sa->sa_sigaction = handle_sigint_exec;
	sigaction(SIGINT, sa, NULL);
	sigemptyset(&(sa->sa_mask));
	sa->sa_flags = 0;
	sa->sa_sigaction = handle_sigquit_exec;
	sigaction(SIGQUIT, sa, NULL);
}

void	signal_tracking(struct sigaction *sa, t_m *m)
{
	init_gl_var();
	if (m->position == ON_MAIN)
		main_sig_set(sa);
	else if (m->position == ON_HEREDOC)
		heredoc_sig_set(sa);
	else if (m->position == ON_EXEC)
		exec_sig_set(sa);
}
