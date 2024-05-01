#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include "libft/libft.h"
#include "newshell.h"
void	make_string(char ***s, char *a, char *b)
{
	int	a_length = strlen(a);
	int b_length = strlen(b);
	*s = malloc (sizeof(char *) * 2);
	(*s)[0] = malloc (a_length + 1);
	memcpy((*s)[0], a, a_length);
	(*s)[0][a_length] = 0;
	(*s)[1] = malloc (b_length + 1);
	memcpy((*s)[1], b, b_length);
	(*s)[1][b_length] = 0;	
}

//typedef struct	s_pipe
//{
//	int	fd[2];
//}				t_pipe;

void	set_tunnel(t_pipe *test)
{
	close(test[0].fd[0]);
	close(test[1].fd[0]);
	close(test[1].fd[1]);
	dup2(test[0].fd[1], 1);
	close(test[0].fd[1]);
}

void	set_tunnel2(t_pipe *test)
{
	close(test[0].fd[1]);
	close(test[1].fd[0]);
	dup2(test[0].fd[0], 0);
	dup2(test[1].fd[1], 1);
	close(test[0].fd[0]);
	close(test[1].fd[1]);
}

void	set_tunnel3(t_pipe *test)
{
	close(test[0].fd[0]);
	close(test[0].fd[1]);
	close(test[1].fd[1]);
	dup2(test[1].fd[0], 0);
	close(test[1].fd[0]);
}

void	execute(t_pipe *test)
{
	int		pid;
	char	**arg1;
	char	*env[] = {NULL};
	int		status;
	int		ret;
	make_string(&arg1, "echo", "\"cat lol.c | ls -la\"");
	pid = fork();
	if (pid == 0)
	{
		//close(test[0].fd[0]);
		//dup2(test[0].fd[1], 1);
		//close(test[0].fd[1]);
		//set_tunnel(test);
		execve("/usr/bin/echo", arg1, env);
	}
	else
	{
		ret = waitpid(0, &status, 0);
		//wait(NULL);
		
	}
}

void	execute2(t_pipe *test)
{
	int		pid;
	char	**arg1;
	char	*env[] = {NULL};
	int status;
	int	ret;
	make_string(&arg1, "grep", "new");
	pid = fork();
	if (pid == 0)
	{
		set_tunnel2(test);
		execve("/usr/bin/grep", arg1, env);
	}
	else
	{
		close(test[0].fd[1]);
		close(test[1].fd[1]);
		ret = waitpid(0, &status, 0);
	}
}

void	execute3(t_pipe *test)
{
	int		pid;
	char	**arg1;
	char	*env[] = {NULL};
	int status;
	int	ret;
	make_string(&arg1, "grep", "1507");
	pid = fork();
	if (pid == 0)
	{
		set_tunnel3(test);
		execve("/usr/bin/grep", arg1, env);
	}
	else
	{
		close(test[0].fd[0]);
		close(test[0].fd[1]);
		close(test[1].fd[0]);
		close(test[1].fd[1]);
		ret = waitpid(0, &status, 0);
	}
}

int	get_no_of_pipes(char *s)
{
	int		count;
	char	c;
	bool	quote;

	c = '|';
	count = 0;
	quote = false;
	while (*s)
	{
		if (*s == '"' && !quote)
		{
			c = '"';
			quote = true;
			s++;
		}
		else if (*s == '"' && quote)
		{
			c = '|';
			quote = false;
		}

		if (*s == c)
			count++;
		s++;
	}
	return (count);
}

// int get_no_of_redirection(char *s)
// {
// 	int		cnt;
// 	bool	quote;
	
// 	cnt = 0;
// 	quote = false;
// 	while (*s)
// 	{
// 		if (ft_strncmp(s, "<<", 2) == 0)
// 		{
// 			cnt++;
// 			s++;
// 		}
// 		else if (ft_strncmp(s, ">>", 2) == 0)
// 		{
// 			cnt++;
// 			s++;
// 		}
// 		else if (ft_strncmp(s, "<", 1) == 0)
// 			cnt++;
// 		else if (ft_strncmp(s, ">", 1) == 0)
// 			cnt++;
// 		s++;
// 	}
// 	return (cnt);
// }

int get_no_of_redirection(char *s)
{
	int		cnt;
	bool	quote;
	
	cnt = 0;
	quote = false;
	while (*s)
	{
		if (*s == '"' && !quote)
		{
			quote = true;
			s++;
		}
		else if (*s == '"' && quote)
		{
			quote = false;
			s++;
		}
		if (!*s)
			return (cnt);
		if (!quote)
		{
			if (ft_strncmp(s, "<<", 2) == 0)
			{
				cnt++;
				s++;
			}
			else if (ft_strncmp(s, ">>", 2) == 0)
			{
				cnt++;
				s++;
			}
			else if (ft_strncmp(s, "<", 1) == 0)
				cnt++;
			else if (ft_strncmp(s, ">", 1) == 0)
				cnt++;
		}
		s++;
	}
	return (cnt);
}

