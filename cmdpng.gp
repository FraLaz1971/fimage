set terminal png
set output 'mercury1_500x320.png'
set title 'Mercury seen by Mariner 10 (1974)'
set palette gray
plot 'mercury1_500x320.raw' binary array=(500,320) format="%uchar" with image

