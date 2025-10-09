#include "fimage.h"
int allocate_array(int nbits,struct image *img){
  long int i;
  if(nbits==32)
	img->arr=(int *)malloc(img->nrows*img->ncols*sizeof(int));
  else if (nbits==16)
	img->arr16=(short int *)malloc(img->nrows*img->ncols*sizeof(short int));
  else if (nbits==8)
	img->arr8=(char *)malloc(img->nrows*img->ncols*sizeof(char));
  return img->status;
}
int fill_array(struct image *img){
long int i,j;
  for(i=0;i<img->nrows;i++)
    for(j=0;j<img->ncols;j++)
       set_element(i,j,++img->count,img);
  return img->status;
}
int print_array(struct image *img){
long int i,j;
  for(i=0;i<img->nrows;i++){
    for(j=0;j<img->ncols;j++)
       printf("%d ",get_element(i,j,img));
    puts("");
  }
  return img->status;
}
int free_array(struct image *img){
  long int i;
  if(img->bitpix==32)
    free(img->arr);
  if(img->bitpix==16)
    free(img->arr16);
  if(img->bitpix==8)
    free(img->arr8);
  fprintf(stderr,"free_array() freed the %d bit array\n",img->bitpix);
  return img->status;
}
int save_fits(struct image *img){
  /* remove the file if exists */
  remove(img->fname);
  /* open fits file for writing */
  if (fits_create_file(&img->ofp, img->fname, &img->status)) /* create new FITS file */
         printerror( img->status );           /* call printerror if error occurs */
  fprintf(stderr,"save_fits() fits file opened\n");
  /* create the image */
  if ( fits_create_img(img->ofp, img->bitpix, img->naxis, img->naxes, &img->status) )
         printerror( img->status );
  fprintf(stderr,"save_fits() image created\n");
  /* initialize the array*/
	img->status=0;
/*  if(allocate_array(img->bitpix,img)) fprintf(stderr,"error in allocating array memory\n"); 
  fprintf(stderr,"save_fits() array allocated\n");
*/
  /* write the image */
  fprintf(stderr,"save_fits() fits file opened\n");
  if(img->bitpix==32){
  if ( fits_write_img(img->ofp, TINT, img->fpixel, img->nelements, img->arr, &img->status) )
        printerror( img->status );
  } else if (img->bitpix==16) {
  if ( fits_write_img(img->ofp, TSHORT, img->fpixel, img->nelements, img->arr16, &img->status) )
        printerror( img->status );
  } else if (img->bitpix==8){
  if ( fits_write_img(img->ofp, TBYTE, img->fpixel, img->nelements, img->arr8, &img->status) )
        printerror( img->status );
  }
  fprintf(stderr,"save_fits() fits file written\n");
  /* close fits file */
  if ( fits_close_file(img->ofp, &img->status) ) /* close the file */
         printerror( img->status );           
  fprintf(stderr,"save_fits() fits file closed\n");
  return img->status;
}
void set_element(long rownum,long colnum,int val,struct image *img){
	if(img->bitpix==32){
		img->arr[rownum*img->ncols+colnum]=val;
	} else if(img->bitpix==16){
		img->arr16[rownum*img->ncols+colnum]=val;
	} else if (img->bitpix==8){
		img->arr8[rownum*img->ncols+colnum]=val;
    }
}
int get_element(long rownum,long colnum,struct image *img){
	if(img->bitpix==32){
		return img->arr[rownum*img->ncols+colnum];
    } else if(img->bitpix==16){
		return img->arr16[rownum*img->ncols+colnum];
    } else if(img->bitpix==8){
		return img->arr8[rownum*img->ncols+colnum];
	} else
	  return 0;
}
int load_fits(struct image *img){
long int i,j;
  /* open fits file for reading */
  img->status=0;
  fprintf(stderr,"load_fits() going to open file %s\n",img->ifname);
  if ( fits_open_file(&img->ifp, img->ifname, READONLY, &img->status) )
     printerror( img->status );
  fprintf(stderr,"load_fits() input fits file opened\n");
  /* load image in memory */
  if(fits_read_key(img->ifp, TLONG, (char*)"NAXIS", &img->naxis,
       (char*)img->cmt, &img->status)) printerror(img->status);
  fprintf(stderr,"naxis:%ld comment:%s\n",img->naxis,img->cmt);
  if(fits_read_key(img->ifp, TLONG, (char*)"NAXIS1", &img->naxes[0],
       (char*)img->cmt, &img->status)) printerror(img->status);
  fprintf(stderr,"naxes[0]:%ld comment:%s\n",img->naxes[0],img->cmt);
  if(fits_read_key(img->ifp, TLONG, (char*)"NAXIS2", &img->naxes[1],
       (char*)img->cmt, &img->status)) printerror(img->status);
  fprintf(stderr,"naxes[1]:%ld comment:%s\n",img->naxes[1],img->cmt);
  if(fits_read_key(img->ifp, TLONG, (char*)"BITPIX", &img->bitpix,
       (char*)img->cmt, &img->status)) printerror(img->status);
  fprintf(stderr,"bitpix:%d comment:%s\n",img->bitpix,img->cmt);
  img->ncols=img->naxes[0];
  img->nrows=img->naxes[1];
  img->nelements=img->naxes[0]*img->naxes[1];
  /* initialize the array*/
  img->status=0;
  if(allocate_array(img->bitpix,img)) fprintf(stderr,"error in allocating array memory\n");
  fprintf(stderr,"load_fits() array allocated\n");

  if(img->bitpix==32){
                  fprintf(stderr,"load_fits() reading a 32 bit per pixel image\n");
  if ( fits_read_img(img->ifp, TINT, img->fpixel, img->nelements, &img->nullval,
                  img->arr, &img->anynull, &img->status) ) printerror( img->status );
  } else if (img->bitpix==16){
                  fprintf(stderr,"load_fits() reading a 16 bit per pixel image\n");
  if ( fits_read_img(img->ifp, TSHORT, img->fpixel, img->nelements, &img->nullval,
                  img->arr16, &img->anynull, &img->status) ) printerror( img->status );
  } else if (img->bitpix==8){
                  fprintf(stderr,"load_fits() reading a 8 bit per pixel image\n");
  if ( fits_read_img(img->ifp, TBYTE, img->fpixel, img->nelements, &img->nullval,
                  img->arr8, &img->anynull, &img->status) ) printerror( img->status );
  }
  fprintf(stderr,"load_fits() image loaded in memory\n");
  /* close fits file */
  if ( fits_close_file(img->ifp, &img->status) ) printerror( img->status );
  fprintf(stderr,"load_fits() input fits file closed\n");
return img->status;
}
void printerror( int status)
{
    /*****************************************************/
    /* Print out cfitsio error messages and exit program */
    /*****************************************************/
    if (status)
    {
       fits_report_error(stderr, status); /* print error report */
       exit( status );    /* terminate the program, returning error status */
    }
    return;
}
