SRC = src/dio/dio_lcfg.c src/dio/dio.c src/tft/tft.c src/tft/tft_lcfg.c src/main.c 

#CC = gcc
CC = arm-linux-gnueabihf-gcc
#INCLDIR = /home/armin/dev/gnublin/gnublin-develop-kernel/linux-2.6.33-lpc313x
#INCLDIR = /home/armin/dev/gnublin/gnublin-develop-kernel/linux-3.3.0-lpc313x

CCOPT = -Wall -g -O3
TARGET = rpi_ssd1963
all: clean rpi_ssd1963 copy

clean:
	rm -f $(TARGET) *~

rpi_ssd1963:
#	$(CC) $(CCOPT) -I$(INCLDIR) -o $(TARGET) $(SRC)
	$(CC) $(SRC) -o $(TARGET) $(CCOPT)
#	$(CC) -I$(INCLDIR) $(SRC) -o $(TARGET) $(CCOPT)


copy: 
	scp $(TARGET) root@pi:/root
