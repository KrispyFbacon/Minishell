/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 19:01:28 by frbranda          #+#    #+#             */
/*   Updated: 2025/03/25 15:21:52 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_token(t_token **token_list, char *input, int i, t_info *info)
{
	t_token	*new_token;
	char	*s;
	int		len;
	int		j;

	len = i - info->start;
	if (len == 0 && !(info->type >= REDIR_IN && info->type <= HEREDOC))
		return ;
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

void	token_end_of_word(char *input, int *i, t_info *info)
{
	char	quote;

	if (info->mode == SINGLE_QUO && input[*i] == '\'')
	{
		quote = input[*i];
		(*i)++;
		while (input[*i] && input[*i] != quote)
			(*i)++;
		if (input[*i] == quote)
			(*i)++;
	}
	else if (info->mode == DOUBLE_QUO && input[*i] == '\"')
	{
		quote = input[*i];
		(*i)++;
		while (input[*i] && input[*i] != quote)
			(*i)++;
		if (input[*i] == quote)
			(*i)++;
	}
	else if (info->mode == GENERAL)
		while (input[*i] && !(ft_strchr(SPECIAL, input[*i])))
			(*i)++;
}

void	token_quote_changer(char *input, int i, t_info *info)
{
	if (input[i] == '\'')
	{
		if (info->mode == GENERAL)
			info->mode = SINGLE_QUO;
		else if (info->mode == SINGLE_QUO)
			info->mode = GENERAL;
	}
	if (input[i] == '\"')
	{
		if (info->mode == GENERAL)
			info->mode = DOUBLE_QUO;
		else if (info->mode == DOUBLE_QUO)
			info->mode = GENERAL;
	}
}

void	token_quote_handler(char *input, int *i, t_info *info)
{
	if (!input[*i])
		return ;
	if (ft_strchr(QUOTES, input[*i]))
	{
		token_quote_changer(input, *i, info);
		(*i)++;
		token_end_of_word(input, i, info);
		if (input[*i] && ft_strchr(QUOTES, input[*i]))
			token_quote_changer(input, *i, info);
	}
}

void	token_word_handler(t_token **token_list, char *input, int *i, int type)
{
	t_info	info;

	info.type = type;
	while (input[*i] && ft_strchr(WHITE_SPACES, input[*i]))
		(*i)++;
	info.mode = GENERAL;
	info.start = *i;
	while (input[*i] && (info.mode != GENERAL
			|| !(ft_strchr(WHITE_SPACES, input[*i]))))
	{
		if (ft_strchr(QUOTES, input[*i]))
			token_quote_handler(input, i, &info);
		else
		{
			token_end_of_word(input, i, &info);
			if (ft_strchr(QUOTES, input[*i]))
				token_quote_handler(input, i, &info);
		}
		if (info.mode == GENERAL && (ft_strchr(WHITE_SPACES, input[*i])
				|| ft_strchr(OPERATOR, input[*i])))
			break ;
		if (input[*i])
			(*i)++;
	}
	add_token(token_list, input, *i, &info);
}
