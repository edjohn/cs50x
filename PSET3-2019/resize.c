// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    //remember resize factor
    int scale = atoi(argv[1]);

    // ensure proper usage
    if ((argc != 4) || scale < 0 || scale > 100)
    {
        fprintf(stderr, "Usage: resize scale infile outfile (scale = positive integer between 0 and 100)\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    int biWidthOriginal = bi.biWidth;
    int biHeightOriginal = bi.biHeight;
    int paddingOriginal = (4 - (biWidthOriginal * sizeof(RGBTRIPLE)) % 4) % 4;

    bi.biWidth *= scale;
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    bi.biHeight = bi.biHeight * scale;

    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + padding) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines (for each row)
    for (int row = 0; row < abs(biHeightOriginal); row++)
    {
        for (int height = 0; height < scale - 1; height++)
        {
            for (int pixel = 0; pixel < biWidthOriginal; pixel++)
            {
                RGBTRIPLE triple;

                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                for (int outfilePixel = 0; outfilePixel < scale; outfilePixel++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            for (int outfilePadding = 0; outfilePadding < padding; outfilePadding++)
            {
                fputc(0x00, outptr);
            }

            fseek(inptr, -(biWidthOriginal * sizeof(RGBTRIPLE)), SEEK_CUR);
        }
        for (int pixel = 0; pixel < biWidthOriginal; pixel++)
        {
            RGBTRIPLE triple;

            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            for (int outfilePixel = 0; outfilePixel < scale; outfilePixel++)
            {
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
        }

        // write outfile's padding
        for (int outfilePadding = 0; outfilePadding < padding; outfilePadding++)
        {
            fputc(0x00, outptr);
        }

        // skip over infile's padding, if any
        fseek(inptr, paddingOriginal, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
