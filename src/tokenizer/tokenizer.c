/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:12:25 by frbranda          #+#    #+#             */
/*   Updated: 2025/04/01 17:24:46 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenizer(t_shell **shell, char *s)
{
	t_token	*token_list;
	t_info	info;
	char	*temp;
	int		i;

	token_list = NULL;
	info.mode = GENERAL;
	info.type_flag = FALSE;
	i = 0;
	while (s[i])
	{
		split_spaces(token_list, s, &i, &info);
		if (handle_expansions(*shell, &s, &i, &info) == TRUE)
		{
			//CHECK IF $ IS AMBIGUOUS change if not continues;
			if (info.temp_flag == TRUE)
			{
				printf("ptr_s: %p ---> %s\n", s, s);
				printf("info.env_start: %i\n", info.env_start);
				printf("info.env_start: %i\n", info.env_end);
				free (s);
				return (1);
			}
			continue ;
		}
		handle_quotes(&s, &i, &info);
		temp = ft_substr(s, info.start, (info.end - info.start));
		add_new_token(&token_list, temp, &info);
		info.type_flag = FALSE;
		free (temp);
	}
	free(s);
	(*shell)->token_list = token_list;
	print_tokens(token_list);
	return (0);
}

// TODO DELETE v

/*
printf("Before expansion: %p -> {%s}\n", s, s);
printf("S: %p -> {%s}\n", s, s);
		printf("TYPE_FLAG: %i\n", info.type_flag);
		printf("TYPE: %i\n", info.type);
		printf("START: %i\n", info.start);
		printf("END: %i\n", info.end);
		printf("S AFTER EXPANSION: %p -> {%s}\n", s, s);
		printf("TEMP AFTER EXPANSION: %p -> {%s}\n", temp, temp);
		printf("input after: %p -> {%s}\n", s, s);
		printf("Before expansion: %p -> {%s}\n", input, input);
		printf("input after: %p -> {%s}\n", input, input);
*/

/* ft_printf("DOING A LOOP\n");
	ft_printf("input[i]: %c\n", input[*i]);
	ft_printf("i       : %i\n", *i);
	ft_printf("start   : %i\n", info.start);
	ft_printf("mode    : %i\n", info.mode);
	ft_printf("------------\n"); */