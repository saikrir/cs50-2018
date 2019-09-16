#include <stdio.h>
#include <cs50.h>
#include "bmp.h"


void resize(const char *srcBmpName,const char *destBmpName, int resizeFactor) 
{
    FILE *srcBmpFile = fopen(srcBmpName, "r");
    FILE *destBmpFile = fopen(destBmpName, "w");

    if(srcBmpFile == NULL) {
        printf("Unable to open file %s " , srcBmpName);
        return;
    }

     BITMAPFILEHEADER bf;
     fread(&bf, sizeof(bf),1, srcBmpFile);

     BITMAPINFOHEADER bi;
     fread(&bi, sizeof(bi), 1, srcBmpFile);

     if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(srcBmpFile);
        fclose(destBmpFile);
        printf("Unsupported file format.\n");
    }

    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int paddingNeeded = (resizeFactor * bi.biWidth * 3) % 4;
    int imageHeight = abs(bi.biHeight);
    int imageWidth = bi.biWidth;

    int newWidth = resizeFactor * bi.biWidth;
    int newHeight = newWidth;

    bi.biHeight = newHeight;
    bi.biWidth = newWidth;

    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + paddingNeeded) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, destBmpFile);
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, destBmpFile);

    for(int row= 0; row < newHeight; row++) {
        RGBTRIPLE triple;

      
        for (int col = 0; col < imageWidth; col++)
        {
            if((row % resizeFactor ==0)) {
                printf("Row %d", row);
                fread(&triple, sizeof(RGBTRIPLE), 1, srcBmpFile);
            }

            for(int i=0; i < resizeFactor; i++) {
                fwrite(&triple, sizeof(RGBTRIPLE), 1, destBmpFile);
            }
            fseek(srcBmpFile, padding, SEEK_CUR);
            for(int i =0; i < paddingNeeded; i++) {
                fputc(0x00 , destBmpFile);
            }
        }
    }
    fclose(srcBmpFile);
    fclose(destBmpFile);
    printf("reszing  %d \n", paddingNeeded);
}

int main(int argc, char const *argv[])
{
    if(argc < 4) {
        printf("Usage: ./resize n infile outfile \n");
        return 1;
    }

    int n = atoi(argv[1]);

    if(n < 0 || n > 100) {
        printf("Invalid resize value \n");
        return 2;
    }

    const char *srcBmpName = argv[2];
    const char *destBmpName = argv[3];

    resize(srcBmpName, destBmpName, n);

    return 0;
}
