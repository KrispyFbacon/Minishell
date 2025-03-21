/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:12:25 by frbranda          #+#    #+#             */
/*   Updated: 2025/03/21 17:04:23 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	separate_token(t_shell *shell, char **s_ptr, int *i, t_info *info)
{
	char	*s;

	s = *s_ptr;
	info->start = *i;
	while (s[*i] && ft_strchr(WHITE_SPACES, s[*i]))
		i++;
	info->end = *i;
	
	info->start = info->end;
}

void	node_quote_handle(t_shell **shell, t_token **token)
{
	t_info	info;
	char	*s;
	int		i;

	info.mode = GENERAL;
	s = (*token)->token;
	i = 0;
	info.start = i;
	while (s[i])
	{
		if (s[i] && ft_strchr(QUOTES, s[i]))
			quote_changer(s, &i, &info);
		else if (s[i] && info.mode == SINGLE_QUO)
			handle_single_quote(*shell, &s, &i, &info);
		else if (s[i] && info.mode == DOUBLE_QUO)
			handle_double_quote(*shell, &s, &i, &info);
		else if(s[i] && info.mode == GENERAL && ft_strchr(WHITE_SPACES, s[i]))
			separate_token(*shell, &s, &i, &info);
		else
			i++;
	}
	(*token)->token = s;
}

void	handle_quotes(t_shell **shell)
{
	t_token	*token;

	token = (*shell)->token_list;
	while(token)
	{
		node_handle(shell, &token);
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
	(*shell)->env = ft_calloc(1, sizeof(t_env));
	(*shell)->env->name = "VAR";
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