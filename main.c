#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <math.h>

#define CHUNK_SIZE 1024

void header(void)
{
    char* program = "Shredder";
    double version = 1.23;
    fprintf(stderr, "%s utility v. %.2f\n"
            "Author: shemhazai [andre.marques@fatec.sp.gov.br]\n"
            "Author: lnsan0 [lcsnascimentodossantos@gmail.com]\n", program, version);
}

/*long long count_size(FILE* fp)
{
    long long size;
    fseek(fp, 0L, SEEK_END); //go to the end of the file to get the amount of bytes
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET); //go to the beggining again
    return size;
}*/

char* count_bytes(off_t size)
{

    char* buffer = malloc(sizeof(char) * 256);
    long tera, giga, mega, kilo;

    tera = (long)pow(2, 40);
    giga = (long)pow(2, 30);
    mega = (long)pow(2, 20);
    kilo = (long)pow(2, 10);

    if(size > tera) {
        double q = size / tera;
        sprintf(buffer, "%2.f TiB", q);
    } else
    if(size > giga) {
        double q = size / giga;
        sprintf(buffer, "%2.f GiB", q);
    } else
    if(size > mega) {
        double q = size / mega;
        sprintf(buffer, "%2.f MiB", q);
    } else
    if(size > kilo) {
        double q = size / kilo;
        sprintf(buffer, "%2.f KiB", q);
    } else {
        sprintf(buffer, "%2.f Bytes", (double)size);
    }

    return buffer;
}


char* count_time(int seconds) {
    int minuto = 0, hora = 0, dia = 0;
    int tday = 86400;
    int thour = 3600;
    int tmin = 60;

    char *buffer = malloc(sizeof(char) * 256);

    if (seconds > tday) {
        dia = seconds / tday;
        hora = seconds % thour;
        minuto = seconds % tmin;
        sprintf(buffer, "%dd %dh %dm %ds", dia, hora, minuto, seconds);
    } else
    if (seconds > thour) {
        hora = seconds / thour;
        minuto = seconds % tmin;
        sprintf(buffer, "%dh %dm %ds", hora, minuto, seconds);
    } else
    if (seconds > tmin) {
        minuto = seconds / tmin;
        sprintf(buffer, "%dm %ds", minuto, seconds);
    } else {
        sprintf(buffer, "%ds", seconds);
    }
    return buffer;
}

off_t count_size(const char* filename)
{
    struct stat t;
    if(stat(filename, &t) == 0) {
        return t.st_size;
    }
    return -1;
}

void get_rnd_byte(char *ptr, FILE* fp)
{
    //memset(ptr, 0, CHUNK_SIZE);
    fread(ptr, 0x1, CHUNK_SIZE, fp);
}

double get_percentage(long long x, long long y)
{
    double value;
    if(y == 0)
    {
        y = 1;
    }
    value = ( x / (double)y ) * 100;
    return value;
}

long double get_file_share_size(long long size)
{
    return (size/100.0);
}

int shred(FILE* fp, long long size) {
    FILE *urand;
    char byte[CHUNK_SIZE];
    long long i = 0;
    size_t k = sizeof(char) * CHUNK_SIZE;
    long double one_percent = get_file_share_size(size);
    double p = 0;
    char* total_byte_size;
    char* actual_bytes;
    char status[256];

    /* Open urandom file */
    urand = fopen("/dev/urandom", "r");
    if (urand == NULL)
    {
        printf("Error opening /dev/urandom!\n");
        return 1;
    }


    printf("Shredding status: \n");

    /* Inits algorithm for shredding files */
    fseek(fp, 0L, SEEK_SET);

    total_byte_size = count_bytes(size);
    for(i = 0; i < size; i += k)
    {
        /* Print status if modulus % 1.0% is true */
        if (i % (long long)one_percent == 0)
        {
            p = get_percentage(i, size);
            //fprintf(stdout, "[ %lld / %lld ] %.2f%% \r", i, size, p);
            actual_bytes = count_bytes(i);
            sprintf(status, "[ %s / %s ] %.2f%% \r", actual_bytes, total_byte_size, p);
            fprintf(stdout, status);
        }

        /* Function to get random data from urandom */
        get_rnd_byte(byte, urand);

        /* IF conditional to ensure the program does not over overwrite data. */
        if( (size - i) < CHUNK_SIZE )
            {
                k = sizeof(char) * (size - i);
            }

        /* Writes N(k) bytes to file pointer. */
        fwrite(byte, 0x1, k, fp);
    }
    p = 100.0;

    //fprintf(stdout, "[ %lld / %lld ] %.2f%% \r", i, size, p);
    actual_bytes = count_bytes(i);
    sprintf(status, "[ %s / %s ] %.2f%% \n", actual_bytes, total_byte_size, p);
    fprintf(stdout, status);

    /*Closes urand file descriptor */
    fclose(urand);
    free(actual_bytes);
    free(total_byte_size);
    return 0;
}

int main(int argc, char* argv[])
{
    clock_t tic = clock();
    // Version 1.21 was
    // long long size
    off_t size;
    FILE *fp;

    /* Prints program header in stderr */
    header();


    /* Check if has enough arguments. */
    if(argc < 2) {
        fprintf(stderr, "%s: missing file operand\n", argv[0]);
        exit(-1);
    }

    /* Open argument file */
    fp = fopen(argv[1], "rb+");

    /* Check file pointer and return error if NULL */
    if(fp == NULL) {
        fprintf(stderr, "%s: error opening file\n", argv[0]);
        exit(-1);
    }

    size = count_size(argv[1]);
    if(size < 0)
    {
        fprintf(stderr, "%s: error counting size of file\n", argv[0]);
        exit(-1);
    }

    shred(fp, size);
    fclose(fp);
    clock_t toc = clock();
    double time_spent;
    time_spent = (double)(toc - tic) / CLOCKS_PER_SEC;
    char *x;
    x = count_time((int)time_spent);
    fprintf(stderr, "Time elapsed: %s\n", x);
    return 0;
}