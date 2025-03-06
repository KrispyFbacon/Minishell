/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:08:49 by frbranda          #+#    #+#             */
/*   Updated: 2025/03/06 14:10:41 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_token *token)
{
	t_token	*temp;

	temp = token;
	ft_printf("-----------------\n");
	while (temp)
	{
		ft_printf("Token: {%s}\n", temp->token);
		if (temp->type == PIPE)
			ft_printf("Type : PIPE\n");
		else
			ft_printf("Type : EXEC\n");
		if (temp->next == NULL)
			ft_printf("next: %s\n", temp->next);
		else
			ft_printf("Next: {%s}\n", temp->next->token);
		temp = temp->next;
		ft_printf("-----------------\n");
	}
}

void	print_tokens_simple(t_token *token)
{
	t_token	*temp;

	if (!token)
		return ;
	temp = token;
	ft_printf("Tokens: [\"%s\"", temp->token);
	temp = temp->next;
	while (temp)
	{
		ft_printf(", \"%s\"", temp->token);
		temp = temp->next;
	}
	ft_printf("]\n");
}
