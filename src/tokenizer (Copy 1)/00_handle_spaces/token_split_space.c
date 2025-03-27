/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split_space.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:23:25 by frbranda          #+#    #+#             */
/*   Updated: 2025/03/24 14:20:37 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_token_redir_type(char *input, int i)
{
	int	type;

	type = 0;
	if (ft_strchr(T_REDIR, input[i]))
	{
		if (input[i] == '>' && input[i + 1] != '>')
			type = REDIR_OUT;
		else if (input[i] == '<' && input[i + 1] != '<')
			type = REDIR_IN;
		else if (input[i] == '>' && input[i + 1] == '>')
			type = APPEND;
		else if (input[i] == '<' && input[i + 1] == '<')
			type = HEREDOC;
	}
	return (type);
}

void	token_redir_handler(t_token **token_list, char *input, int *i)
{
	int	type;

	type = get_token_redir_type(input, *i);
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

void	type_checker(t_token **token_list, char *input, int *i)
{
	t_token	*last;

	if (!(*token_list))
		token_word_handler(token_list, input, i, CMD);
	last = find_last_token(*token_list);
	if (last->type == PIPE)
		token_word_handler(token_list, input, i, CMD);
	else
		token_word_handler(token_list, input, i, ARG);
}

void	token_split_space(t_token **token_list, char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		while (input[i] && ft_strchr(WHITE_SPACES, input[i]))
			i++;
		if (!input[i])
			return ;
		if (input[i] && ft_strchr(T_PIPE, input[i]))
			token_pipe_handler(token_list, input, &i);
		else if (input[i] && ft_strchr(T_REDIR, input[i]))
			token_redir_handler(token_list, input, &i);
		else
			type_checker(token_list, input, &i);
	}
}
