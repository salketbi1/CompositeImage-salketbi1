#include "bitmap.h"
#include <iostream>
#include <fstream>

// Read in the files from the user and store them in the array
void open_files(Bitmap images[]);

// Check that the image is a good one
bool good_image(Bitmap image);

// Return true if at least two of the images have the same dimensions
bool at_least_two(Bitmap images[]);

// Iterate th all the images and assign each pixel the new average in the 
//composite_image
void composite(Bitmap& composite_image, Bitmap images[]);

using namespace std;

int main()
{
/*
1. Ask the user for filename until they entered 10 files or DONE
2. Print error if the file does not exist, is not valid bitmap, or is not
   same dimension as the first image
3. If the file is good then add theimage if not then ignore it
4. Check that at least 2 of the filenames are imaes with same dimensions
5. If there not at least 2 images with same dimensions then print error and do
   nothing otherwise keep going
6. Iterate the images matrix with the same dimensions and and get the average rgb 
7. Assign the average rgb to each pixel ([row][col])
8. Print progress update when image finishes
9. Save the file to composite-salketbi1.bmp
*/
    return 0;
}
