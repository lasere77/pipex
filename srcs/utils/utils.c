/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 17:41:03 by mcolin            #+#    #+#             */
/*   Updated: 2025/12/07 13:34:21 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	panic_free(t_cmd *cmd, pid_t *list_pid)
{
	unset_cmd(cmd);
	free(list_pid);
	exit(EXIT_FAILURE);
}

char	is_in_dir(char **new_arg)
{
	char	result;

	result = 0;
	if (ft_strchr(new_arg[0], '/') && access(new_arg[0], F_OK | X_OK) == 0)
		result = 1;
	free_split(new_arg);
	return (result);
}

void	free_split(char **strs)
{
	size_t	i;

	if (!strs)
		return ;
	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
}
