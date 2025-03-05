/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:12:25 by frbranda          #+#    #+#             */
/*   Updated: 2025/03/05 19:13:38 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// var len handle but it will be changed later on when env var will be handled
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
	
	
	if(input[*i] == '\"')
		s = new_string(input, i, DOUBLE_QUO);
	else if(input[*i] == '\'')
		s = new_string(input, i, SINGLE_QUO);
	else
		s = new_string(input, i, GENERAL);
	if(!s)
		return ;
	new_token = initialize_token(s, ARG);
	add_last_token(token, new_token);
	free(s);
}

void	token_split(t_token_tree **token_list, char *input)
{
	t_token	*token;
	int		i;
	
	i = 0;
	token = NULL;
	while(input[i])
	{
		while (input[i] && input[i] == ' ')
			i++;
		if (!input[i])
			break ;
		else
			token_add(&token, input, &i);
		if (input[i])
			i++;
	}
	(*token_list)->token_list = token;
}

void	tokenizer(t_shell **shell, char *input)
{
	t_token_tree	*token_list;

	token_list = initialize_token_list();
	token_split(&token_list, input);
	print_token_list(token_list);
	(*shell)->token_tree = token_list;
}