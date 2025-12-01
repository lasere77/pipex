/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mewen <mewen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 09:35:56 by mcolin            #+#    #+#             */
/*   Updated: 2025/12/01 23:18:40 by mewen            ###   ########.fr       */
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
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

static int	main_loop(int argc, char *argv[], char **path, int fd)
{
	char	**new_arg;
	int		iter;

	iter = 0;
	while (iter != argc - 3)
	{
		new_arg = get_new_arg(path, argv[2 + iter]);
		if (!new_arg)
		{
			free_split(path);
			exit(EXIT_FAILURE);
		}
		fd = creat_process(new_arg, &argv[argc + 1], fd);
		free_split(new_arg);
		iter++;
	}
	return (fd);
}

/*
./pipex infile "grep 1" "grep je" "wc -w" outfile && cat outfile
< infile grep 1 | grep je | wc -w > outfile  && cat outfile

./pipex infile "cat" outfile && cat outfile
./pipex infile "grep fd" outfile && cat outfile
TO DO:

BONUS:
	gnl for <<
*/
int	main(int argc, char *argv[], char *env[])
{
	char	**path;
	int		fd;

	path = ft_split(get_path(env), ':');
	if (!path)
		return (EXIT_FAILURE);
	fd = main_loop(argc, argv, path, open_input_file(argv[1]));
	free_split(path);
	write_in_file(argv[argc - 1], fd);
	close(fd);
	return (0);
}
