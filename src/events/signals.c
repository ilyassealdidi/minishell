/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 18:45:48 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/08 01:06:39 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	interrupt(int sig)
{
	g_received_signal++;
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	init_signals(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, interrupt);
	signal(SIGQUIT, SIG_IGN);
}
