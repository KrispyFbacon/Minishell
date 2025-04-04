/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_structs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:48:28 by frbranda          #+#    #+#             */
/*   Updated: 2025/04/04 13:18:37 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

// TODO DELETE LATER WHEN ENV IS INITIALIZE
/* t_env	*initialize_env(void)
{
	t_env	*new;
	t_env	*new2;
	t_env	*new3;

	new = ft_calloc(1, sizeof(t_env));
	new->name = ft_strdup("VAR");
	new->value = ft_strdup("s -");
	new->next = NULL;
	new2 = ft_calloc(1, sizeof(t_env));
	new2->name = ft_strdup("VAR1");
	new2->value = ft_strdup("echo");
	new2->next = NULL;
	new->next = new2;
	new3 = ft_calloc(1, sizeof(t_env));
	new3->name = ft_strdup("REDIR");
	new3->value = ft_strdup(">>");
	new3->next = NULL;
	new2->next = new3;
	return (new);
} */
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
