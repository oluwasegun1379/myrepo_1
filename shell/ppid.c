#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	pid_t parent_pid;

	parent_pid = getppid();
	printf("%u\n", parent_pid);

	return (0);
}

