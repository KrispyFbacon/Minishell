/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:12:25 by frbranda          #+#    #+#             */
/*   Updated: 2025/03/20 18:30:21 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
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
	(*shell)->env = ft_calloc(1, sizeof(t_env));
	(*shell)->env->name = "VAR";
	//(*shell)->env->value = "BACON";
	(*shell)->env->value = "s -";
	(*shell)->env->next = NULL;
	handle_expansions(shell);
	//handle_quotes(shell);
	print_tokens((*shell)->token_list);
	free((*shell)->env);
	(*shell)->env = NULL;
}

/* ft_printf("DOING A LOOP\n");
	ft_printf("input[i]: %c\n", input[*i]);
	ft_printf("i       : %i\n", *i);
	ft_printf("start   : %i\n", info.start);
	ft_printf("mode    : %i\n", info.mode);
	ft_printf("------------\n"); */