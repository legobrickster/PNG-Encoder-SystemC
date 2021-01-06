# PNG-Encoder-SystemC
This is a PNG encoder model which works on fungus.bmp. To use this model the zlib library should be installed. zlib uses -lz as a compiler flag. Once zlib is installed the only option that needs changing is the SystemC directory in the makefile, which is the first variable in settings, SYSTEMC_HOME. It should be the location of the SystemC library. 

The model can be run using the command 'make test'. It will create a PNG image called as fungus.png. The image is tested to be viewable on the default Ubuntu(18.04,20.04) and Windows 10 image viewers. There are two other files called as fungus_png.txt and fungus_png.cc which are used as buffers. They can be deleted. DEFLATE seems to work faster when reading from a file rather than reading from an array so the two files were used. 

Currently, the model only works for fungus.bmp. If other images need to be tested, the  header chunk and data chunk must be modified in the monitor.cc file. BMP files have many different formats for example fungus.bmp stores every RGB triplet in BGR format rather than RGB. It also has a 255 value in between triplets. To accomadate for these possible differences in images a better BMP decoder may be designed in the future along with an automatic chunk creator.

Thank you for using the SystemC model!
