CROSS=arm-linux-

CFLAGS= -Wall -Wshadow -Wwrite-strings -Wsign-compare -Wfloat-equal \
	-Wmissing-noreturn -Wbad-function-cast \
	-Wmissing-prototypes -Winline -Wredundant-decls -O3

all: adc_test

adc_test: adc_test.o
	$(CROSS)gcc $(CFLAGS) -o $@ $+

clean:
	rm -f a.out *.o adc_test

%.o: %.c
	$(CROSS)gcc $(CFLAGS) -c -o $@ $+