all: sujet

dist: correction package

package: sujet
	cp sheet/*.pdf .
	cp -r material in103-examen-material
	cp examen-etu.pdf in103-examen-material
	tar -cvzf in103-examen.tar.gz in103-examen-material
	rm -rf in103-examen-material

correction: sujet
	cp sheet/*.pdf .
	cp -r correction in103-examen-correction
	cp examen-correction.pdf in103-examen-correction
	tar -cvzf in103-examen-correction.tar.gz in103-examen-correction
	rm -rf in103-examen-correction

sujet:
	make -C sheet all

clean:
	rm -f *.tar.gz *~
	@for i in 1 2 3 4 5 6 7 8; do \
		make -C exo$$i clean; \
	done

realclean: clean
	@for i in 1 2 3 4 5 6 7 8; do \
		make -C exo$$i realclean; \
	done

.PHONY: dist package correction sujet clean realclean
