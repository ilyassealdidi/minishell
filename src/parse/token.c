/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 21:22:32 by ialdidi           #+#    #+#             */
/*   Updated: 2024/06/05 21:46:36 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_token_type	get_token_type(char *str)
{
	if (ft_strncmp(str, ">>", 2) == 0)
		return (APPEND);
	if (ft_strncmp(str, "<<", 2) == 0)
		return (HEREDOC);
	if (ft_strncmp(str, "|", 1) == 0)
		return (PIPE);
	if (ft_strncmp(str, ">", 1) == 0)
		return (REDIR_OUT);
	if (ft_strncmp(str, "<", 1) == 0)
		return (REDIR_IN);
	if (((*str == '\'' || *str == '"') && ft_strchr(str + 1, *str))
		|| (ft_isprint(*str) && (*str != '\'' && *str != '"')))
		return (ARG);
	return (NONE);
}

bool	is_expandable(char *str)
{
	char	*dollar_sign;

	dollar_sign = ft_strchr(str + (*str == '"'), '$');
	if (dollar_sign == NULL)
		return (false);
	if (*str == '"' && ft_strchr(str + 1, '"') < dollar_sign)
		return (false);
	if (*str != '"' && str + ft_strcspn(str, " |><'\"") < dollar_sign) /**/
		return (false);
	if (ft_isalpha(*(dollar_sign + 1)) || *(dollar_sign + 1) == '?')
			return (true);
	return (false);
}

static int	get_token_length(char *line, t_token_type type)
{
	if (type == PIPE || type == REDIR_IN || type == REDIR_OUT)
		return (1);
	else if (type == HEREDOC || type == APPEND)
		return (2);
	else if (*line == '"' || *line == '\'')
		return (ft_strchr(line + 1, *line) - line - 1);
	else
		return (ft_strcspn(line, " |><'\""));
}

static int	set_next_token(char **line, t_token *token)
{
	int					len;

	token->type = get_token_type(*line);
	if (token->type == NONE)
		return (ERROR);
	len = get_token_length(*line, token->type);
	token->is_expandable = is_expandable(*line);
	token->content = ft_substr(*line, (**line == '"' || **line == '\''), len);
	if (token->content == NULL)
		return (FAILURE);
	*line += len + (**line == '"' || **line == '\'') * 2;
	token->is_joinable = ft_strchr(" |><", **line) == NULL && **line != '\0'
		&& token->type == ARG;
	return (SUCCESS);
}

int	tokens_init(t_list **tokens, char *line)
{
	int					ret;
	t_token				token;
	
	while (*line != '\0')
	{
		while (*line == ' ')
			line++;
		if (*line == '\0')
			break ;
		ft_memset(&token, 0, sizeof(t_token));
		ret = set_next_token(&line, &token);
		if (ret != SUCCESS)
			return (ret);
		if (ft_appendtoken(tokens, &token) == FAILURE)
				return (free(token.content), FAILURE);
	}
	if (is_valid_syntax(*tokens) == ERROR)
		return (ERROR);
	return (SUCCESS);
}