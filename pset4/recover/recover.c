#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <stdint.h>

// A BYTE will represent each 0x00
typedef uint8_t BYTE;

// Byte size of a FAT filesystem is 512
#define FAT_SIZE 512

//
#define JPG_SIZE 8

// Function if a single jpeg is found return true.
bool is_new_jpg(BYTE buffer[]);

int main(int argc, char *argv[])
{
    // if the commandline argument does not equal 2
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Open the image provided from the second commandline argument and assign it to a variable.
    FILE *original_image = fopen(argv[1], "r");

    // If the file provided is not found
    if (original_image == NULL)
    {
        printf("file not found\n");
        return 1;
    }

    // Create a buffer variable that will contain a single unit of 512 bytes
    BYTE buffer[FAT_SIZE];

    // Assign a boolean value to a variable which will represent if the start of a jpeg is found in the buffer.
    bool jpg_found = false;

    // This will be the counter for when we once hit a memory allocation of the start of a jpeg
    int counter = 0;

    // This will contain the newly created image based from the forensic image.
    FILE *new_image;

    // While the end of the file has not been reached.
    while (fread(buffer, FAT_SIZE, 1, original_image))
    {
        // if the current BYTE that the buffer passed to has a s.
        if (is_new_jpg(buffer))
        {
            // If the this block is getting executed then that means this buffer equals the start of a jpg
            if (!jpg_found)
            {
                // So set the jpg_found to true.
                jpg_found = true;
            }
            else
            {
                // close the file the next iteration
                fclose(new_image);
            }

            // Set a empty jpg file to contain the recovered jpg file.
            char jpg_file[JPG_SIZE];

            // Format & generate a 'jpg_file' and set a counter to name the file based on the current count.
            sprintf(jpg_file, "%03i.jpg", counter++);

            // Now write the recovered jpg file to the new image
            new_image = fopen(jpg_file, "w");

            // If the new_image is empty.
            if (new_image == NULL)
            {
                return 1;
            }

            // Start the process of recovering
            fwrite(buffer, FAT_SIZE, 1, new_image);

        }
        // On go the process of recovery until the is_new_jpg() function returns false with the provided buffer.
        else if (jpg_found)
        {
            // Add to the new image a new FAT format containg a jpg.
            fwrite(buffer, FAT_SIZE, 1, new_image);
        }
    }

    // Close both images now that the program is finished
    fclose(new_image);

    fclose(original_image);

    // Exit with zero
    return 0;
}

// This function will return if it sees any matching sequences in the begining of each FAT formatted array.
bool is_new_jpg(BYTE buffer[])
{
// If the first byte is 0xff, the second 0xd8, the third 0xff and the fourth first 4 bits of the 4th byte starts with 1110
    return buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0;
}
