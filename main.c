#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 30000

const char* read_file(size_t* size, const char* path)
{
    FILE* fp = fopen(path, "rb");
    fseek(fp, 0, SEEK_END);
    size_t fs = ftell(fp);
    rewind(fp);

    char* buf = malloc(fs+1);

    if(!buf)
    {
        printf("ERROR: Couldn't allocate memory for file buffer!!!\n");
        return NULL;
    }

    if(fread(buf, 1, fs, fp) != fs)
    {
        printf("ERROR: Couldn't read file!!!\n");
        return NULL;
    }

    fclose(fp);

    *size = fs;
    buf[fs] = '\0';
    return buf;
}

int main(int argc, char* argv[])
{
    char* mem = calloc(MEMORY_SIZE, 1);
    char* ptr = mem;

    if(argc<2)
    {
        printf("USAGE - .\\brainfuck <INPUT>\n");
        printf("ERROR: No input file!!!\n");
        return 1;
    }

    size_t size = 0;
    const char* source = read_file(&size, argv[1]);

    if(!source)
        return 1;

    for(size_t i = 0; i < size; ++i)
    {
        switch(source[i])
        {
            case '>':
            {
                ptr++;
            }
            break;
            case '<':
            {
                ptr--;
            }
            break;
            case '+':
            {
                *ptr++;
            }
            break;
            case '-':
            {
                *ptr--;
            }
            break;
            case '.':
            {
                putchar(*ptr);
            }
            break;
            case ',':
            {
                *ptr = getchar();
            }
            break;
            case '[':
            {
                if(!*ptr)
                {
                    for(;source[i] != ']'; ++i);
                }
            }
            break;
            case ']':
            {
                if(*ptr)
                {
                    for(;source[i] != '['; --i);
                }
            }
            break;
            default:
                // These are just comments lol
            break;
        }
    }

    free(mem);
    free(ptr);

    return 0;
}