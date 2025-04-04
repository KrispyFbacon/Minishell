/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:12:25 by frbranda          #+#    #+#             */
/*   Updated: 2025/04/04 13:12:59 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO DELETE printf and (*shell)->exit_status = 0;
void	tokenizer(t_shell **shell, char *s)
{
	t_token	*token_list;
	t_info	info;
	int		i;

	token_list = NULL;
	inizialize_info(&info);
	i = 0;
	while (s[i])
	{
		split_spaces(token_list, s, &i, &info);
		if (handle_expansions(*shell, &s, &i, &info) == TRUE)
			continue ;
		if (info.error_flag == TRUE)
		{
			free_tokens(&token_list);
			return ;
		}
		handle_quotes(&s, &i, &info);
		add_new_token(&token_list, s, &info);
		info.type_flag = FALSE;
	}
	free(s);
	(*shell)->token_list = token_list;
	(*shell)->exit_status = 0;
	print_tokens(token_list);
}
