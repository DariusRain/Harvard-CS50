#include "helpers.h"
#include <cs50.h>
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Iteratate through the first dimension of the image which is height.
    for (int i = 0; i < height; i++)
    {
        // iterate through the second dimension of the image which is width.
        for (int j = 0; j < width; j++)
        {
            // Take current pixel during iteration and assign it to the predefined struct.
            // This is also a hard copy becuase both have the same type definition therefore compatiable.
            RGBTRIPLE pixel = image[i][j];

            // Calculate the average value of all 3 of rgb values
            int avg = round((pixel.rgbtGreen + pixel.rgbtBlue + pixel.rgbtRed) / 3.0);

            // Set all of the value of red green and blue to the average above which is grey
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = avg;

        }
    }
    return;
}

// Set limit to see if the value of any pixel exceeds 255 bits
int limit(int x)
{
    // If the value passed is greater than 255 then return 255 otherwise the value is okay.
    if (x > 255)
    {
        return 255;
    }
    else
    {
        return x;
    }

}


// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Same iteration as grayscale
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Copy the current iteration.
            RGBTRIPLE pixel = image[i][j];

            // Extract each color value from the pixel object
            int red = pixel.rgbtRed;
            int green = pixel.rgbtGreen;
            int blue = pixel.rgbtBlue;

            // Round the formula given to us and limit the value returned to 255 if over 255.
            image[i][j].rgbtRed = limit(round(.393 * red + .769 * green + .189 * blue));
            image[i][j].rgbtGreen = limit(round(.349 * red + .686 * green + .168 * blue));
            image[i][j].rgbtBlue = limit(round(.272 * red + .534 * green + .131 * blue));
        }
    }
    return;
}


// Create a swap function
void swap(RGBTRIPLE *pixel1, RGBTRIPLE *pixel2)
{
    // Assign container the hex location & value of pixel 1
    RGBTRIPLE container = *pixel1;

    // Assign hex location value of pixel1 to the hex location & value of pixel2
    *pixel1 = *pixel2;

    // Assign the hex location and value of
    *pixel2 = container;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        // This whole iteration is cut in half becuase two values are being swapped every time
        // so in each iteration the hexadecimal addresses swap their values until there is no more to swap.
        for (int j = 0; j < width / 2; j++)
        {
            // Pass the hexadecimal addresses for the current iterated value
            // and the opposing iterated value.
            swap(&image[i][j], &image[i][width - 1 - j]);

        }
    }

    return;
}

// Check if pixel is above or below range of width and height
bool validate_pixel(int i, int j, int height, int width)
{
    // if i & j don't exceed height and are not negative integers then the returned
    // value should be true.
    return i < height && j < width && i >= 0 && j >= 0;
}

// This function returns a blurred version of the RGBTRIBPLE struct that is being passed and returns a new one.
RGBTRIPLE blur_pixel(int dimension1, int dimension2, int height, int width, RGBTRIPLE image[height][width])
{
    // Declare a clean set of rgb variables everytime this function is called.
    int red = 0, blue = 0, green = 0;

    // Keep a valid pixel count for
    int validPixelCount = 0;

    // Start count at -1 to be one off
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            // This sets the dimensions to be off by one the first iteration if
            // the value does not fall below the width or height of the image.
            int updated_i = i + dimension1;
            int updated_j = j + dimension2;

            // Check if the pixel is within range.
            if (validate_pixel(updated_i, updated_j, height, width))
            {
                // This count will represent the value of average,
                // which is the length away a pixel is from the edge of the grid
                validPixelCount++;

                // Now assign each red, green & blue each time a valid pixel has passed
                // representing the sum of the row that will be divided later on by the pixel count.
                red += image[updated_i][updated_j].rgbtRed;
                green += image[updated_i][updated_j].rgbtGreen;
                blue += image[updated_i][updated_j].rgbtBlue;
            }
        }
    }

    // Declare a struct representing a single blurred pixel using the above results
    RGBTRIPLE blurred_pixel;

    // Use float for a more acurate value and divide each individual summed rgb value by the divided by the amount
    // of rows which is the valid pixel count thus representing the average.
    // Now assign the values
    blurred_pixel.rgbtRed = round((float) red / validPixelCount);
    blurred_pixel.rgbtGreen = round((float) green / validPixelCount);
    blurred_pixel.rgbtBlue = round((float) blue / validPixelCount);

    // Return the individual pixel to the blur function and it shall call it again during iteration.
    return blurred_pixel;
}


// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a empty two dimensional array with the same length & width
    RGBTRIPLE blurred_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < height; j++)
        {
            // Assign each index an individual RGBTRIPLE struct as a blurred pixel based on the official image.
            blurred_image[i][j] = blur_pixel(i, j, height, width, image);
        }
    }

    //  Now hard copy that new blurred image into the official one making it now blurry! :)
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = blurred_image[i][j];
        }
    }
    return;
}