void	init_tcmd(t_cmd ***t, int n)
{
	int	i;
	
	i = 0;
	(*t) = malloc (sizeof(t_cmd *) * (n));
	while (i < (n))
	{
		(*t)[i] = malloc (sizeof(t_cmd));
		i++;
	}
}

int	get_split_length(char **split_string)
{
	int	i;
	int	split_length;

	i = 0;
	split_length = 0;
	while (split_string[i])
	{
		split_length++;
		i++;
	}
	return (split_length);
}

void	set_pipe_head(t_pipe *tp, int cmd_index)
{
	int	i;

	i = 0;
	while (i < tp[0].n)
	{
		close(tp[i].fd[0]);
		if (i != 0)
			close(tp[i].fd[1]);
		i++;
	}
	dup2(tp[0].fd[1], 1);
	close(tp[0].fd[1]);
}

void	set_pipe_body(t_pipe *tp, int cmd_index)
{
	int	i;

	i = 0;
	while (i < tp[0].n)
	{
		if (i != cmd_index - 1)
			close(tp[i].fd[0]);
		if (i != cmd_index)
			close(tp[i].fd[1]);
		i++;
	}
	dup2(tp[cmd_index - 1].fd[0], 0);
	dup2(tp[cmd_index].fd[1], 1);
	close(tp[cmd_index - 1].fd[0]);
	close(tp[cmd_index].fd[1]);
}

void	set_pipe_tail(t_pipe *tp, int cmd_index)
{
	int	i;

	i = 0;
	while (i <tp[0].n)
	{
		if (i != tp[0].n - 1)
			close(tp[i].fd[0]);
		close(tp[i].fd[1]);
		i++;
	}
	dup2(tp[tp[0].n - 1].fd[0], 0);
	close(tp[tp[0].n - 1].fd[0]);
}

void	fork_and_run(t_cmd *t, t_pipe *tp, int cmd_index, t_cmd *tz)
{
	int	pid;
	int	ret;
	int	status;

	pid = fork();
	if (pid == 0)
	{
		if (cmd_index == 0)
		{
			set_pipe_head(tp, cmd_index);
		}
        if (cmd_index == tp[0].n)
		{
			set_pipe_tail(tp, cmd_index);
		}
		else
		{
			set_pipe_body(tp, cmd_index);
		}
		execve(t->cmd, t->arg, t->env);
		return ;
	}
	else
	{
		if (cmd_index != 0)
			close(tp[cmd_index - 1].fd[1]);
		waitpid(0, &tz->status, 0);
	}
}

char	*get_execute_path(char *split_string)
{
	struct stat	buf;
	char		*value;
	char		**split_env;
	char 		*finding_cmd;
	int			i;

	if (stat(split_string, &buf) == 0) /*현재 폴더에 있다면*/
		finding_cmd = split_string;
	else /*없다면 PATH 검색*/
	{
		value = getenv("PATH");
		split_env = ft_split(value, ':');
		i = 0;
		while (split_env[i])
		{
			finding_cmd = ft_strjoin(split_env[i], ft_strjoin("/", split_string));
			if (stat(finding_cmd, &buf) == 0)
				break;
			else
				*finding_cmd = 0;
			i++;
		}
	}
	return (finding_cmd);
}

void	echo(char **arg)
{
	int	i;
	bool newline;

	i = 1;
	newline = true;

	if (ft_strncmp(arg[1], "-n", 2) == 0)
	{
		i = 2;
		newline = false;
	}
	while (arg[i])
	{
		printf("%s ", arg[i]);
		i++;
	}
	if (newline)
		printf("\n");
}

void	cd(char **arg)
{
	chdir(arg[1]);
}

void	pwd(char **arg)
{
	char	cwd[100];
	size_t	size = 100;
	getcwd(cwd, size);
	
	printf("%s\n", cwd);
}

void	env()
{
	extern char **environ;
	int	fd;

	for (int i = 0; environ[i]; i++)
		printf("%s\n", environ[i]);
	fd = open("environment", O_RDONLY, 0777);
}

void builtin_exit(t_cmd **t)
{
	int	i;
	free(t[0]->tp);
	
	i = 1;
	while (i < t[0]->ts->no_of_commands)
	{
		free(t[i]);
	}
	free(t[0]->ts);
	free(t);	
	exit(0);
}

void get_status(int status)
{
	printf("%d\n", status);
}

int	is_builtin(char *s)
{
	if (ft_strncmp("echo", s, 4) == 0)
		return (1);
	else if (ft_strncmp("cd", s, 2) == 0)
		return (2);
	else if (ft_strncmp("pwd", s, 3) == 0)
		return (3);
	else if (ft_strncmp("export", s, 6) == 0)
		return (4);
	else if (ft_strncmp("unset", s, 5) == 0)
		return (5);
	else if (ft_strncmp("env", s, 3) == 0)
		return (6);
	else if (ft_strncmp("exit", s, 4) == 0)
		return (7);
	else if (ft_strncmp("$?", s, 2) == 0)
		return (8);
	return (0);
}

void	export(char **arg)
{
	int	fd;

	fd = open("environment", O_WRONLY | O_APPEND | O_CREAT, 0777);
	write(fd, ft_strjoin(arg[1], "\n"), ft_strlen(arg[1]) + 1);
	close(fd);
}

