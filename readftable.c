#include "fimage.h"
/* read a binary table from a FITS file */
int main(int argc, char **argv){
  struct image img;

  if (argc<2){
    fprintf(stderr,"usage:%s <infile.fits>\n",argv[0]);
    return 1;
  }
  strcpy(img.ifname,argv[1]);

  fprintf(stderr,"argv[1]: %s ifname: %s\n", argv[1],img.ifname);
/* read fits file content in the struct */
	img.status=0;
	if(load_table_header(2,&img)) fprintf(stderr,"error in loading table header file\n");
	fprintf(stderr,"main() table header loaded\n");
	fprintf(stderr,"main() going to load the table\n");
	if(load_table(&img)) fprintf(stderr,"error in loading fits table\n");
	fprintf(stderr,"main() fits table loaded\n");
	fprintf(stderr,"main() table structure freed\n");
  return 0;
}
