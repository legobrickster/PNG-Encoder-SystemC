##########################################################################
# Makefile: SystemC model of a color PNG encoder
##########################################################################
#
# 17/12/20 VG	initial version
# with help and guidance from RD
# stimulus.cc borrowed and modified from Weiwei Chen's JPEG model
##########################################################################

### SETTINGS #############################################################

SYSTEMC_HOME	= /usr/local/systemcc233

CC		= g++
#CMPOPTS		= -O2 -Wall
CMPOPTS	= -g -Wall
LNKOPTS		= -Wl,-rpath -Wl,$(SYSTEMC_HOME)/lib-linux64
INC		= -I. -I$(SYSTEMC_HOME)/include
LIBS		= -L$(SYSTEMC_HOME)/lib-linux64
LIBC		= -L$/usr/local/include

TARGETS	=	png

IMAGES	=	Sydney_xxs.bmp \
		Sydney_xs.bmp \
		Sydney_s.bmp \
		Sydney_m.bmp \
		Sydney_l.bmp \
		Sydney_xl.bmp \
		Sydney_xxl.bmp \
		fungus_xxs.bmp \
		fungus_xs.bmp \
		fungus_s.bmp \
		fungus_m.bmp \
		fungus_l.bmp \
		fungus_xl.bmp \
		fungus_xxl.bmp

DIFF		= diff --brief --report-identical-files
ECHO		= echo
JPEGTOPNM	= pngtopnm
RISC		= risc
RM		= rm -f
TIME		= /usr/bin/time

### TARGETS ##############################################################

all: $(TARGETS)

configure: 
	set -e; \
	u=5+3; \
	echo $$u; \
	#W=$$(xxd -s 0x012 -l 0x02 images/fungus.bmp); \
	O=$$(xxd -s 0x012 -l 0x02 images/fungus.bmp | cut -c 11-12); \
	P=$$(xxd -s 0x012 -l 0x02 images/fungus.bmp | cut -c 13-15); \
	#echo $$(xxd -s 0x012 -l 0x02 images/fungus.bmp | cut -c 5-10); \
	Z="$$P$$O"; \
	Y="$$(echo $$Z | tr -d '[:space:]')"; \
	XSIZE="$$(echo $$((0x$$Y)))"; \
	echo "$$XSIZE"; \
	A=$$(xxd -s 0x016 -l 0x02 images/fungus.bmp | cut -c 11-12); \
	B=$$(xxd -s 0x016 -l 0x02 images/fungus.bmp | cut -c 13-15); \
	R="$$B$$A"; \
	I="$$(echo $$R | tr -d '[:space:]')"; \
	YSIZE="$$(echo $$((0x$$I)))"; \
	echo "$$YSIZE"; \
	if [ $$XSIZE -gt 10000 ]; then \
		XSIZE=$$((65536-$$XSIZE)); \
	fi; \
	if [ $$YSIZE -gt 10000 ]; then \
		YSIZE=$$((65536-$$YSIZE)); \
	fi; \
	echo "$$XSIZE"; \
	echo "$$YSIZE"; \
	
test: $(TARGETS)
	set -e; \
	O=$$(xxd -s 0x012 -l 0x02 images/fungus.bmp | cut -c 11-12); \
	P=$$(xxd -s 0x012 -l 0x02 images/fungus.bmp | cut -c 13-15); \
	#echo $$(xxd -s 0x012 -l 0x02 images/fungus.bmp | cut -c 5-10); \
	Z="$$P$$O"; \
	Y="$$(echo $$Z | tr -d '[:space:]')"; \
	XSIZE="$$(echo $$((0x$$Y)))"; \
	echo "$$XSIZE"; \
	A=$$(xxd -s 0x016 -l 0x02 images/fungus.bmp | cut -c 11-12); \
	B=$$(xxd -s 0x016 -l 0x02 images/fungus.bmp | cut -c 13-15); \
	R="$$B$$A"; \
	I="$$(echo $$R | tr -d '[:space:]')"; \
	YSIZE="$$(echo $$((0x$$I)))"; \
	echo "$$YSIZE"; \
	if [ $$XSIZE -gt 10000 ]; then \
		XSIZE=$$((65536-$$XSIZE)); \
	fi; \
	if [ $$YSIZE -gt 10000 ]; then \
		YSIZE=$$((65536-$$YSIZE)); \
	fi; \
	echo "$$XSIZE"; \
	echo "$$YSIZE"; \
	for t in $(TARGETS); do \
		$(ECHO); \
		$(ECHO) "Testing encoder $$t on images/fungus.bmp..."; \
		$(TIME) ./$$t images/fungus.bmp fungus.png; \
	done




### TARGET EXECUTABLES ###################################################

# regular executable with Accellera SystemC
png: png.o stimulus.o monitor.o addfilter.o upfilter.o paeth.o
	$(CC) png.o stimulus.o monitor.o addfilter.o upfilter.o paeth.o \
		-o png -lsystemc -lz $(INC) $(LIBS) $(LIBC) $(LNKOPTS)

png.o: png.cc png.h config.h types.h stimulus.h monitor.h addfilter.h upfilter.h paeth.h
	$(CC) -c -DXSIZE=3216 -DYSIZE=2136 -lz png.cc $(INC) $(CMPOPTS)
#-D XSIZE="$$(echo "$$XSIZE")" -D YSIZE="$$(echo "$$YSIZE")"
stimulus.o: stimulus.cc stimulus.h config.h types.h
	$(CC) -c -DXSIZE=3216 -DYSIZE=2136 -lz  stimulus.cc $(INC) $(CMPOPTS)

monitor.o: monitor.cc monitor.h config.h types.h
	$(CC) -c -lz -DXSIZE -DYSIZE monitor.cc $(INC) $(CMPOPTS)

addfilter.o: addfilter.cc addfilter.h config.h types.h
	$(CC) -c -lz -DXSIZE -DYSIZE addfilter.cc $(INC) $(CMPOPTS)

upfilter.o: upfilter.cc upfilter.h config.h types.h
	$(CC) -c -lz -DXSIZE -DYSIZE upfilter.cc $(INC) $(CMPOPTS)

paeth.o: paeth.cc paeth.h config.h types.h
	$(CC) -c -lz -DXSIZE -DYSIZE paeth.cc $(INC) $(CMPOPTS)

##########################################################################
# EOF
##########################################################################
#-DXSIZE="$$(echo "$$XSIZE")" -DYSIZE="$$(echo "$$YSIZE")"

