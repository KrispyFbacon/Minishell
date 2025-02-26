/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outdated_tokenizer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:09:00 by frbranda          #+#    #+#             */
/*   Updated: 2025/02/26 13:09:10 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// found a string (input) that its not a '|'
//  inserts into input into new string until finds '|' or NULL
char	*new_string(char *input, int *i)
{
	char	*new_s;
	int		len;
	int		j;

	j = 0;
	len = 0;
	while (input[*i] && input[*i] != '|')
	{
		*i = *i + 1;
		len++;
	}
	new_s = (char *)ft_calloc((len + 1), sizeof(char));
	if (!new_s)
		return (NULL);
	while (len != 0)
	{
		new_s[j] = input[*i - len];
		len--;
		j++;
	}
	new_s[j] = '\0';
	*i = *i - 1;
	return (new_s);
}

// handles when it finds a string that is not a '|'
void	handle_string_to_node(t_token_tree **token_list, char *input, int *i)
{
	t_token_tree	*new_node;
	char			*s;

	s = new_string(input, i);
	if (!s)
		return ;
	new_node = initialize_token_list(s, EXEC);
	add_last_node(token_list, new_node);
	free(s);
}

// splits the input with pipes and adds to token_tree/list
void	node_split(t_token_tree **token_list, char *input)
{
	t_token_tree	*new_node;
	int				i;

	i = 0;
	while (input[i])
	{
		while (input[i] && input[i] == ' ')
			i++;
		if (!input[i])
			break ;
		else
		{
			if (input[i] == '|')
			{
				new_node = initialize_token_list("|", PIPE);
				add_pipe_to_node(token_list, new_node);
			}
			else
				handle_string_to_node(token_list, input, &i);
		}
		i++;
	}
}

void	tokenizer(t_shell **shell, char *input)
{
	t_token_tree	*token_list;

	token_list = NULL;
	node_split(&token_list, input);
	print_token_list(token_list);
	(*shell)->token_tree = token_list;
}