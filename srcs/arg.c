/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mewen <mewen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 23:14:24 by mewen             #+#    #+#             */
/*   Updated: 2025/12/01 23:16:36 by mewen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arg.h"

char	*get_path(char *env[])
{
	int				cond;
	unsigned int	i;

	i = 0;
	cond = 1;
	while (env[i] && cond)
		cond = ft_strncmp(env[i++], "PATH=", 5);
	if (!env[i])
		return (NULL);
	return (env[i - 1] + 5);
}

static char	*get_bin_path(char **path, char *name_bin, size_t len_name_bin)
{
	char			*res;
	unsigned int	i;
	unsigned int	len_path;

	i = 0;
	while (path[i])
	{
		len_path = ft_strlen(path[i]);
		res = malloc(sizeof(char) * (len_name_bin + 1 + len_path + 1));
		if (!res)
			return (NULL);
		ft_memcpy(res, path[i], len_path);
		res[len_path] = '/';
		ft_memcpy(res + len_path + 1, name_bin, len_name_bin);
		res[len_name_bin + 1 + len_path] = 0;
		if (access(res, F_OK | X_OK) == 0)
		{
			free(name_bin);
			return (res);
		}
		free(res);
		i++;
	}
	free(name_bin);
	return (NULL);
}

void	free_split(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
}

char	**get_new_arg(char **path, char *argv)
{
	char	**new_arg;
	char	*tmp;

	new_arg = ft_split(argv, ' ');
	if (!new_arg)
		return (NULL);
	if (access(new_arg[0], F_OK | X_OK) != 0)
	{
		tmp = get_bin_path(path, new_arg[0], ft_strlen(new_arg[0]));
		if (!tmp)
		{
			free_split(new_arg);
			return (NULL);
		}
		new_arg[0] = tmp;
	}
	return (new_arg);
}
