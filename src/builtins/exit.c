/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 19:35:37 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/28 20:52:54 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static long	get_number(const char *str)
{
	long			num;
	int				sign;
	int				i;

	i = 0;
	num = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		sign = 1 - 2 * (str[i++] == '-');
	while (ft_isdigit(str[i]))
	{
		if (num == LONG_MAX / 10 && str[i] - '0' == 8 && sign == -1
			&& !ft_isdigit(str[i + 1]))
			return (LONG_MIN);
		if (((num == LONG_MAX / 10 && str[i] - '0' > 7)
				|| num > LONG_MAX / 10))
			return (errno = ERANGE, LONG_MAX + (sign == -1));
		num = num * 10 + str[i++] - '0';
	}
	if ((str[i] && !ft_isdigit(str[i]))
		|| (!ft_isdigit(str[i]) && i > 0 && !ft_isdigit(str[i - 1])))
		errno = EINVAL;
	return (num * sign);
}

static void	ft_exit(t_object *obj, int status)
{
	ft_lstclear(&obj->commands, destroy_command);
	ft_lstclear(&obj->env, destroy_env);
	rl_clear_history();
	exit(status);
}

int	builtin_exit(t_object *obj, t_command *command)
{
	unsigned char	nb;
	t_string		value;

	nb = 0;
	if (ft_lstsize(obj->commands) == 1)
		ft_dprintf(STDERR_FILENO, "exit\n");
	if (command->argc >= 2)
	{
		value = ft_strtrim(command->argv[1], " \t");
		if (isnull(value))
			return (FAILURE);
		errno = 0;
		nb = get_number(value);
		free(value);
		if (errno != 0)
		{
			ft_error(B_EXIT, command->argv[1], EMNAR);
			ft_exit(obj, -1);
		}
		if (command->argc > 2)
			return (ft_error(B_EXIT, NULL, EMTMA), FAILURE);
	}
	ft_exit(obj, nb);
	return (SUCCESS);
}
