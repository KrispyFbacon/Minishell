/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:03:57 by frbranda          #+#    #+#             */
/*   Updated: 2025/02/26 17:20:58 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// free tokens
void	free_tokens(t_token **token)
{
	t_token	*temp;

	while (*token != NULL)
	{
		free((*token)->token);
		temp = (*token)->next;
		free(*token);
		*token = temp;
	}
}

// FREE of the token list (binary tree)
void	free_token_list(t_token_tree **token)
{
	t_token_tree	*temp;

	if ((*token))
	{
		while (*token != NULL)
		{
			free_tokens(&(*token)->token_list);
			if ((*token)->left)
				free_token_list(&(*token)->left);
			free((*token)->token_list);
			temp = (*token)->right;
			free(*token);
			*token = temp;
		}
	}
}

// free main struct (shell)
void	free_shell(t_shell	**shell)
{
	free_token_list(&(*shell)->token_tree);
	if ((*shell)->env_var)
		free((*shell)->env_var);
	free((*shell));
}

/* // free binary tree IF ONLY we expand to the left and to the right
void free_token_list(t_token_tree **token)
{
	if (*token == NULL)
		return;

	free_token_list(&(*token)->left);// Free left first
	free_token_list(&(*token)->right);// Free right next
	free((*token)->token_list);
	free(*token);
	*token = NULL;
} */