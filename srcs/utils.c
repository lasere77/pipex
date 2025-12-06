/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 17:41:03 by mcolin            #+#    #+#             */
/*   Updated: 2025/12/06 20:19:02 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	panic_free(t_cmd *cmd, pid_t *list_pid)
{
	unset_cmd(cmd);
	free(list_pid);
	exit(EXIT_FAILURE);
}

char	is_last_cmd_valid(int argc, char *argv[], char *env[])
{
	char	**path;
	char	*bin_path;
	char	**new_arg;

	path = ft_split(get_path(env), ':');
	if (!path)
		return (0);
	new_arg = ft_split(argv[argc - 2], ' ');
	bin_path = get_bin_path(path, new_arg[0]);
	free_split(path);
	free_split(new_arg);
	if (!bin_path)
		return (0);
	free(bin_path);
	return (1);
}

void	free_split(char **strs)
{
	size_t	i;

	i = 0;
	if (strs)
	{
		while (strs[i])
			free(strs[i++]);
		free(strs);
	}
}

void	write_in_file(char *file_path, int fd)
{
	char	c;
	int		write_file;

	unlink(file_path);
	write_file = open(file_path, O_RDONLY | O_WRONLY | O_CREAT, 0644);
	if (write_file == -1)
		return ;
	while (read(fd, &c, 1))
		write(write_file, &c, 1);
	close(write_file);
}

int	open_input_file(char *file_path)
{
	int	fd;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		perror("open");
	return (fd);
}
