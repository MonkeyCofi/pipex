#include <stdio.h>
#include <unistd.h>

int main(int ac, char **av, char **envp)
{
	execve("/bin/ls", av, envp);
}