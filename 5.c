#include <stdlib.h>
#include <libgen.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct
{
    int fd;
    off_t lines_count;
    off_t* offset;
    off_t* size;
} FileTable;

const int BUFFER_SIZE = 6;

size_t file_size(int fd)
{
    size_t cnt = 0;
    char buf[BUFFER_SIZE];
    int nbytes = read(fd, buf, BUFFER_SIZE);

    while (nbytes > 0)
    {
        for (const char* ch = buf; ch < buf + BUFFER_SIZE; ch++)
        {
            if (*ch == '\n')
            {
                cnt++;
            }
        }

        nbytes = read(fd, buf, BUFFER_SIZE);
    }
    lseek(fd, 0, SEEK_SET);
    return cnt;
}

FileTable* read_file(const char* name)
{
    FileTable* file = (FileTable*) malloc(sizeof(FileTable));


    if (!file)
    {
        return NULL;
    }


    file->fd = open(name, O_RDONLY);

    if (file->fd == -1)
    {
        free(file);
        return NULL;
    }

    size_t tfile_size = file_size(file->fd);
    file ->offset = (off_t*)malloc(tfile_size*sizeof(off_t));
    file ->size = (off_t*)malloc(tfile_size*sizeof(off_t));

    if (file->offset == NULL || file->size == NULL)
    {
        return NULL;
    }
    file->lines_count = 1;
    file->offset[0] = 0;
    char buf[BUFFER_SIZE];
    off_t i = 0, line_offset = 0;
    int nbytes = read(file->fd, buf, BUFFER_SIZE);

    while (nbytes > 0)
    {
        for (const char* ch = buf; ch < buf + BUFFER_SIZE; ch++)
        {
            i++;

            if (*ch == '\n')
            {
                file->size[file->lines_count-1] = i;
                line_offset += i;
                file->offset[file->lines_count] = line_offset;
                file->lines_count++;
                i = 0;
            }
        }

        nbytes = read(file->fd, buf, BUFFER_SIZE);
    }

    if (nbytes == -1)
    {
        close(file->fd);
        free(file);
        return NULL;
    }

    printf("File size: %d lines\n", file->lines_count);
    return file;
}

int get_request()
{
    printf("Enter line number (0 for exit): ");
    int res;

    if (scanf("%d", &res) == EOF)
    {
        return -1;
    }
    else
    {
        return res;
    }
}

int main(int argc, char** argv)
{
   /* if (argc != 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return 0;
    }*/


    FileTable* file = read_file("text.txt");

    if (!file)
    {
        perror("Can't read the input file");
        return 0;
    }

    int string_number;

    do
    {
        string_number = get_request();

        if (string_number < 0)
        {
            puts("Bad line number, aborted.\nERROR");
        }
        else if (file->lines_count < string_number)
        {
            puts("Line not found\nERROR");
            break;
        }
        else if (string_number > 0)
        {
            off_t len = file->size[string_number-1];

            for (off_t i = 0; i < len; i += BUFFER_SIZE)
            {
                char buf[BUFFER_SIZE];
                off_t chunk = (len - i > BUFFER_SIZE)? BUFFER_SIZE : len - i;

                if (lseek(file->fd, file->offset[string_number-1] + i, SEEK_SET) == -1 || read(file->fd, buf, chunk) != chunk)
                {
                    perror("Reading error");
                    puts("ERROR");
                    close(file->fd);
                    free(file);
                    return 1;
                }

                write(STDIN_FILENO, buf, chunk);
            }

            puts("OK");
        }
    }
    while (string_number > 0);

    close(file->fd);
    free(file);
    return 0;
}
