#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    //ensure proper usage of the function
    if(argc != 3)
    {
        fprintf(stderr, "Usage: whodunit infile outfile\n");
        return 1;
    }

    char *image = argv[1];
    char *word = argv[2];

    //open the image
    FILE *inptr = fopen(image, "r");
    if(inptr == NULL)
    {
        fprintf(stderr,"Error opening the file %s.\n", image);
        return 2;
    }

    //open the word
    FILE *outptr = fopen(word, "w");
    if(outptr == NULL)
    {
        fprintf(stderr,"Error opening the file %s.\n", word);
        return 3;
    }

    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER),1, inptr);

    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

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

    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    for (int i =0; i< abs(bi.biHeight); i++)
    {
        for (int j=0; j< bi.biWidth; j++)
        {
          RGBTRIPLE triple;

          // read RGB triple from infile
          fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

          if (triple.rgbtBlue == 0x00 & triple.rgbtGreen == 0x00 & triple.rgbtRed == 0xff)
          {
              triple.rgbtBlue= 0xff;
              triple.rgbtGreen = 0xff;
          }

          fwrite(&triple, sizeof(RGBTRIPLE),1, outptr);

        }
         // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }


    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;

}