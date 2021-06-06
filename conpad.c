// SPDX-License-Identifier: MIT
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

void usage() {
	puts("Concatenate contents from all arguments and print to stdout.");
}

int main(int argc, char *argv[])
{
	const int padding = 1;

	if (argc < 2) {
		usage();
		return 1;
	}

	for (int i = 1; i < argc; i++) {
		if (access(argv[i], R_OK) == -1) {
			if (errno == ENOENT) {
				fprintf(stderr, "%s: File does not exist.", argv[i]);
				return 1;
			} else if (errno == EACCES) {
				fprintf(stderr, "%s: Access denied.", argv[i]);
				return 1;
			} else {
				fprintf(stderr, "%s: Unknown error: %d", argv[i], errno);
				return 1;
			}
		}
	}
	
	FILE *f;
	char *buf = 0;
	long len = 0;
	long pos = 0;
	for (int i = 1; i < argc; i++) {
		int fn_len = strlen(argv[i]);
		f = fopen(argv[i], "r");
		if (f) {
			fseek(f, 0, SEEK_END);
			int f_len = ftell(f);
			
			if (i < argc - 1)
				len += f_len + padding + fn_len + 5; // Prev. size + file size + padding + \n + file name + header
			else
				len += f_len + fn_len + 5; // Prev. size + file size + \n + file name + header
				
			fseek(f, 0, SEEK_SET);
			buf = realloc(buf, len);

			if (buf) {
				strcpy(buf + pos, "### ");
				pos += 4;
				strcpy(buf + pos, argv[i]);
				pos += fn_len;
				buf[pos++] = '\n';

				fread(buf + pos, 1, f_len, f);
				pos += f_len;

				if (i < argc - 1) {
					for (int j = 0; j < padding; j++)
						buf[pos++] = '\n';
				}
			}
			fclose(f);
		}
	}

	fputs(buf, stdout);
	free(buf);

	return 0;
}

