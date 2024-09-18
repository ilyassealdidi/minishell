/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 10:59:11 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/18 16:29:15 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

string	join(string str1, string str2)
{
	string			joined;

	if (str2 == NULL)
		return (str1);
	if (str1 != NULL && *str1 != '\0' && *str2 == '\0')
		return (str1);
	if (*str2 == '\0')
	{
		str2 = ft_strdup("");
		if (str2 == NULL)
			return (free(str1), NULL);
	}
	joined = ft_strjoin(str1, str2);
	free(str1);
	free(str2);
	return (joined);
}
