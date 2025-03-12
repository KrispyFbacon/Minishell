/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split_space.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:23:25 by frbranda          #+#    #+#             */
/*   Updated: 2025/03/12 17:18:39 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	token_redir_handler(t_token **token_list, char *input, int *i)
{
	int	type;

	type = get_token_type(input, *i);
	if (type == 0)
		return ;
	if (type == REDIR_OUT || type == REDIR_IN)
		(*i)++;
	else if (type == APPEND || type == HEREDOC)
		*i = *i + 2;
	token_word_handler(token_list, input, i, type);
}

void	token_pipe_handler(t_token **token_list, char *input, int *i)
{
	t_token	*new_token;

	if (input[*i] == '|')
	{
		new_token = initialize_token("|", PIPE);
		add_last_token(token_list, new_token);
		(*i)++;
	}
}

void	token_split_space(t_token **token_list, char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		while (input[i] && ft_strchr(WHITE_SPACES, input[i]))
			i++;
		if (input[i] && ft_strchr(T_PIPE, input[i]))
			token_pipe_handler(token_list, input, &i);
		else if (input[i] && ft_strchr(T_REDIR, input[i]))
			token_redir_handler(token_list, input, &i);
		else
			token_word_handler(token_list, input, &i, CMD);
	}
}
