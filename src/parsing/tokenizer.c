/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:12:25 by frbranda          #+#    #+#             */
/*   Updated: 2025/03/11 19:36:10 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* void	token_split(t_token **token_list, char *input)
{
	int		i;
	int		start;
	int		mode;

	i = 0;
	while (input[i])
	{
		while (input[i] && ft_strchr(WHITE_SPACES, input[i]))
			i++;
		mode = GENERAL;
		start = i;
		while (input[i]
				&& (mode == GENERAL || !(ft_strchr(WHITE_SPACES, input[i]))))
		{
			if (mode == GENERAL && ft_strchr(S_REDIR, input[i]))
				break;
			handle_quotes(input, &i, &start, &mode);
			if (input[i] && mode == GENERAL && ft_strchr(WHITE_SPACES, input[i]))
				break;
			i++;
		}
		if (i > start)
			add_token_word(token_list, input, start, i);
		handle_token_redir(token_list, input, &i);
		handle_token_pipe(token_list, input, &i);
	}
} */
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

void	add_token(t_token **token_list, char *input, int i, t_info *info)
{
	t_token	*new_token;
	char	*s;
	int	len;
	int	j;

	len = i - info->start;
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
	char quote;
	
	if (info->mode != GENERAL)
	{
		quote = input[*i];
		(*i)++;
		while (input[*i] && input[*i] != quote)
			(*i)++;
	}
	else
	{
		while (input[*i] && (ft_strchr(WHITE_SPACES, input[*i])))
			(*i)++;
	}
}

void	token_word_handler(t_token **token_list, char *input, int *i, int type)
{
	t_info info;

	info.type = type;
	while (input[*i] && ft_strchr(WHITE_SPACES, input[*i]))
			(*i)++;
	info.mode = GENERAL;
	info.start = *i;
	while (input[*i])
	{
		if(ft_strchr(QUOTES, input[*i]))
			token_quote_changer(input, *i, &info);
		if (info.mode == GENERAL && ft_strchr(WHITE_SPACES, input[*i]))
			break ;
		token_end_of_word(input, i, &info);
		if (info.mode == GENERAL && ft_strchr(OPERATOR, input[*i]))
			break ;
		if (input[*i])
			(*i)++;
	}
	add_token(token_list, input, *i, &info);
}

/* ft_printf("DOING A LOOP\n");
	ft_printf("input[i]: %c\n", input[*i]);
	ft_printf("i       : %i\n", *i);
	ft_printf("start   : %i\n", info.start);
	ft_printf("mode    : %i\n", info.mode);
	ft_printf("------------\n"); */

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
	t_token *new_token;
	
	if (input[*i] == '|')
	{
		new_token = initialize_token("|", PIPE);
		add_last_token(token_list, new_token);
		(*i)++;
	}
}

void	token_space_handler(t_token **token_list, char *input)
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


void	tokenizer(t_shell **shell, char *input)
{
	t_token	*token_list;

	token_list = NULL;
	token_space_handler(&token_list, input);
	print_tokens(token_list);
	(*shell)->token_list = token_list;
}

/* // var len handle but it will be changed later on when env var will be handled
int	var_len(char *input,int *i)
{
	int		len;
	
	len = 0;
	(*i)++;
	while (input[*i] && input[*i] != ' ' && input[*i] != '\"')
	{
		len++;
		(*i)++;
	}
	return (len);
}
// get length for alloc and diffrerent count when finds $VAR
int	get_len(char *input,int *i,int mode)
{
	int	len;

	len = 0;
	while (input[*i] && input[*i] != ' ' && mode == GENERAL)
	{
		if (mode == GENERAL && input[*i] == '$')
			len += var_len(input, i);
		else
		{
			len++;
			(*i)++;
		}
	}
	while (input[*i] && ((mode == SINGLE_QUO && input[*i] != '\'') ||
		(mode == DOUBLE_QUO && input[*i] != '\"')))
	{
		if (mode == DOUBLE_QUO && input[*i] == '$')
			len += var_len(input, i);
		else
		{
			len++;
			(*i)++;
		}
	}
	return (len);
}
// creates a new string depending on the quote mode
// $VAR with double quotes or normal it will ignore $ 
// (change it later when env var will be handled)
char	*new_string(char *input, int *i, int mode)
{
	char	*new_s;
	int		len;
	int		j;

	j = 0;
	if (mode == SINGLE_QUO || mode == DOUBLE_QUO)
		(*i)++;
	len = get_len(input, i, mode);
	new_s = (char *)ft_calloc((len + 1), sizeof(char));
	if (!new_s)
		return (NULL);
	*i -= len;
	while (j < len)
	{
		if ((mode == DOUBLE_QUO || mode == GENERAL) && input[*i] == '$')
		{
			len--;
			(*i)++;
		}
		else
		{
			new_s[j] = input[*i];
			j++;
			(*i)++;
		}
	}
	new_s[j] = '\0';
	if (mode == SINGLE_QUO || mode == DOUBLE_QUO)
		(*i)++;
	return (new_s);
}
// when find other than spaces checks for quotes
void	token_add(t_token **token, char *input, int *i)
{
	t_token	*new_token;
	char	*s;

	s = new_string(input, i, GENERAL);
	if(!s)
		return ;
	new_token = initialize_token(s, EXEC);
	add_last_token(token, new_token);
	free(s);
}

void	token_split(t_token **token_list, char *input)
{
	int		i;

	i = 0;
	while(input[i])
	{
		while (input[i] && input[i] == ' ')
			i++;
		if (!input[i])
			break ;
		else
			token_add(token_list, input, &i);
		if (input[i])
			i++;
	}
} */