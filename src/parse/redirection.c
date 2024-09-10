/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 00:14:37 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/11 00:18:27 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	redir_init(t_list *node, t_command *command)
{
	t_token			*token;
	char			*filename;

	token = get_token(node);
	filename = get_token(node->next)->content;
	if (token->type == REDIR_IN)
	{
		if (command->in != 0)
			close(command->in);
		command->in = open(filename, O_RDONLY);
	}
	if (token->type == APPEND || token->type == REDIR_OUT)
	{
		if (command->out != 1)
			close(command->out);
		if (token->type == APPEND)
			command->out = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			command->out = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (command->in == -1 || command->out == -1)
		return (ft_error(NULL, filename, NULL), FAILURE);
	return (SUCCESS);
}
