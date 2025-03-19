/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:03:57 by frbranda          #+#    #+#             */
/*   Updated: 2025/03/19 13:27:02 by yes              ###   ########.fr       */
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
	(*token) = NULL;
}

// free main struct (shell)
void	free_shell(t_shell	**shell)
{
	if ((*shell)->token_list)
		free_tokens(&(*shell)->token_list);
	if ((*shell)->env)
		free((*shell)->env);
	free((*shell));
}
