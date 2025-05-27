/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:20:13 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/05/27 23:27:02 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Parses the argument passed to the `pwd` command to check for invalid
 * options.
 * 
 * This function checks if the argument passed to the `pwd` command is a
 * redirection operator (such as `>`, `>>`, or `|`), which are not supported by
 * the `pwd` command. If an unsupported argument is found, the function prints
 * an error message and returns a failure code.
 * 
 * @param arg The argument passed to the `pwd` command.
 * @return int Returns `1` if the argument is an invalid redirection operator
 * or pipe. Returns `0` if the argument is valid.
 */
static int	parse_pwd(char *arg)
{
	if (arg[0] == '-' && arg[1])
		return (ft_printf_fd(2, "minishell: pwd: -%c: invalid option\n",
				arg[1]), 2);
	return (0);
}

/**
 * @brief Prints the current working directory to the standard output.
 * 
 * This function retrieves and prints the current working directory using the 
 * `getcwd` function. If an argument is provided to the command, it checks if 
 * the argument is valid and returns an error if necessary. If the current 
 * working directory cannot be retrieved, it prints an error message and
 * returns a failure code.
 * 
 * @param args An array of strings containing the arguments passed to the `pwd`
 * command. The first element (`args[0]`) is the command name (`pwd`), and any
 * subsequent elements are options or arguments.
 * @param shell Pointer to the shell structure, containing necessary data for
 * the shell execution.
 * @return int Returns `0` if the current directory is successfully retrieved
 * and printed. If an error occurs (such as an invalid argument or failure to
 * get the current directory), it prints an error message and returns `1`.
 */
int	ft_pwd(char **args, t_shell *shell)
{
	char	cwd[4096];

	(void)shell;
	if (args[1] && parse_pwd(args[1]))
		return (1);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_printf_fd(1, "%s\n", cwd);
		return (0);
	}
	else
		return (ft_printf_fd(2, "pwd: error retrieving current directory\n"), 1);
}
