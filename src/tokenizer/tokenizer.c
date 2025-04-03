/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:12:25 by frbranda          #+#    #+#             */
/*   Updated: 2025/04/03 21:00:13 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO move to inizialize_structs
void	inizialize_info(t_info	*info)
{
	info->start = 0;
	info->end = 0;
	info->env_start = 0;
	info->env_end = 0;
	info->type = CMD;
	info->type_flag = FALSE;
	info->mode = GENERAL;
	info->error_flag = FALSE;
}

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


// TODO DELETE v

/* printf ("AFTER SPLIT_SPACES-------\n");
		printf ("i: %i\n", i);
		printf("START: %i\n", info.start);
		printf("END: %i\n", info.end);
		printf("ENV_START: %i\n", info.env_start);
		printf("ENV_END: %i\n", info.env_end); */

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