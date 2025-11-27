/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 10:00:00 by mcolin            #+#    #+#             */
/*   Updated: 2025/11/27 16:38:03 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"
#include "libft/libft.h"

#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void    creat_process(char **argv, char *env[], int *fd_infile)
{
	int		pipefd[2];
    pid_t	cpid;

    // for (int i = 0; argv[i]; i++)
    //     printf("%s\n", argv[i]);
    if (pipe(pipefd) == -1)
	{
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    cpid = fork();
    if (cpid == -1)
	{
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (cpid == 0)
	{
        dup2(*fd_infile, stdin->_fileno);   /*replace stdin par fd_infile*/
        
        close(pipefd[0]);
        // write(pipefd[1], )
        *fd_infile = pipefd[1];
        execve(argv[0], argv, env);
    }
	else
	{
        close(pipefd[0]);
        // pipefd[1] = *fd_infile;
        close(pipefd[1]);
        wait(NULL);
    }
}
