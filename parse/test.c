#include <stdio.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>

int	main(void)
{
	int	fd[2];

	pipe(fd);

	int	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
		printf("hello33\n");
	}
	else
	{
		wait(NULL);
		close(fd[1]);
	}

	int	qid = fork();
	if (qid == 0)
	{
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
		char	**args = malloc (sizeof(char *) * 2);
		args[0] = malloc (5);
		args[0] = "grep";
		args[1] = malloc (2);
		args[1] = "h";
		char	*envs[] = {NULL};
		execve("/usr/bin/grep", args, envs);
	}
	else
	{
		close(fd[1]);
	}
}