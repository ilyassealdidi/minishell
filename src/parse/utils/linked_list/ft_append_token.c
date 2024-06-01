/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 20:27:38 by ialdidi           #+#    #+#             */
/*   Updated: 2024/06/01 17:02:02 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_appendtoken(t_list **head, t_token *token)
{
	t_list	*new;

	new = ft_lstnew(token);
	if (!new)
		return (0);
	ft_lstadd_back(head, new);
	return (1);
}
