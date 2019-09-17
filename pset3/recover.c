#include <stdio.h>
#include <cs50.h>
#include <stdint.h>

bool isStartJPEG(uint8_t buffer[], int size) {

	if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff
			&& (buffer[3] & 0xf0) == 0xe0) {
		return true;
	}

	return false;
}

int main(int argc, char const *argv[]) {
	uint8_t buffer[512];

	FILE *cardImage = fopen("/home/skrao/Desktop/card.raw", "r");

	int bytesRead = 0;
	int jpegIndex = 0;
	char fileName[20];

	FILE *outFile = NULL;

	if (cardImage) {

		do {
			bytesRead = fread(buffer,  sizeof(uint8_t), 512, cardImage);
			if (isStartJPEG(buffer, bytesRead)) {
				sprintf(fileName, "%03i.jpg", jpegIndex++);
				if(outFile) {
					fclose(outFile);
					outFile = fopen(fileName , "w");
				}
				outFile = fopen(fileName, "w");
			}
			if(outFile) {
				fwrite(buffer, sizeof(uint8_t), bytesRead, outFile);
			}

		} while (bytesRead == 512);

		fclose(cardImage);
	}else {
		printf("Cant open the file");
		return 1;
	}

	return 0;
}
