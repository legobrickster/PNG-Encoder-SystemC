# Makefile: test images for the color JPEG encoder
#
# modifications:
# 04/04/16 RD	added extra small sizes xs, xxs
# 04/04/16 RD	added test and checkjpeg targets
# 03/19/16 RD	added this Makefile to generate various image sizes
# 03/19/16 RD	added photo "Sydney_orig.jpg" (taken by Rainer Doemer)
#		and corresponding reference "Sydney_ref.jpg"
# 03/19/16 RD	renamed "golden.jpg" to "fungus_ref.jpg"
# 03/17/16 RD	fixed the corrupt "golden.jpg"
# 01/18/13 WC	initial photo "fungus.bmp" (taken by Weiwei Chen)
#		and corresponding reference "golden.jpg"

JPEGTOPNM	= jpegtopnm
PPMTOBMP	= ppmtobmp
BMPTOPNM	= bmptopnm
PNMSCALE	= pnmscale
LN		= ln -s
RM		= rm -f
ECHO		= echo

ORIGINALS =	fungus.bmp fungus_ref.jpg \
		Sydney_orig.jpg Sydney_ref.jpg

TARGETS =	fungus_xxl.bmp \
		fungus_xl.bmp \
		fungus_l.bmp \
		fungus_m.bmp \
		fungus_s.bmp \
		fungus_xs.bmp \
		fungus_xxs.bmp \
		Sydney.bmp \
		Sydney_xxl.bmp \
		Sydney_xl.bmp \
		Sydney_l.bmp \
		Sydney_m.bmp \
		Sydney_s.bmp \
		Sydney_xs.bmp \
		Sydney_xxs.bmp

all:	$(TARGETS)

test:	$(TARGETS) checkjpeg

clean:
	$(RM) $(TARGETS)
	$(RM) *.log

checkjpeg:
	n=0; \
	for img in *.jpg; do \
		$(ECHO) -n "Testing integrity of $$img... "; \
		$(JPEGTOPNM) -verbose $$img 1>/dev/null 2>$$img.log; \
		if [ $$? -ne 0 ]; then \
			$(ECHO) "Failed!"; \
			$(ECHO) " " `grep -i Corrupt $$img.log`; \
			$(ECHO) "  For more details, see $$img.log"; \
			n=`expr $$n + 1`; \
		else \
			$(ECHO) "Passed!"; \
			$(RM) $$img.log; \
		fi; \
	done; \
	if [ $$n -gt 0 ]; then \
		$(ECHO) "$$n images corrupt."; \
		exit $$n; \
	else \
		$(ECHO) "All images seem ok."; \
	fi

fungus_xxl.bmp:	fungus.bmp
	$(LN) $< $@

fungus_xl.bmp: fungus_xxl.bmp
	$(BMPTOPNM) $< | $(PNMSCALE) -reduce 2 | $(PPMTOBMP) > $@

fungus_l.bmp: fungus_xl.bmp
	$(BMPTOPNM) $< | $(PNMSCALE) -reduce 2 | $(PPMTOBMP) > $@

fungus_m.bmp: fungus_l.bmp
	$(BMPTOPNM) $< | $(PNMSCALE) -reduce 2 | $(PPMTOBMP) > $@

fungus_s.bmp: fungus_m.bmp
	$(BMPTOPNM) $< | $(PNMSCALE) -reduce 2 | $(PPMTOBMP) > $@

fungus_xs.bmp: fungus_s.bmp
	$(BMPTOPNM) $< | $(PNMSCALE) -reduce 2 | $(PPMTOBMP) > $@

fungus_xxs.bmp: fungus_xs.bmp
	$(BMPTOPNM) $< | $(PNMSCALE) -reduce 2 | $(PPMTOBMP) > $@


Sydney.bmp:	Sydney_orig.jpg
	$(JPEGTOPNM) $< | $(PPMTOBMP) > $@

Sydney_xxl.bmp:	Sydney.bmp
	$(LN) $< $@

Sydney_xl.bmp: Sydney_xxl.bmp
	$(BMPTOPNM) $< | $(PNMSCALE) -reduce 2 | $(PPMTOBMP) > $@

Sydney_l.bmp: Sydney_xl.bmp
	$(BMPTOPNM) $< | $(PNMSCALE) -reduce 2 | $(PPMTOBMP) > $@

Sydney_m.bmp: Sydney_l.bmp
	$(BMPTOPNM) $< | $(PNMSCALE) -reduce 2 | $(PPMTOBMP) > $@

Sydney_s.bmp: Sydney_m.bmp
	$(BMPTOPNM) $< | $(PNMSCALE) -reduce 2 | $(PPMTOBMP) > $@

Sydney_xs.bmp: Sydney_s.bmp
	$(BMPTOPNM) $< | $(PNMSCALE) -reduce 2 | $(PPMTOBMP) > $@

Sydney_xxs.bmp: Sydney_xs.bmp
	$(BMPTOPNM) $< | $(PNMSCALE) -reduce 2 | $(PPMTOBMP) > $@


# EOF
