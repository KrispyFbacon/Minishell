/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:14:30 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/05/15 15:09:29 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO delete or do ft_print_buffered_error;
/**
 * @brief Prints an error message based on the current `errno` value.
 * 
 * This function checks if `errno` is set, and if so, it prints the error
 * message associated with the current value of `errno` using `perror`.
 * 
 * @param error The error message to be printed if `errno` is set.
 * @return int Returns the status code (currently always `0`).
 */
int	print_msg_error(char *error)
{
	int	status_code;

	status_code = 0;
	if (errno)
		perror(error);
	shell->exit_status = 1;
/* 	else
		status_code = ft_print_buffered_error(error); */
	return (status_code);
}

/**
 * @brief Handles errors related to the `export` command when an invalid
 * argument is provided.
 * 
 * This function checks the provided argument to the `export` command. If the
 * argument starts with a dash ('-') and has invalid options or is not a valid
 * identifier, an appropriate error message is printed.
 * 
 * @param arg The argument passed to the `export` command that is being
 * validated.
 * @return int Returns an error code:
 * 
 * - `2` if the argument is an invalid option (e.g., `-a`, `-1`).
 * 
 * - `1` if the argument is a valid identifier but not allowed for export.
 * 
 * - `0` if no error is found.
 */
int	export_error(char *arg)
{
	if (arg[0] == '-')
	{
		if (arg[1])
			return (ft_printf("minishell: export -%c: invalid option\n",
					arg[1]), 2);
		return (ft_printf("minishell: export: `%s': not a valid identifier\n",
				arg), 1);
	}
	return (0);
}

/**
 * @brief Prints an error message indicating that the provided variable name is
 * not a valid identifier.
 * 
 * This function is used to print an error message when an invalid variable name
 * is encountered during the export process. The error message indicates that the
 * variable is not a valid identifier as per the shell's requirements.
 * 
 * @param var The name of the variable that is not valid.
 */
int	print_invalid_var(char *var)
{
	return (ft_printf("minishell: export: `%s': not a valid identifier\n", var),
		1);
}
