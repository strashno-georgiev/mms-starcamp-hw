#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
//------------------------------------------------------------------------
// NAME: Kaloyan Georgiev
// CLASS: XIb
// NUMBER: 18
// PROBLEM: #1
// FILE NAME: main.c (unix file name)
// FILE PURPOSE:
// Realizaciya na tail
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// FUNCTION: secure_write (име на функцията)
// осигурява автоматично частичното писане, връща -1 при грешка
// PARAMETERS:
// приема файлов дескриптор на файла fd, низ s и големината му int len
//------------------------------------------------------------------------
int secure_write(int fd, char* s, int len) {
	int res = write(fd, s, len);
	while(res < len) {
		if(res < 0) {
			return -1;
		}
		else {
			res = write(fd, s, len);
		}
	}
	return 0;
}

//------------------------------------------------------------------------
// FUNCTION: print_last_l (име на функцията)
// изкарва на стандартния изход последните int lines на брой реда от text
// PARAMETERS:
// низ text, дължината му int len, брой редове int lines
//------------------------------------------------------------------------
void print_last_l(char* text, int len, int lines) {
	int i, count=0;
	for(i=len-1; i > 0; i--) {
		//write(STDOUT_FILENO, text+i, 1);
		if(text[i] == '\n') {
			count++;
		}
		if(count == lines+1) {
			break;
		}
	}
	for(int j=i+1; j < len; j++) {
		secure_write(STDOUT_FILENO, text+j, 1);
	}
}
//------------------------------------------------------------------------
// FUNCTION: count_lines_s (име на функцията)
// връща броя на редовете в подадения низ
// PARAMETERS:
// приема низ text и дължината му int len
//------------------------------------------------------------------------
int count_lines_s(char* text, int len) {
	int count=0;
	for(int i=0; i < len; i++) {
		if(text[i] == '\n') {
			count++;
		}
	}
	return count;
}
//------------------------------------------------------------------------
// FUNCTION: count_lines (име на функцията)
// връща броя на редовете в подадения файл или -1 при грешка
// PARAMETERS:
// приема файлов дескриптор на файла fd
//------------------------------------------------------------------------
int count_lines(int fd) {
	int res, count=0;
	char buffer[1024];
	while((res = read(fd, buffer, 1024)) != 0) {
		if(res < 0) {
			return -1;
		}
		count += count_lines_s(buffer, res);
	}
	lseek(fd, 0, SEEK_SET);
	return count;
}
//------------------------------------------------------------------------
// FUNCTION: tenl (име на функцията)
// премахва първите 10-н реда (подравнява съдържанието с дължината на първите 10-н реда назад) в низ с н реда (н>10)
// връща броя на премахнатите символи
// PARAMETERS:
// низ text и дължината му int size
//------------------------------------------------------------------------
//trunctate extra newlines
int tenl(char* text, int size) {
	int count = count_lines_s(text, size);
	if(count > 10) {
		int i, j, nlcount = 0;
		for(i = 0; nlcount < count - 10; i++ ) {
			if(text[i] == '\n') {
				nlcount++;
			}
		}
		//i++;
		for(j = 0; j < size-i; j++) {
			text[j] = text[j+i];
		}
		return i;
	}
	return 0;
}
//------------------------------------------------------------------------
// FUNCTION: tail (име на функцията)
// изкарва последните 10 реда от подадения файл на стандартния изход, връща -1 при грешка при четене и -2 при грешка при писане
// PARAMETERS:
// приема файлов дескриптор на файла fd
//------------------------------------------------------------------------
int tail(int fd) {
	if(fd == STDIN_FILENO) {
		size_t buffsize = 2048;
		char* buffer = malloc(buffsize);
		size_t rds = 1024;
		size_t offset = 0;
		int res;
		while((res = read(fd, buffer + offset, rds)) != 0) {
			if(res < 0) {
				//read error
				free(buffer);
				return -1;
			}
			offset += res;
			int trunct = tenl(buffer, offset);
			offset -= trunct;
			if(offset + rds > buffsize) {
				buffer = realloc(buffer, buffsize *= 2);
			}
		}
		res = secure_write(STDOUT_FILENO, buffer, offset);
		if(res < 0) {
			//write error
			free(buffer);
			return -2;
		}
		free(buffer);

	}
	else {
		int line_count = count_lines(fd);
		if(line_count < 0) {
			//read error;
			return -1;
		}
		int culc = 0;
		char buffer[1024];
		int res;
		if(line_count > 10) {
			while(culc < line_count - 10 && (res = read(fd, buffer, 1024)) != 0) {
				if(res < 0) {
					return -1;
				}
				culc += count_lines_s(buffer, res);
			}
			int overlap = 10 - (line_count - culc);
			print_last_l(buffer, res, overlap);
		}
		while((res = read(fd, buffer, 1024)) != 0) {
			if(res < 0) {
				return -1;
			}
			secure_write(STDOUT_FILENO, buffer, res);
		}
	}
	return 0;
}

void open_err(char* filename) {
	char first[] = "tail: cannot open '";
	char last[] = "' for reading";
	int errlen = strlen(first) + strlen(filename) + strlen(last);
	char errm[errlen+1];
	strcpy(errm, first);
	strcat(errm, filename);
	strcat(errm, last);
	errm[errlen] = '\0';
	perror(errm);
}
void write_err(char* filename) {
	char first[] = "tail: error writing '";
	char last[] = "'";
	int errlen = strlen(first) + strlen(filename) + strlen(last);
	char errm[errlen+1];
	strcpy(errm, first);
	strcat(errm, filename);
	strcat(errm, last);
	errm[errlen] = '\0';
	perror(errm);
}

void read_err(char* filename) {
	char first[] = "tail: error reading '";
	char last[] = "'";
	int errlen = strlen(first) + strlen(filename) + strlen(last);
	char errm[errlen+1];
	strcpy(errm, first);
	strcat(errm, filename);
	strcat(errm, last);
	errm[errlen] = '\0';
	perror(errm);

}
int main(int argc, char* argv[]) {
		if(argc == 1) {
			int res;
			res = tail(STDIN_FILENO);
			if(res == -1) {
				read_err("standard input");
			}
			else if(res == -2) {
				write_err("standard output");
			}
		}
		else if(argc > 1) {
			char* output = "standard output";
			char* filename;
			int fd;
			for(int i=1; i < argc; i++) {
				if(strcmp(argv[i], "-") == 0) {
					fd = STDIN_FILENO;
					filename = "standard input";
				}
				else {
					fd = open(argv[i], O_RDONLY);
					filename = argv[i];
					if(fd < 0) {
						open_err(argv[i]);
						continue;
					}
				}
				int res;
				if(argc > 2) {
					if(i > 1) {
						res = secure_write(STDOUT_FILENO, "\n", 1);
						if(res < 0) {
							write_err(output);
						}
					}
					res = secure_write(STDOUT_FILENO, "==> ", 4);
					if(res < 0) {
						write_err(output);
					}
					res = secure_write(STDOUT_FILENO, filename, strlen(filename));
					if(res < 0) {
						write_err(output);
					}
					res = secure_write(STDOUT_FILENO, " <==\n", 5);
					if(res < 0) {
						write_err(output);
					}
				}
				res = tail(fd);
				if(res == -1) {
					read_err(filename);
				}
				else if(res == -2) {
					write_err(output);
				}
				close(fd);
			}
		}
}
