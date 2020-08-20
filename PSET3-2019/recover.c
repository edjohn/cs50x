#include <stdio.h>
#include <stdlib.h>

int found_jpeg(unsigned char *buffer);
int get_bytesread(FILE *infileptr);

int main(int argc, char *argv[])
{
    //Check for correct number of command line arguments
    if (argc != 2)
    {
        fprintf(stderr, "Usage: recover (infile)\n");
        return 1;
    }

    //Open memory card file
    FILE *infile;
    infile = fopen(argv[1], "r");

    //Check if file can be opened
    if (infile == NULL)
    {
        fprintf(stderr, "Could not open file.\n");
        return 2;
    }

    //Initialize variables
    FILE *outfile = NULL;
    unsigned char fileblock[512];
    char filename[8];
    int filenumber = 0;

    //Loop through jpeg files until end of file
    while (get_bytesread(infile) == 512)
    {
        //Find first jpeg file
        while (found_jpeg(fileblock) == 1)
        {
            fread(fileblock, 512, 1, infile);
        }

        //Open empty file to write into
        sprintf(filename, "%03d.jpg", filenumber);
        outfile = fopen(filename, "w");

        //Write into file until new jpeg header is found
        fwrite(fileblock, 512, 1, outfile);
        fread(fileblock, 512, 1, infile);

        while ((found_jpeg(fileblock) == 1) && (get_bytesread(infile) == 512))
        {
            fwrite(fileblock, 512, 1, outfile);
            fread(fileblock, 512, 1, infile);
        }

        if (get_bytesread(infile) != 512)
        {
            fread(fileblock, 512, 1, infile);
            fwrite(fileblock, 512, 1, outfile);
            fclose(outfile);
            break;
        }

        //Close outfile if present and iterates filenumber
        if (outfile != NULL)
        {
            fclose(outfile);
            filenumber += 1;
        }
    }

    //Close memory card file
    fclose(infile);

    //Program finished successfully
    return 0;
}

//Check if values are consistent with a jpeg header
int found_jpeg(unsigned char *buffer)
{
    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
    {
        return 0;
    }
    return 1;
}

//Returns how many bytes have been read
int get_bytesread(FILE *infileptr)
{
    unsigned char temp_fileblock[512];

    int bytes_read = fread(temp_fileblock, 1, 512, infileptr);
    int temp = bytes_read;
    fseek(infileptr, -temp, SEEK_CUR);
    return temp;
}








