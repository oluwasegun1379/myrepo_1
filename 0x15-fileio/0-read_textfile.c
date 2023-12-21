#include "main.h"
/**
 * 0-read_textfile - reads the textfile and print the letters to the console.
 * @filename: the name of the file created.
 * @letters: numbers of letters printed to the console.
 * Return: numbers of letters printed, return 0 if fails.
 */
ssize_t read_textfile(const char *filename, size_t letters)
{
	int fd;
	ssize_t nwr, nrd;
	char *buf;

	// Check if filename is NULL
	if (!filename)
		return (0);

	// Open the file in read-only mode
	fd = open(filename, O_RDONLY);

	// Check if the file couldn't be opened
	if (fd == -1)
		return (0);

	// Allocate memory for the buffer
	buf = malloc(sizeof(char) * (letters));

	// Check if memory allocation fails
	if (!buf)
		return (0);

	// Read 'letters' number of characters from the file into the buffer	
	nrd = read(fd, buf, letters);

	// Write the read characters to the standard output (console)
	nwr = write(STDOUT_FILENO, buf, nrd);

	// Close the file descriptor
	close(fd);

	// Free the allocated buffer memory
	free(buf);

	return (nrd);
}
