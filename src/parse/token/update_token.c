/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 20:41:13 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/27 19:26:02 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	contains_command(t_list *head)
{
	t_token			*token;
	t_list			*tmp;

	tmp = ft_lstlast(head);
	while (tmp)
	{
		token = tmp->content;
		if (token->type == PIPE)
			return (false);
		if (token->type == CMD || token->type == BUILTIN)
			return (true);
		tmp = tmp->previous;
	}
	return (false);
}

static void	update_token_type(t_list *head, t_token *new)
{
	t_token			*last;

	last = get_last_token(head);
	if (is_expandable(new) && !is_quoted(new) && new->content != NULL
		&& ft_strchr(" \t", new->content[0]) && last != NULL
		&& !is_operator(last) && isset(last->content)
		&& ft_strlen(last->content) != 0 && is_joinable(last))
		set_token_state(last, JOINABLE, false);
	if (is_expandable(new) && !is_quoted(new) && new->content
		&& ft_strchr(" \t", new->content[ft_strlen(new->content) - 1]))
		set_token_state(new, JOINABLE, false);
	if (last != NULL && last->type == HEREDOC)
		new->type = DELIMITER;
	else if (last != NULL && is_redir(last))
		new->type = FILENAME;
	else if (new->content
		&& isbuiltin(new->content) && contains_command(head) == false)
		new->type = BUILTIN;
	else if (new->type == ARG && contains_command(head) == false)
		new->type = CMD;
	else if ((isnull(head) || last->type == PIPE) && new->type == ARG)
		new->type = CMD;
}

void	update_token(t_list *head, t_token *new)
{
	if (!is_redir(new) && new->type != PIPE)
		update_token_type(head, new);
}
