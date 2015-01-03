neomatrixtest
=============

test neomatrix pixel level brightness setting and colours

to run this test download the 3 adafruit libraries from pwr33 as well which all have an extra parameter to drawpixel to allow pixel level brightness setting. 

bright < 0 : use default panel brightness

bright = 0 : use unscaled rgb values

bright > 0 : scale this pixels brightness by bright value 1 = dimmest 255 = brightest 
