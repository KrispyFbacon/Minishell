/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:12:25 by frbranda          #+#    #+#             */
/*   Updated: 2025/03/31 12:53:37 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenizer(t_shell **shell, char *s)
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
			continue ;
		handle_quotes(&s, &i, &info);
		temp = ft_substr(s, info.start, (info.end - info.start));
		add_new_token(&token_list, temp, &info);
		info.type_flag = FALSE;
		free (temp);
		temp = NULL;
	}
	free(s);
	(*shell)->token_list = token_list;
	print_tokens(token_list);
}

t_env	*initialize_env(void)
{
	t_env	*new;
	t_env	*new2;

	new = ft_calloc(1, sizeof(t_env));
	new->name = "VAR";
	new->value = "$VAR1";
	new->next = NULL;
	new2 = ft_calloc(1, sizeof(t_env));
	new2->name = "VAR1";
	new2->value = ">>";
	new2->next = NULL;
	new->next = new2;
	return (new);
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