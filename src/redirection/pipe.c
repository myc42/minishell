

#include "../../includes/minishell.h"

int	handle_pipe(char **tab_argv)
{
	int i;
	int fd;
	int pipe_fd[2];
	pid_t pid ;
	

	i = 0;
	fd = 0;
	pid = fork();
	
	while (tab_argv[i])
	{
		if (ft_strncmp(tab_argv[i], "|", ft_strlen(tab_argv[i])))
		{
			pipe(pipe_fd);
			if (pid == 0)
			{
				dup2(fd, 0);
				close(pipe_fd[0]);
			}
			else
			{
				wait(NULL);
				close(pipe_fd[1]);
				fd = pipe_fd[0];
			}
		}
		i++;
	}
	return (0);
}