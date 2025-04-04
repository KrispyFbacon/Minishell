/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:08:49 by frbranda          #+#    #+#             */
/*   Updated: 2025/04/04 12:57:11 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	print_token_type(t_token *token)
{
	if (token->type == CMD)
		ft_printf("Type : CMD\n");
	else if (token->type == ARG)
		ft_printf("Type : ARG\n");
	else if (token->type == PIPE)
		ft_printf("Type : PIPE\n");
	else if (token->type == REDIR_OUT)
		ft_printf("Type : REDIR_OUT\n");
	else if (token->type == REDIR_IN)
		ft_printf("Type : REDIR_IN\n");
	else if (token->type == APPEND)
		ft_printf("Type : APPEND\n");
	else if (token->type == HEREDOC)
		ft_printf("Type : HEREDOC\n");
	else
		ft_printf("Type : NULL\n");
}

void	print_tokens(t_token *token)
{
	t_token	*temp;

	temp = token;
	if (!token)
		return ;
	ft_printf("\n-----------------\n");
	ft_printf("TOKEN LIST: \n");
	ft_printf("-----------------\n");
	while (temp)
	{
		ft_printf("Token: {%s}\n", temp->token);
		print_token_type(temp);
		if (temp->next == NULL)
			ft_printf("next: %s\n", temp->next);
		else
			ft_printf("Next: {%s}\n", temp->next->token);
		temp = temp->next;
		ft_printf("-----------------\n");
	}
}
// TODO DELETE WHEN NOT NEEDED
/* void	print_tokens_simple(t_token *token)
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
} */
