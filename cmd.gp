set term wxt persist
set palette gray
plot 'mercury1_500x320.raw' binary array=(500,320) format="%uchar" with image

