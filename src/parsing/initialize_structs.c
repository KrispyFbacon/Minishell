/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_structs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:48:28 by frbranda          #+#    #+#             */
/*   Updated: 2025/03/06 13:54:59 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*initialize_token(char *s, int type)
{
	t_token	*new;

	new = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!new)
		return (NULL);
	new->token = ft_strdup(s);
	new->type = type;
	new->state = GENERAL;
	new->next = NULL;
	return (new);
}

// inicialize shell
t_shell	*initialize_shell(void)
{
	t_shell	*new;

	new = (t_shell *)ft_calloc(1, sizeof(t_shell));
	if (!new)
		return (NULL);
	new->token_list = NULL;
	new->env_var = NULL;
	new->exit_status = 0;
	return (new);
}
