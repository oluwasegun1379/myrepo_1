#include "main.h"
/**
 * append _text_to_file - add or append new text at the end of a file.
 * @filename: the filename.
 * @text_content: the new content to be added.
 * Return: 1 if the file exits, -1 if file does not exist.
 */
int append_text_to_file(const char *filename, char *text_content)
{
	int fd, rwr, nletters;

	// Check if filename is NULL
	if (!filename)
		return (-1);

	// Open the file for writing, append to the end
	fd = open(filename, O_WRONLY | O_APPEND);

	// Check if the file couldn't be opened
	if (fd == -1)
		return (-1);

	// If text_content is not NULL
	if (text_content)
	{
		// Find the number of letters in text_content
		for (nletters = 0; text_content[nletters]; nletters++)
			;

		// Write nletters number of characters from text_content to the file
		rwr = write(fd, text_content, nletters);

		// Check if the write operation failed
		if (rwr == -1)
		{
			close(fd);
			return (-1);
		}
	}

	// Close the file descriptor
	close(fd);

	 // Return 1 for success
	return(1);
}
