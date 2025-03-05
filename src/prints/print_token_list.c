/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_token_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:09:01 by frbranda          #+#    #+#             */
/*   Updated: 2025/03/05 17:15:46 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token_list(t_token_tree *token_list)
{
	t_token	*temp;

	if (!(token_list->token_list))
		return ;
	temp = token_list->token_list;
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

// PRINTS token_list (binary tree)
/*  if (!token)
		return ; */
/* void	print_token_list(t_token_tree *token)
{
	t_token_tree	*temp;

	temp = token;
	ft_printf("-----------------\n");
	while (temp)
	{
		ft_printf("Token: {%s}\n", temp->token_list);
		if (temp->type == PIPE)
			ft_printf("Type : PIPE\n");
		else
			ft_printf("Type : EXEC\n");
		if (temp->left == NULL)
			ft_printf("Left : %s\n", temp->left);
		else
			ft_printf("Left : {%s}\n", temp->left->token_list);
		if (temp->right == NULL)
			ft_printf("Right: %s\n", temp->right);
		else
			ft_printf("Right: {%s}\n", temp->right->token_list);
		if (temp->left)
			print_token_list(temp->left);
		temp = temp->right;
		ft_printf("-----------------\n");
	}
} */

/* 
void	print_token_list_simple(t_token_tree *token)
{
	t_token_tree	*temp;

	if (!token)
		return ;
	temp = token;
	ft_printf("Tokens: [\"%s\"", temp->token_list);
	temp = temp->right;
	while (temp)
	{
		ft_printf(", \"%s\"", temp->token_list);
		temp = temp->right;
	}
	ft_printf("]\n");
} */
