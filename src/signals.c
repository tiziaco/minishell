/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiacovel <tiacovel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:47:53 by tiacovel          #+#    #+#             */
/*   Updated: 2024/03/11 17:09:57 by tiacovel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/commands.h"

void	sigint_handler(int num)
{
	(void)num;
	ft_printf("\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sigquit_handler(int num)
{
	(void)num;
	ft_printf("Quit: 3\n", 1);
}

void	init_signals(t_data *data)
{
	t_term	term;

	term = data->term;
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	//signal(SIGQUIT, sigquit_handler);
}
