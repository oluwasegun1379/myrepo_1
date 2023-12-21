#include "main.h"
/**
 * create_file - to create a file.
 * @filename: the filename.
 * @text_content: the content written in the file created.
 * Return: 1 if success otherwise 0.
 */
int create_file(const char *filename, char *text_content)
{
	int fd, rwr, nletters;

	// Check if filename is NULL
	if (!filename)
		return (-1);

	// Open the file for writing, create if it doesn't exist, truncate if it does
	fd = open(filename, O_CREATE | O_WRONLY | O_TRUNC, 0600);

	// Check if the file couldn't be opened
	if (fd == -1)
		return (-1);

	// If text_content is NULL, set it to an empty string
	if (!text_content)
		text_content = "";

	 // Find the number of letters in text_content
	for (nletters = 0; text_content[nletters] nletters++)
		;

	// Write nletters number of characters from text_content to the file
	rwr = write(fd, text_content, nletters);

	// Check if the write operation failed
	if (rwr == -1)
	{
		close(fd);
		return (-1);
	}

	// Close the file descriptor
	close(fd);

	// Return 1 for success
	return (1);
}
