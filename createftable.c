#include <stdio.h>
#include <stdlib.h>
#include "fimage.h"
int main(int argc, char **argv){
  long j;
  struct image img;
  struct trow* row;
  img.btable.tfields=3;
  if(argc<3){
    fprintf(stderr,"usage:%s <nrows> <filename.fits>\n",argv[0]);
    return 1;
  }
  img.btable.nrows=atol(argv[1]);
  strcpy(img.fname,argv[2]);
  row = (struct trow*)malloc(img.btable.nrows * img.btable.tfields * sizeof(struct trow));
  set_table_data(row);
    for(j=0; j<img.btable.nrows; j++){
		printf("%s %ld %lf \n", row[j].str,row[j].inum,row[j].rnum);
  }
	img.status=0;
	fprintf(stderr,"main() going to initialize the fits file\n");
	if(init_table(&img))fprintf(stderr,"error in initializing fits file\n");
	fprintf(stderr,"main() image saved on file\n");
	if(set_chdu(1,&img))  fprintf(stderr,"error in setting the hdu\n");
	fprintf(stderr,"main() hdu set\n");
	if(add_table_struct(&img,row))  fprintf(stderr,"error in adding a table\n");
	fprintf(stderr,"main() binary table addedd\n");
  
  free(row);
  return 0;
}
