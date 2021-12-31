/*
 * Author: Vincenzo Sagristano
 */

/*
 * dup2test - test for dup2 syscall.
 *
 * This test aims to perform a dup2 call such that
 * it's possible to use printf/scanf to make r/w operations
 * on a file (which filename is hardcoded for the sake of simplicity).
 * 
 * Check the file in the /.//.//. location to understand if the operation worked.
 * The final content of the file should be:
 * 
 * --Using printf...--
 * "And what marks did you see by the wicket-gate?"
 * "None in particular."
 * "Good heaven! Did no one examine?"
 * "Yes, I examined, myself."
 * "And foud nothing?"
 * "It was all very confused. Sir Charles had evidently stood there for five or ten minutes."
 * "How do you know that?"
 * "Because the ash had twice dropped from his cigar."
 * 
 * --Using puts...--
 * "And what marks did you see by the wicket-gate?"
 * "None in particular."
 * "Good heaven! Did no one examine?"
 * "Yes, I examined, myself."
 * "And foud nothing?"
 * "It was all very confused. Sir Charles had evidently stood there for five or ten minutes."
 * "How do you know that?"
 * "Because the ash had twice dropped from his cigar."
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

int main()
{
	const char *out_text = "\"And what marks did you see by the wicket-gate?\"\n"
						   "\"None in particular.\"\n"
						   "\"Good heaven! Did no one examine?\"\n"
						   "\"Yes, I examined, myself.\"\n"
						   "\"And foud nothing?\"\n"
						   "\"It was all very confused. Sir Charles had evidently stood there for five or ten minutes.\"\n"
						   "\"How do you know that?\"\n"
						   "\"Because the ash had twice dropped from his cigar.\"\n";
	const char *filename = "/dup-2-test.txt";
	int fd1, fd2, fd3;
	char buf[256];
	int actually_read = 0;

	if ((fd1 = open(filename, O_CREAT | O_RDWR, "777")) == -1)
	{
		printf("Error opening %s\n", filename);
		return -1;
	}

	if ((fd2 = open("aaa.txt", O_CREAT | O_RDWR, "777")) == -1)
	{
		printf("Error opening aaa.txt\n");
		return -1;
	}

	if ((fd3 = open("x.txt", O_CREAT | O_APPEND | O_RDWR, "777")) == -1)
	{
		printf("Error opening aaa.txt\n");
		return -1;
	}

	dup2(fd1, STDOUT_FILENO);
	dup2(fd2, STDIN_FILENO);
	dup2(fd3, STDOUT_FILENO);

	write(STDIN_FILENO, "ciao", 4);
	actually_read = read(STDOUT_FILENO, buf, 255);
	buf[actually_read] = '\0';
	printf("%s", out_text);
	printf("%s", buf);

	close(fd2);

	return 0;
}