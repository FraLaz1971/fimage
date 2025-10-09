#ifndef FIMAGE_H
#define FIMAGE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fitsio.h"
struct image{
  int *arr; /* the 32 bits array */
  short int *arr16; /* the 16 bits array */
  char *arr8;
  long nrows;
  long ncols;
  long count;
  long fpixel; /* first pixel in the array */
  long nelements; /* n. of elements of the array */
  int nullval;
  int anynull;
  int status;
  fitsfile *ifp;
  fitsfile *ofp;
  int bitpix; /* n. of bits for each pixel */
  long naxis; /*n. of axis(dimensions) */
  long naxes[2]; /*dimension of each axis */
  char fname[80]; /* name of the output file */
  char ifname[80]; /* name of the input file */
  char cmt[80];
};
int allocate_array(int nbits,struct image *img);
int fill_array(struct image *img);
int print_array(struct image *img);
int free_array(struct image *img);
int save_fits(struct image *img);
int load_fits(struct image *img);
void set_element(long rownum,long colnum,int val,struct image *img);
int get_element(long rownum,long colnum,struct image *img);
void printerror( int status);
#endif //FIMAGE_H
