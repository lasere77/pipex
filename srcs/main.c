/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 09:35:56 by mcolin            #+#    #+#             */
/*   Updated: 2025/11/27 16:23:15 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"
#include "utils.h"
#include "libft.h"

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

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

char	*get_bin_path(char **path, char *name_bin, unsigned int len_name_bin)
{
	char			*res;
	unsigned int	i;
	unsigned int	len_path;

	i = 0;
	while (path[i])
	{
		len_path = ft_strlen(path[i]);
		res = malloc(sizeof(char) * (len_name_bin + 1 +  len_path + 1));
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
	unsigned int i;

	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
}

char	**get_new_arg(char **path, char *argv)
{
	char    **new_arg;
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
/*
./pipex infile "grep 1" "grep je" "wc -w" outfile && cat outfile
< infile grep 1 | grep je | wc -w > outfile  && cat outfile

*/
int	main(int argc, char *argv[], char *env[])
{
	char	**path;
	char	**new_arg;
	int		fd;
	int		iter;

	(void)argc;
	path = ft_split(get_path(env), ':');
	if (!path)
		return (1);
	iter = 0;
	fd = open(argv[1], O_RDONLY);
	while (iter != argc - 3)
	{
		new_arg = get_new_arg(path, argv[2 + iter]);
		if (!new_arg)
		{
			free_split(path);
			return (1);
		}
		fd = creat_process(new_arg, env, fd);		//return pipefd[0]
		free_split(new_arg);
		iter++;
	}
	char c;
	int write_file = open(argv[argc - 1], O_WRONLY);
	while (read(fd, &c, 1))
		write(write_file, &c, 1);
	close(fd);
	return (0);
}
