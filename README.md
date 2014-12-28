2542AB
======

2542AB is an Arduino library for the scantily-documented 2542AB 3.5 segment display. I salvaged one from an INNOKIN iTaste MVP 3.0 vaporizer battery. It's a 12 pin device with .1" spacing. The datasheet I managed to find was a jpeg.

#####Diagram
![Datashit][datashit]

#####Features
  - Psuedo-dimming in software, also conveniently eliminates the need to put current limitors on the anodes.
  - Uses Timer/Counter1 for refreshing, controlled with simple ```on()``` and ```off()``` funcitons.
  - Decimal point control, settable minimum and maximum displayable number.
  - One constructor to assign all of the pins needed. This library is a pin hog, but I had some to spare at the time of writing.


[datashit]: http://g04.s.alicdn.com/kf/HTB1hQV5GVXXXXbZXFXXq6xXFXXXX/200334777/HTB1hQV5GVXXXXbZXFXXq6xXFXXXX.jpg
