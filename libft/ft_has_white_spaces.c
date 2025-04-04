/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_has_white_spaces.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:41:31 by yes               #+#    #+#             */
/*   Updated: 2025/04/04 13:14:48 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// TODO change header ^

/**
 * @brief Checks if a string contains any whitespace characters.
 * 
 * @param s The input string to check.
 * @return 1 if the string contains whitespace, 0 otherwise.
 */
int	ft_has_white_spaces(char *s)
{
	const char	*white_space;
	int			i;

	white_space = " \t\r\n\v\f";
	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (ft_strchr(white_space, s[i]))
			return (1);
		i++;
	}
	return (0);
}
