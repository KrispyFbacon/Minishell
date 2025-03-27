/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_structs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:48:28 by frbranda          #+#    #+#             */
/*   Updated: 2025/03/21 15:17:40 by yes              ###   ########.fr       */
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
	new->head = NULL;
	new->env = NULL;
	new->pid = getpid();
	new->s_pid = ft_itoa(getpid());
	new->exit_status = 0;
	return (new);
}
