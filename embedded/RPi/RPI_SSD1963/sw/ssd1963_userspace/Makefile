SRC = src/dio/dio_lcfg.c src/dio/dio.c src/tft/tft.c src/tft/tft_lcfg.c src/main.c 

CC = arm-linux-gnueabihf-gcc

CCOPT = -Wall -g -O3
TARGET = rpi_ssd1963
all: clean rpi_ssd1963 copy

clean:
	rm -f $(TARGET) *~

rpi_ssd1963:
	$(CC) $(SRC) -o $(TARGET) $(CCOPT)

copy: 
	scp $(TARGET) root@pi:/root
