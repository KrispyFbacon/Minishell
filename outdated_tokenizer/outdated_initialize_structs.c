/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_structs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:48:28 by frbranda          #+#    #+#             */
/*   Updated: 2025/02/26 13:05:25 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*initialize_tokens(char *s)
{
	t_token	*new;

	new = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!new)
		return (NULL);
	new->token = ft_strdup(s);
	new->type = ARG;
	new->state = GENERAL;
	new->next = NULL;
	return (new);
}

// inicialize token_list (binary_tree)
t_token_tree	*initialize_token_list(char *s, int type)
{
	t_token_tree	*new;

	new = (t_token_tree *)ft_calloc(1, sizeof(t_token_tree));
	if (!new)
		return (NULL);
	//new->token_list = ft_strdup(s);
	new->token_list = NULL;
	new->type = type;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

// inicialize shell
t_shell	*initialize_shell(void)
{
	t_shell	*new;

	new = (t_shell *)ft_calloc(1, sizeof(t_shell));
	if (!new)
		return (NULL);
	new->token_tree = NULL;
	new->env_var = NULL;
	new->exit_status = 0;
	return (new);
}
