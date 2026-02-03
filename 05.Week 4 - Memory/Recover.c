#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Each block on the memory card is 512 bytes
#define BLOCK_SIZE 512

// BYTE is just an unsigned 8-bit integer (one byte)
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Must have exactly one command-line argument (the forensic image)
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover card.raw\n");
        return 1;
    }

    // Open the forensic image for reading in binary mode
    FILE *input = fopen(argv[1], "rb");
    if (input == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 2;
    }

    BYTE buffer[BLOCK_SIZE];       // 512-byte read buffer
    FILE *output = NULL;           // pointer to current JPEG being written
    int  count   = 0;              // JPEG file counter (000, 001, 002 …)

    // Read the forensic image one 512-byte block at a time
    while (fread(buffer, BLOCK_SIZE, 1, input) == 1)
    {
        // Check whether this block starts a new JPEG
        // Signature: 0xff 0xd8 0xff 0xe? (fourth byte's high nibble == 0xe)
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // If we were already writing a JPEG, close it first
            if (output != NULL)
            {
                fclose(output);
            }

            // Open a new output file named 000.jpg, 001.jpg, …
            char filename[8]; // "###.jpg" + '\0' = 8 chars
            sprintf(filename, "%03d.jpg", count);
            output = fopen(filename, "wb");
            if (output == NULL)
            {
                fprintf(stderr, "Could not create %s.\n", filename);
                fclose(input);
                return 1;
            }

            count++;
        }

        // If we have found at least one JPEG, keep writing blocks to it
        if (output != NULL)
        {
            fwrite(buffer, BLOCK_SIZE, 1, output);
        }
    }

    // Close the last JPEG and the input file
    if (output != NULL)
    {
        fclose(output);
    }
    fclose(input);

    return 0;
}
