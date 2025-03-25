/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_new_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:35:33 by yes               #+#    #+#             */
/*   Updated: 2025/03/25 18:35:51 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*add_new_token(t_token **token_list, char *temp, t_info *info)
{
	t_token	*new_token;
	
	if (info->len <= 0 && !(info->type >= REDIR_IN && info->type <= HEREDOC))
		return (*token_list);
	new_token = initialize_token(temp, info->type);
	add_last_token(token_list, new_token);
	free (temp);
	temp = NULL;
	return (*token_list);
}