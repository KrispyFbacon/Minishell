/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:12:25 by frbranda          #+#    #+#             */
/*   Updated: 2025/03/18 18:01:48 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* void	quote_changer(char *s, int *i, t_info *info)
{
	if (s[*i] == '\'' && info->mode != DOUBLE_QUO)
	{
		(*i)++;
		if (info->mode == GENERAL)
			info->mode = SINGLE_QUO;
		else if (info->mode == SINGLE_QUO)
			info->mode = GENERAL;
	}
	if (s[*i] == '\"' && info->mode != SINGLE_QUO)
	{
		(*i)++;
		if (info->mode == GENERAL)
			info->mode = DOUBLE_QUO;
		else if (info->mode == DOUBLE_QUO)
			info->mode = GENERAL;
	}
}

void	expand_env(char *s, int *i, t_info *info)
{
	(*i)++;
	ft_printf("Expantion made\n");
	while (s[*i] && s[*i] != "\"" && !(ft_strchr(WHITE_SPACES, s[*i])))
		*i++;
	(*i)--;
}

void general_mode_handler();

void	node_edit(t_shell **shell, t_token **token)
{
	t_info	info;
	char	*s;
	int	i;
	
	info.mode = GENERAL;
	s = (*token)->token;
	i = 0;
	while (s[i])
	{
		if (s[i] && ft_strchr(QUOTES, s[i]))
			mode_handler(s, &i, &info);
		info.start = i;
		if(info.mode == GENERAL)
			general_mode_handler();
		else if(info.mode == SINGLE_QUO)
			single_quote_handler();
		else if(info.mode == DOUBLE_QUO)
			double_quote_handler();
		i++;
	}
	
}

void	handle_quotes(t_shell **shell)
{
	t_token	*token;

	token = (*shell)->token_list;
	while(token)
	{
		node_edit(shell, &token);
		token = token->next;
	}
} */
void	expand_env(t_shell **shell, char *s, int *i, t_info *info)
{
	(*i)++;
	ft_printf("Expantion made\n");
	while (s[*i] && s[*i] != "\"" && !(ft_strchr(WHITE_SPACES, s[*i])))
		*i++;
}

void	node_edit_expand(t_shell **shell, t_token **token, int end, t_info *info)
{
	char	*s;
	int	i;
	
	info->mode = GENERAL;
	s = (*token)->token;
	
}

void	node_expand(t_shell **shell, t_token **token)
{
	t_info	info;
	char	*s;
	int	i;
	
	info.mode = GENERAL;
	s = (*token)->token;
	i = 0;
	info.start = i;
	while (s[i])
	{
		if (s[i] && ft_strchr(QUOTES, s[i]))
			token_quote_changer(s, &i, &info);
		if (s[i] == '$' && info.mode != SINGLE_QUO)
			expand_env(shell, s, &i, &info);
		if (s[i])
			i++;
	}
	node_edit_expand(shell, token, &i, &info);
}

void	handle_expantions(t_shell **shell)
{
	t_token	*token;

	token = (*shell)->token_list;
	while(token)
	{
		node_expand(shell, &token);
		token = token->next;
	}
}

void	tokenizer(t_shell **shell, char *input)
{
	t_token	*token_list;

	token_list = NULL;
	token_split_space(&token_list, input);
	if (!token_list)
		return ;
	print_tokens(token_list);
	(*shell)->token_list = token_list;
	(*shell)->head = token_list;
	handle_expantions(shell);
	//handle_quotes(shell);
	print_tokens((*shell)->token_list);
}

/* ft_printf("DOING A LOOP\n");
	ft_printf("input[i]: %c\n", input[*i]);
	ft_printf("i       : %i\n", *i);
	ft_printf("start   : %i\n", info.start);
	ft_printf("mode    : %i\n", info.mode);
	ft_printf("------------\n"); */