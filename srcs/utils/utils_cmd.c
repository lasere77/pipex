/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 10:31:01 by mcolin            #+#    #+#             */
/*   Updated: 2025/12/07 11:02:16 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_cmd.h"

char	is_last_cmd_valid(int argc, char *argv[], char *env[])
{
	char	**path;

	path = ft_split(get_path(env), ':');
	if (!path)
		return (0);
	if (!is_valid_cmd(ft_split(argv[argc - 2], ' '), path)
		&& !is_in_dir(ft_split(argv[argc - 2], ' ')))
	{
		free_split(path);
		return (0);
	}
	free_split(path);
	return (1);
}

char	is_valid_cmd(char **new_arg, char **path)
{
	char	result;
	char	*bin_path;

	result = 0;
	bin_path = get_bin_path(path, new_arg[0]);
	if (bin_path)
		result = 1;
	free(bin_path);
	free_split(new_arg);
	return (result);
}
