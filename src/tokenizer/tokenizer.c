/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:12:25 by frbranda          #+#    #+#             */
/*   Updated: 2025/03/28 22:06:59 by yes              ###   ########.fr       */
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
	i = 0;
	(*shell)->env = initialize_env();
	printf("Before expansion: %p -> {%s}\n", s, s);
	while (s[i])
	{
		split_spaces(token_list, s, &i, &info);
		printf("S: %p -> {%s}\n", s, s);
		if (handle_expansions(*shell, &s, &i, &info) == TRUE)
			continue ;
		// handle_quotes;
		temp = ft_substr(s, info.start, (info.end - info.start));
		printf("S AFTER EXPANSION: %p -> {%s}\n", s, s);
		printf("TEMP AFTER EXPANSION: %p -> {%s}\n", temp, temp);
		if (info.end - info.start > 0 || (info.type >= REDIR_IN && info.type <= HEREDOC))
		{
			ft_printf ("Token: {%s}\n", temp);
			print_type(&info);
			ft_printf("-----------------------\n");
		}
		add_new_token(&token_list, temp, &info);
		free (temp);
		temp = NULL;
	}
	printf("input after: %p -> {%s}\n", s, s);
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
	new2->value = "s -";
	new2->next = NULL;
	new->next = new2;
	
	return (new);
}

void	print_type(t_info *info)
{
	if (info->len <= 0)
		return ;
	if (info->type == CMD)
		ft_printf("Type : CMD\n");
	else if (info->type == ARG)
		ft_printf("Type : ARG\n");
	else if (info->type == PIPE)
		ft_printf("Type : PIPE\n");
	else if (info->type == REDIR_OUT)
		ft_printf("Type : REDIR_OUT\n");
	else if (info->type == REDIR_IN)
		ft_printf("Type : REDIR_IN\n");
	else if (info->type == APPEND)
		ft_printf("Type : APPEND\n");
	else if (info->type == HEREDOC)
		ft_printf("Type : HEREDOC\n");
	else
		ft_printf("Type : NULL\n");
}

/* ft_printf("DOING A LOOP\n");
	ft_printf("input[i]: %c\n", input[*i]);
	ft_printf("i       : %i\n", *i);
	ft_printf("start   : %i\n", info.start);
	ft_printf("mode    : %i\n", info.mode);
	ft_printf("------------\n"); */