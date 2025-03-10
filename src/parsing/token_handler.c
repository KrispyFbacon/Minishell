/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 19:01:28 by frbranda          #+#    #+#             */
/*   Updated: 2025/03/10 19:30:04 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_quotes(char *input, int i, int *mode)
{
	if (input[i] == '\'' || input[i] == '\"')
	{
		if (*mode == SINGLE_QUO || *mode == DOUBLE_QUO)
			*mode = GENERAL;
		else if (*mode == GENERAL && input[i] == '\'')
			*mode = SINGLE_QUO;
		else if (*mode == GENERAL && input[i] == '\"')
			*mode = DOUBLE_QUO;
	}
}

void	add_token_word(t_token **token_list, char *input, int start, int i)
{
	t_token	*new_token;
	char	*s;
	int	len;
	int	j;

	len = i - start;
	s = (char *)ft_calloc((len + 1), sizeof(char));
	if (!s)
		return ;
	j = 0;
	while (start < i)
	{
		s[j] = input [start];
		start++;
		j++;
	}
	s[j] = '\0';
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
	if (info.type == APPEND || info.type == HEREDOC)
		*i = *i + 2;
	while (input[*i] && ft_strchr(WHITE_SPACES, input[*i]))
		(*i)++;
	mode = GENERAL;
	info.start = *i;
	while (input[*i] && (ft_strchr(WHITE_SPACES, input[*i])
		|| ft_strchr(S_REDIR, input[*i])))
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