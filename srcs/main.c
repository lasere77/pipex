/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 09:35:56 by mcolin            #+#    #+#             */
/*   Updated: 2025/12/05 10:26:29 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"
#include "arg.h"

static void	write_in_file(char *file_path, int fd)
{
	int		write_file;
	char	c;

	unlink(file_path);
	write_file = open(file_path, O_RDONLY | O_WRONLY | O_CREAT, 0644);
	while (read(fd, &c, 1))
		write(write_file, &c, 1);
	close(write_file);
}

static int	open_input_file(char *file_path)
{
	int	fd;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		perror("open");
	return (fd);
}

static int	wait_child(int nb_child, pid_t *tab_pid)
{
	int	i;
	int	status;

	i = 0;
	while (i != nb_child)
		waitpid(tab_pid[i++], &status, 0);
	return (status);
}

static int	main_loop(int argc, char *argv[], char **path, int *fd)
{
	char	**new_arg;
	pid_t	*tab_pid;
	int		iter;
	int		status;

	tab_pid = malloc(sizeof(pid_t) * (argc - 3 + 1));
	if (!tab_pid)
		return (-1);
	iter = 0;
	while (iter != argc - 3)
	{
		new_arg = get_new_arg(path, argv[2 + iter]);
		if (!new_arg)
		{
			free_split(path);
			exit(EXIT_FAILURE);
		}
		*fd = creat_process(new_arg, &argv[argc + 1], *fd, &tab_pid[iter]);
		free_split(new_arg);
		iter++;
	}
	status = wait_child(argc - 3, tab_pid);
	free(tab_pid);
	return (status);
}

int	main(int argc, char *argv[], char *env[])
{
	char	**path;
	int		fd;
	int		status;

	path = ft_split(get_path(env), ':');
	if (!path)
		return (EXIT_FAILURE);
	fd = open_input_file(argv[1]);
	status = main_loop(argc, argv, path, &fd);
	free_split(path);
	write_in_file(argv[argc - 1], fd);
	close(fd);
	return (WEXITSTATUS(status));
}
