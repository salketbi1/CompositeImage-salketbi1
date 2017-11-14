// Saif Alketbi
// Project 3
// main.cpp

#include "bitmap.h"
#include <iostream>
#include <fstream>
using namespace std;

// Read in the files from the user and store them in the vector
void open_files(vector<Bitmap> & images_lists, bool & images_ready);

// Check that the image in the file location is a good one
bool good_image(string image_file);

// Return true if the two bitmap the same height and width
bool same_Size(Bitmap b1, Bitmap b2);

// Sum all of the imags pixels
void sum_pixels(PixelMatrix & comp, Bitmap image);

// Compute the average RGB value
void compute_average(PixelMatrix & comp, int size);

// Iterate th all the images and assign each pixel the new average in the 
//composite_image
void composite(Bitmap& composite_image, vector<Bitmap> images_list);


int main()
{
  vector<Bitmap> images_list;
  Bitmap composite_image;
  bool images_Ready = false;

  open_files(images_list, images_Ready);

  if (images_Ready)
  {
    composite(composite_image, images_list);

    if (composite_image.isImage())
    {
      string filename = "composite-salketbi1.bmp";
      composite_image.save(filename);
      cout <<"Saved " << filename << endl;
    }
    else
    {
      cout << endl;
      cout << "Composite failed!" << endl;
    }
  }

    return 0;
}

void open_files(vector<Bitmap> & images_list, bool & images_ready)
{
  string filename="";
  images_ready = true;

  for (int i=0;i<10;i++)
  {
    Bitmap to_open;
    cout<<"What is your filename?"<<endl;
    cin>>filename;
    cin.ignore();

    if (filename=="DONE")break;

    // check that file exists and is a good bmp
    if (good_image(filename))
    {
      to_open.open(filename);
      // If this  is not the first image on the array then first have to
      // check is the size of the original image
      if (images_list.size()>0)
      {
        // have to check that the dimensions are same as first image
        if (same_Size(to_open, images_list[0]))
          images_list.push_back(to_open);
        else
          cout << "The image size is not the same as the first image." << endl;
      }
      else
        images_list.push_back(to_open);
    }
    cout << endl;
  }
  if (images_list.size()<2)
  {
    cout << "There not enough images for the composite."<<endl;
    images_ready=false;
  }
}

bool good_image(string image_file)
{
  Bitmap image;
  image.open(image_file);
  return image.isImage();
}

bool same_Size(Bitmap b1, Bitmap b2)
{
  PixelMatrix b1_pixels = b1.toPixelMatrix();

  PixelMatrix b2_pixels = b2.toPixelMatrix();

  // first check the ROWs
  if (b1_pixels.size()!=b2_pixels.size())
    return false;

  else

    // if it passes then check the COLumns
    for (int i=0;i<b1_pixels.size();i++)
      if (b1_pixels[i].size()!=b2_pixels[i].size())
        return false;

  return true;
}

void composite(Bitmap& composite_image, vector<Bitmap> images_list)
{
  PixelMatrix ref=images_list[0].toPixelMatrix();
  PixelMatrix comp;

  comp.resize(ref.size());

  for (int i=0;i<ref.size();i++)
    comp[i].resize(ref[i].size());

  for (int i=0;i<images_list.size();i++)
  {
    cout<<"Processing image " << i+1 << " of " << images_list.size() << endl;
    sum_pixels(comp, images_list[i]);
  }

  compute_average(comp, images_list.size());
  composite_image.fromPixelMatrix(comp);
}

void sum_pixels(PixelMatrix & comp, Bitmap image)
{
  PixelMatrix image_pixels = image.toPixelMatrix();

  for (int i=0;i<comp.size();i++)
  {
    for (int j=0;j<comp[i].size();j++)
    {
      Pixel px;
      px.red = comp[i][j].red+image_pixels[i][j].red;
      px.green = comp[i][j].green+image_pixels[i][j].green;
      px.blue = comp[i][j].blue+image_pixels[i][j].blue;
      comp[i][j]=px;
    }
  }
}

void compute_average(PixelMatrix & comp, int size)
{
  for (int i=0;i<comp.size();i++)
  {
    for (int j=0;j<comp[i].size();j++)
    {
      Pixel x;
      x.red=comp[i][j].red/size;
      x.green=comp[i][j].green/size;
      x.blue=comp[i][j].blue/size;
      comp[i][j]=x;
    }
  }
}
