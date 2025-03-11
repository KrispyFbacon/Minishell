/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 19:01:28 by frbranda          #+#    #+#             */
/*   Updated: 2025/03/11 12:42:55 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_quotes(char *input, int *i, int *start, int *mode)
{
	char	quote;
	
	if (input[*i] == '\'' || input[*i] == '\"')
	{
		quote = input[*i];
		if (*mode == GENERAL && quote == '\'')
			*mode = SINGLE_QUO;
		else if (*mode == GENERAL && quote == '\"')
			*mode = DOUBLE_QUO;
		(*i)++;
		*start = *i;
		while (input[*i] && input[*i] != quote)
			(*i)++;
		if (input[*i] == quote)
		{
			*mode = GENERAL;
			(*i)++;
		}
	}
}

void	add_token_word(t_token **token_list, char *input, int start, int i)
{
	t_token	*new_token;
	char	*s;
	int	len;

	while (start < i && ft_strchr(WHITE_SPACES, input[start]))
		start++;
	while (i > start && ft_strchr(WHITE_SPACES, input[i - 1]))
		i--;
	len = i - start;
	if (len <= 0)
		return;
	s = (char *)ft_calloc((len + 1), sizeof(char));
	if (!s)
		return ;
	len = 0;
	while (start < i)
	{
		s[len] = input [start];
		start++;
		len++;
	}
	s[len] = '\0';
	new_token = initialize_token(s, CMD);
	add_last_token(token_list, new_token);
	free (s);
}
void	add_token(t_token **token_list, char *input, int i, t_stupid *info)
{
	t_token	*new_token;
	char	*s;
	int	len;
	int	j;

	len = i - (info->start);
	s = (char *)ft_calloc((len + 1), sizeof(char));
	if (!s)
		return ;
	j = 0;
	while (info->start < i)
	{
		s[j] = input [info->start];
		info->start++;
		j++;
	}
	s[j] = '\0';
	new_token = initialize_token(s, info->type);
	add_last_token(token_list, new_token);
	free (s);
}

void	handle_token_redir(t_token **token_list, char *input, int *i)
{
	t_stupid	info;
	int	mode;

	info.type = get_token_type(input, *i);
	if (info.type == 0)
		return ;
	if (info.type == REDIR_IN || info.type == REDIR_OUT)
		(*i)++;
	else if (info.type == APPEND || info.type == HEREDOC)
		*i = *i + 2;
	while (input[*i] && ft_strchr(WHITE_SPACES, input[*i]))
		(*i)++;
	mode = GENERAL;
	info.start = *i;
	while (input[*i] && !(ft_strchr(WHITE_SPACES, input[*i])
		&& !(ft_strchr(S_REDIR, input[*i]))))
		(*i)++;
	if (*i > info.start)
		add_token(token_list, input, *i, &info);
}

void	handle_token_pipe(t_token **token_list, char *input, int *i)
{
	t_stupid	info;
	
	if (input[*i] == '|')
	{
		info.type = PIPE;
		info.start = *i;
		add_token(token_list, input, *i + 1, &info);
		(*i)++;
	}
}