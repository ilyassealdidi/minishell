/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 19:30:50 by ialdidi           #+#    #+#             */
/*   Updated: 2024/08/24 16:37:24 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	print_invalid_error(char *arg)
{
	ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
}

static bool	is_valid_identifier(char *str)
{
	int	i;

	if (!ft_isalpha(*str) && *str != '_')
		return (INVALID);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (INVALID);
		i++;
	}
	return (VALID);
}

int	builtin_unset(t_object *obj, t_command *command)
{
	int	i;

	i = 1;
	while (command->argv[i])
	{
		if (is_valid_identifier(command->argv[i]) == INVALID)
		{
			print_invalid_error(command->argv[i]);
			obj->exit_status = 1;
		}
		else
			unset_env(&obj->env, command->argv[i]);
		i++;
	}
	return (SUCCESS);
}
