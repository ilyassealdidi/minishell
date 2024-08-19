/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 20:41:13 by ialdidi           #+#    #+#             */
/*   Updated: 2024/08/19 12:25:43 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>



static bool	contains_command(t_list *head)
{
	t_token	*token;
	t_list	*tmp;

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

void	update_token_type(t_list *head, t_token *new)
{
	t_token	*last;

	if (new->type == REDIR_IN || new->type == HEREDOC
		|| new->type == PIPE || new->type == REDIR_OUT
		|| new->type == APPEND)
		return ;
	last = get_last_token(head);
	if (last != NULL && last->type == HEREDOC)
		new->type = DELIMITER;
	else if (last != NULL && last->type == REDIR_IN)
		new->type = INFILE;
	else if (head != NULL && (last->type == REDIR_OUT || last->type == APPEND))
		new->type = OUTFILE;
	else if (new->content && is_builtin(new->content) && contains_command(head) == false)
		new->type = BUILTIN;
	else if (new->type == ARG && contains_command(head) == false)
		new->type = CMD;
	else if ((head == NULL || last->type == PIPE) && new->type == ARG)
		new->type = CMD;
}