void	handle_builtin(char **split_string, t_cmd **t, int status)
{
	int	no = is_builtin(split_string[0]);
	if (no)
	{
		if (no == 1)
		{
			echo(split_string);
		}
		else if (no == 2)
			cd(split_string);
		else if (no == 3)
			pwd(split_string);
		else if (no == 4)
			export(split_string);
		else if (no == 6)
			env();
		else if (no == 7)
			builtin_exit(t);
		else if (no == 8)
			get_status(status);
		return ;
	}
}

int	set_tcmd(t_cmd **t, char *src, int status)
{
	int		i;
	int		split_length;
	int 	string_length;
	char	**split_string;
	char	*join_string;

	split_string = ft_split_quote(src, ' '); /*arg(명령어 옵션) 쪼개기*/
	if (is_builtin(split_string[0]))
	{
		handle_builtin(split_string, t, status);
		return (0);
	}
	(*t)->cmd =  get_execute_path(split_string[0]); /*명령어의 경로 파악*/
	split_length = get_split_length(split_string); /*인자의 개수*/
	(*t)->arg = malloc (sizeof (char *) * split_length);
	i = 0;
	while (split_string[i])
	{
		string_length = ft_strlen(split_string[i]);
		(*t)->arg[i] = malloc ( string_length + 1);
		ft_memcpy((*t)->arg[i], split_string[i], string_length);
		(*t)->arg[i] = ft_strtrim((*t)->arg[i], "\"");
		(*t)->arg[i][string_length] = 0;
		i++;
	}
	(*t)->env = NULL;
	return (1);
}

void	init_pipes(t_pipe **tp, t_parse *ts)
{
	int	i;

	i = 0;
	(*tp) = malloc (sizeof(t_pipe) * ts->no_of_pipes);
	while (i < ts->no_of_pipes)
	{
		pipe((*tp)[i].fd);
		i++;
	}
	(*tp)[0].n = ts->no_of_pipes;
}

void	init_parse_parameter(t_parse *ts, char *s)
{
	ts->i = 0;
	ts->no_of_redirection = 0;
	ts->cmd_index = 0;
	ts->no_of_pipes = get_no_of_pipes(s);
	ts->no_of_commands = ts->no_of_pipes + 1;
	ts->split_pipe = ft_split_quote(s, '|'); // split string by pipe
}

void	execute_cmds(t_parse *ts, t_cmd **tcmd, char *s, t_pipe *tp)
{
	static int	status;
	while (ts->split_pipe[ts->i])
	{
		ts->no_of_redirection = get_no_of_redirection(s);
		//printf("%d\n", ts->no_of_redirection);
		if (ts->no_of_redirection == 0)
		{
			//명령어에 Redirection이 없다면
			if (set_tcmd(&tcmd[ts->i], ts->split_pipe[ts->i], status) == 0)
				return ;
			if (*(tcmd[ts->i]->cmd) == 0)
			{
				printf("Command not found\n");
				break;
			}
			// printf("%s =%s\n", tcmd[ts->i]->arg[0],tcmd[ts->i]->arg[1]);
			fork_and_run(tcmd[ts->i], tp, ts->cmd_index, tcmd[0]);
			status = tcmd[0]->status;
		}
		else
		{
			//명령어에 REDIRECTION이 있다면	
		}
		ts->i++;
		ts->cmd_index++; //몇번째 명령어인지 확인
	}
}

int	has_only_spaces(char *s)
{
	 while (*s)
	 {
		if (*s == ' ' || *s == '\t')
			;
		else
			return (0);
		s++;
	 }
	 return (1);
}

void	parse_command(char *s)
{
	t_cmd	**tcmd;
	t_pipe	*tp;
	t_parse *ts;

	ts = malloc (sizeof(t_parse));
	if (has_only_spaces(s))
		return ;
	init_parse_parameter(ts, s);
	init_tcmd(&tcmd, ts->no_of_commands);
	init_pipes(&tp, ts);
	tcmd[0]->tp = tp;
	tcmd[0]->ts = ts;
	execute_cmds(ts, tcmd, s, tp);	
}

int	has_andor(char *s)
{
	bool	quote;
	int		count;
	char	c;

	c = '&';
	count = 0;
	quote = false;
	while (*s)
	{
		if (*s == '"' && !quote)
		{
			quote = true;
			c = '"';
			s++;
		}
		else if(*s == '"' && quote)
		{
			quote = false;
			c = '&';
		}
		if (*s == c && !quote)
			count++;
		s++;
	}
	return (count);
}

int main(void)
{
	// char    *s = "echo \"cat lol.c | cat > lol.c\"";
	// parse_command(s);
	//char 	*s;
	// t_pipe	*test;
	// test = malloc (sizeof(t_pipe) * 2);

	

	//int		pid;
	//pipe(test[0].fd);
	//pipe(test[1].fd);
	while (1)
	{
		//printf("hello\n");
		char *s = readline("shell$ ");
		parse_command(s);
	}
	//	execute(test);
	//	execute2(test);
	//	execute3(test);
	//}
}
