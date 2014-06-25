all:
	gcc -o bench_bcm2835-O3 bench_bcm2835.c -lbcm2835 -O3
	gcc -o bench_bcm2835-O0 bench_bcm2835.c -lbcm2835 -O0
	gcc -o bench_wiringPi-O3 bench_wiringPi.c -lwiringPi -O3
	gcc -o bench_wiringPi-O0 bench_wiringPi.c -lwiringPi -O0
	gcc -o bench_native-O3 bench_native.c -O3
	gcc -o bench_native-O0 bench_native.c -O0
clean:
	chmod -x bench_bash.sh
	rm bench_bcm2835-O3
	rm bench_bcm2835-O0
	rm bench_wiringPi-O3
	rm bench_wiringPi-O0
	rm bench_native-O3
	rm bench_native-O0
