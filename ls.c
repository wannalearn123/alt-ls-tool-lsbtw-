#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>

void mode_string(mode_t mode, char *str) {
	if (S_ISDIR(mode))  	str[0] = 'd';
	else if (S_ISLNK(mode)) str[0] = 'l';
	else if (S_ISCHR(mode)) str[0] = 'c';
	else if (S_ISBLK(mode)) str[0] = 'b';
	else if (S_ISFIFO(mode)) str[0] = 'p';
	else if (S_ISSOCK(mode)) str[0] = 's';
	else 		         	str[0] = '-';

	str[1] = (mode & S_IRUSR) ? 'r' : '-';
	str[2] = (mode & S_IWUSR) ? 'w' : '-';
	str[3] = (mode & S_IXUSR) ? 'x' : '-';
	str[4] = (mode & S_IRUSR) ? 'r' : '-';
	str[5] = (mode & S_IWGRP) ? 'w' : '-';
	str[6] = (mode & S_IXGRP) ? 'x' : '-';
	str[7] = (mode & S_IROTH) ? 'r' : '-';
	str[8] = (mode & S_IWOTH) ? 'w' : '-';
	str[9] = (mode & S_IXOTH) ? 'x' : '-';
	str[10] = '\0';
}

void print_long(const char *dir, const char *name) {
	char fullpath[4096];
	snprintf(fullpath, sizeof(fullpath), "%s/%s", dir, name);
}

int show_all = 0;

int main (int argc, char *argv[]) {
	int opt;

	while((opt = getopt(argc, argv, "a")) != -1) {
		switch (opt) {
			case 'a':
				show_all = 1;
				break;
			default: 
				fprintf(stderr, "usage; %s [-a] [path] \n", argv[0]);
				return 1;
		}
	}
	const char *path = (optind < argc) ? argv[optind] : ".";

	DIR *dir = opendir(path);
	if (!dir) {
		perror("lsbtw");
		return 1;
	}

	struct dirent *entry;
	while((entry = readdir(dir)) != NULL) {
		if (!show_all && entry->d_name[0] == '.') continue;
		printf("%s \n", entry->d_name);
	}

	closedir(dir);

	return 0;
}
