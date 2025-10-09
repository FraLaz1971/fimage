# fimage
###
simple programs to read and write FITS images
###
to compile on linux (needs NASA cfitsio lib.). It is supposed that
the the libraries and .h header files are in the directory
pointed by CFITSIO_HOME env variable, otherwise change the makefile.
###
`make`
###
to run on linux
###
`./writefimage 3 5 img3x5_001.fits`
###
`./readfimage img3x5_001.fits`
###
