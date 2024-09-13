/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:45:38 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/11 20:53:01 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	print_env(t_list *head)
{
	t_list			*node;
	t_environment	*env;
	int				list_size;

	list_size = ft_lstsize(head);
	node = head;
	while (list_size--)
	{
		env = node->content;
		if (env->hidden == false)
		{
			ft_printf("declare -x %s", env->element.key);
			if (env->element.value != NULL)
				ft_printf("=\"%s\"", env->element.value);
			ft_printf("\n");
		}
		node = node->next;
		if (node == NULL)
			node = head;
	}
}

static bool	is_valid_identifier(char *str)
{
	int	i;

	if (!ft_isalpha(*str) && *str != '_')
		return (INVALID);
	i = 1;
	while (str[i])
	{
		if (str[i] == '=' || ft_strncmp(&str[i], "+=", 2) == 0)
			break ;
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (INVALID);
		i++;
	}
	return (VALID);
}

//update the function's name
static int	set_dict(t_dictionnary *dict, char *env, char *equal)
{
	if (equal == NULL)
	{
		dict->key = ft_strdup(env);
		if (dict->key == NULL)
			return (FAILURE);
		dict->value = NULL;
	}
	else
	{
		dict->key = ft_substr(env, 0, equal - (equal[-1] == '+') - env);
		char *todup = ft_strchr(env, '=') + 1;
		dict->value = ft_strdup(todup);
		if (dict->key == NULL || dict->value == NULL)
			return (destroy_dictionnary(dict), FAILURE);
	}
	return (SUCCESS);
}

static int	export_env(t_object *obj, char *arg)
{
	t_dictionnary	dict;
	char			*equal;

	equal = ft_strchr(arg, '=');
	if (set_dict(&dict, arg, equal) == FAILURE)
		return (FAILURE);
	if (equal != NULL && equal[-1] == '+'
		&& append_env(&obj->env, dict) == FAILURE)
		return (destroy_dictionnary(&dict), FAILURE);
	else if (set_env(&obj->env, dict) == FAILURE)
		return (destroy_dictionnary(&dict), FAILURE);
	destroy_dictionnary(&dict);
	return (SUCCESS);
}

int	builtin_export(t_object *obj, t_command *cmd)
{
	int				i;

	i = 1;
	if (cmd->argc == 1)
		return (print_env(obj->env), SUCCESS);
	while (cmd->argv[i])
	{
		if (is_valid_identifier(cmd->argv[i]) == INVALID)
		{
			ft_error(EXPORT, cmd->argv[i], EMNVI);
			obj->exit_status = 1;
		}
		else if (export_env(obj, cmd->argv[i]) == FAILURE)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}
