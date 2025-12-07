/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 09:35:56 by mcolin            #+#    #+#             */
/*   Updated: 2025/12/07 12:11:19 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arg.h"
#include "cmd.h"
#include "utils.h"
#include "utils_cmd.h"
#include "process.h"

static void	write_in_file(char *file_path, int fd)
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

static int	open_input_file(char *file_path)
{
	int	fd;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		perror("open");
	return (fd);
}

static int	exec_cmd(t_cmd *cmd, int fd)
{
	pid_t	*list_pid;
	size_t	i;

	list_pid = malloc(sizeof(pid_t) * (get_nb_cmd(cmd) + 1));
	if (!list_pid)
		return (-1);
	i = 0;
	while (i < get_nb_cmd(cmd))
	{
		fd = do_child(cmd, i, fd, &list_pid[i]);
		i++;
	}
	wait_child(cmd, list_pid);
	free(list_pid);
	return (fd);
}

int	main(int argc, char *argv[], char *env[])
{
	t_cmd	*cmd;
	int		fd;
	int		status;

	cmd = set_cmd(argc, argv, env);
	if (!cmd)
		return (1);
	fd = open_input_file(argv[1]);
	fd = exec_cmd(cmd, fd);
	status = cmd[get_nb_cmd(cmd) - 1].status;
	unset_cmd(cmd);
	write_in_file(argv[argc - 1], fd);
	if (fd >= 0)
		close(fd);
	if (!is_last_cmd_valid(argc, argv, env))
		return (127);
	return (WEXITSTATUS(status));
}
