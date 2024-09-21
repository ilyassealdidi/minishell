/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 16:46:33 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/21 16:59:14 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	is_valid_syntax(t_list *tokens)
{
	t_token			*current;
	t_token			*next;

	if (is_operator(get_last_token(tokens)) || get_token(tokens)->type == PIPE)
		return (ERROR);
	while (tokens->next)
	{
		current = tokens->content;
		next = tokens->next->content;
		if (current->type != PIPE)
		{
			if (is_operator(current) && is_operator(next))
				return (ERROR);
		}
		tokens = tokens->next;
	}
	return (SUCCESS);
}

int	tokens_init(t_object *obj, t_string line)
{
	int				ret;
	t_token			token;

	while (*line != '\0')
	{
		ret = set_token(&line, &token);
		if (ret != SUCCESS)
			return (ft_lstclear(&obj->tokens, destroy_token), ret);
		if ((is_expandable(&token) && expand(obj, &token) == FAILURE)
			|| ft_appendtoken(obj, &token) == FAILURE)
			return (free(token.content),
				ft_lstclear(&obj->tokens, destroy_token), FAILURE);
		while (*line != '\0' && (*line == ' ' || *line == '\t'))
			line++;
	}
	if (obj->tokens && is_valid_syntax(obj->tokens) == ERROR)
		return (ft_lstclear(&obj->tokens, destroy_token), ERROR);
	return (SUCCESS);
}
