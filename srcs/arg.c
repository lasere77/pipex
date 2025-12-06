/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 23:14:24 by mewen             #+#    #+#             */
/*   Updated: 2025/12/06 19:28:49 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arg.h"

char	*get_path(char *env[])
{
	size_t	i;
	int		cond;

	i = 0;
	cond = 1;
	while (env[i] && cond)
		cond = ft_strncmp(env[i++], "PATH=", 5);
	if (!env[i])
		return (NULL);
	return (env[i - 1] + 5);
}

char	*get_bin_path(char **path, char *name_bin)
{
	size_t	i;
	char	*res;
	size_t	len_path;
	size_t	len_name_bin;

	if (!name_bin || !path)
		return (NULL);
	len_name_bin = ft_strlen(name_bin);
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
			return (res);
		free(res);
		i++;
	}
	return (NULL);
}

char	**get_arg(char **path, char *arg)
{
	char	**new_arg;
	char	*tmp;

	new_arg = ft_split(arg, ' ');
	if (!new_arg)
		return (NULL);
	tmp = new_arg[0];
	new_arg[0] = get_bin_path(path, new_arg[0]);
	if (!new_arg[0])
		new_arg[0] = tmp;
	else
		free(tmp);
	return (new_arg);
}
