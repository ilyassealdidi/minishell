/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 18:40:28 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/23 18:58:46 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	exit_shell(t_object *obj)
{
	ft_lstclear(&obj->commands, destroy_command);
	ft_lstclear(&obj->env, destroy_env);
	rl_clear_history();
	printf("\033[F\033[2Cexit\n");
	exit(EXIT_SUCCESS);
}
