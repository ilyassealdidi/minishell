/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 09:59:45 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/19 09:34:13 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_array(char **strs)
{
	int				i;

	if (!strs)
		return ;
	i = 0;
	while (strs[i] != NULL)
		free(strs[i++]);
	free(strs);
}
