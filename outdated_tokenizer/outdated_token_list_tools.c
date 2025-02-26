/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:48:27 by frbranda          #+#    #+#             */
/*   Updated: 2025/02/25 18:02:37 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// find the last node and return it
t_token_tree	*find_last_node(t_token_tree *token)
{
	t_token_tree	*temp;

	if (!token)
		return (NULL);
	temp = token;
	while (temp->right != NULL)
	{
		temp = temp->right;
	}
	return (temp);
}

// adds new node to the last of node_list
t_token_tree	*add_last_node(t_token_tree **token, t_token_tree *new)
{
	t_token_tree	*last;

	if (!new)
		return (NULL);
	if (!*token)
		*token = new;
	else
	{
		last = find_last_node(*token);
		last->right = new;
	}
	return (*token);
}

// finds pipe and returns it's position if it doesn't find return NULL
t_token_tree	*find_last_pipe(t_token_tree *token)
{
	t_token_tree	*temp;
	t_token_tree	*last_pipe;

	if (!token)
		return (NULL);
	temp = token;
	last_pipe = NULL;
	while (temp->right != NULL)
	{
		if (temp->token_list[0] == '|')
		{
			last_pipe = temp;
		}
		temp = temp->right;
	}
	return (last_pipe);
}

// add pipe to the binary tree, if no pipes found then put new pipe as
//  head(parent?) of list
t_token_tree	*add_pipe_to_node(t_token_tree **token, t_token_tree *new)
{
	t_token_tree	*last_pipe;
	t_token_tree	*last_node;

	last_pipe = NULL;
	if (!new)
		return (NULL);
	if (!*token)
		*token = new;
	else
	{
		last_pipe = find_last_pipe(*token);
		if (!last_pipe)
		{
			new->left = *token;
			*token = new;
		}
		else
		{
			last_node = find_last_node(*token);
			last_pipe->right = new;
			new->left = last_node;
		}
	}
	return (new);
}
