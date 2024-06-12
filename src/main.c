/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:46:25 by ialdidi           #+#    #+#             */
/*   Updated: 2024/06/11 18:24:31 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int argc, char **argv, char **env)
{
	t_object			obj;
	char				*rl;
	int					status;

	atexit(func);
	if (argc != 1)
		return (ft_printf("Usage: ./minishell\n"), 1);
	ft_memset(&obj, 0, sizeof(t_object));
	while (1)
	{
		if (argv[1])
			rl = ft_strdup("echo $PATH$");
		else
			rl = readline(YELLOW"Minishell$ "RESET);
		if (!rl)
			continue ;
		status = parse(rl, &obj);
		if (*rl != '\0')
			add_history(rl);
		free(rl);
		ft_lstclear(&obj.tokens, free_token);
	}
	return ((void)argc, 0);
}
