/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_new_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:35:33 by yes               #+#    #+#             */
/*   Updated: 2025/03/30 16:37:26 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*add_new_token(t_token **token_list, char *temp, t_info *info)
{
	t_token	*new_token;

	if (info->end - info->start <= 0
		&& !(info->type >= REDIR_IN && info->type <= HEREDOC))
		return (NULL);
	new_token = initialize_token(temp, info->type);
	add_last_token(token_list, new_token);
	return (*token_list);
}
