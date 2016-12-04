#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <math.h>

#define CHUNK_SIZE 1024

/* Color defines */
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"



char* help = YEL "Shredder" RESET " - secure shredding tool\n"
        "Available arguments: \n"
        "   -u      -> Remove file from operational system after shredding\n";


void header(void)
{
    char* program = "Shredder";
    double version = 1.23;
    fprintf(stderr, YEL "%s utility " RESET "v. %.2f\n"
            "Author: shemhazai [andre.marques@fatec.sp.gov.br]\n"
            "Author: lnsan0 [lcsnascimentodossantos@gmail.com]\n", program, version);
}

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

    size_t k = sizeof(char) * CHUNK_SIZE;

    long long i = 0;
    long double one_percent = get_file_share_size(size);
    double p = 0;

    char* total_byte_size;
    char* actual_bytes;
    char status[256];
    char byte[CHUNK_SIZE];

    /* Open urandom file */
    urand = fopen("/dev/urandom", "r");
    if (urand == NULL)
    {
        printf("Error opening /dev/urandom!\n");
        return 1;
    }


    printf("\nShredding status: \n");

    /* Set file descriptor to point to the 0-index byte of file. */
    fseek(fp, 0L, SEEK_SET);

    total_byte_size = count_bytes(size);
    for(i = 0; i < size; i += k)
    {

        /* Fix: 2016/12/04
         * Files with size < 100 bytes make 'one_percent' to be 0 and raise Floating Pointer Exception
         * at the next if conditional.
         */
        if((long long)one_percent == 0) {
            one_percent = 1;
        }

        /* Print status if modulus % 1.0% is true */
        if (i % (long long)one_percent == 0)
        {
            p = get_percentage(i, size);
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

    actual_bytes = count_bytes(i);
    sprintf(status, "[ %s / %s ] "GRN"%.2f%%"RESET" \n", actual_bytes, total_byte_size, p);
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
    int erase_flag = 0;
    int int_loop = 0;
    char* file_name;


    /* Prints program header in stderr */
    header();


    /* Check if has enough arguments. */
    if(argc < 2) {
        fprintf(stderr, "%s: missing file operand\n", argv[0]);
        exit(-1);
    }

    file_name = argv[1];
    /* Parse arguments */
    for (int_loop = 0; int_loop < argc; int_loop++) {

        // Check if --remove flag is present
        if(!strcmp(argv[int_loop], "-u")) {
            erase_flag++;
        }
    }

    /* Open argument file */
    fp = fopen(file_name, "rb+");

    /* Check file pointer and return error if NULL */
    if(fp == NULL) {
        fprintf(stderr, "%s: error opening file\n", argv[0]);
        exit(-1);
    }

    size = count_size(file_name);
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

    

    if(erase_flag > 0) {
	fprintf(stderr, "Removing file ...");
        remove(file_name);
    }

    return 0;
}
