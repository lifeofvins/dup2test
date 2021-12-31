/*
 * Author: Vincenzo Sagristano
 */

/*
 * dup2test - test for dup2 syscall.
 * 
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define TEST_SECTION 0

int main()
{
#if TEST_SECTION
	const char *out_text = "\"And what marks did you see by the wicket-gate?\"\n"
						   "\"None in particular.\"\n"
						   "\"Good heaven! Did no one examine?\"\n"
						   "\"Yes, I examined, myself.\"\n"
						   "\"And foud nothing?\"\n"
						   "\"It was all very confused. Sir Charles had evidently stood there for five or ten minutes.\"\n"
						   "\"How do you know that?\"\n"
						   "\"Because the ash had twice dropped from his cigar.\"\n";
	const char *filename = "/dup-2-test.txt";

	int fd1;
#else
	int fd2, fd3;
	char buf[256];
	int actually_read = 0;
#endif

#if TEST_SECTION
	if ((fd1 = open(filename, O_CREAT | O_RDWR, "777")) == -1)
	{
		printf("Error opening %s\n", filename);
		return -1;
	}
	dup2(fd1, STDOUT_FILENO);
	printf("%s", out_text);
#else
	if ((fd2 = open("aaa.txt", O_CREAT | O_RDWR, "777")) == -1)
	{
		printf("Error opening aaa.txt\n");
		return -1;
	}

	if ((fd3 = open("x.txt", O_CREAT | O_RDWR, "777")) == -1)
	{
		printf("Error opening x.txt\n");
		return -1;
	}
	dup2(fd2, STDIN_FILENO);
	dup2(fd3, STDOUT_FILENO);

	write(STDIN_FILENO, "ciao", 4);
	
	actually_read = read(STDOUT_FILENO, buf, 255);
	buf[actually_read] = '\0';
	write(STDIN_FILENO, buf, sizeof(buf)-8);
	close(fd2);
	close(fd3);
#endif
	return 0;
}
