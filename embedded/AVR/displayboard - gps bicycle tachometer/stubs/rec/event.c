#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>
#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <sys/time.h>
#include <termios.h>
#include <signal.h>
#include <inttypes.h>

    uint8_t recording = 0;
    int8_t rec_toggle = -1;
    uint8_t start_recording = 0;
    uint8_t stop_recording = 0;
	uint8_t touchcnt = 0;

void handler(int sig)
{
    printf("\nexiting...(%d)\n", sig);
    exit(0);
}

void perror_exit(char *error)
{
    perror(error);
    handler(9);
}

int main(int argc, char *argv[])
{
    struct input_event ev[64];
    int fd, rd, value, size = sizeof(struct input_event);
    char name[256] = "Unknown";
    char *device = NULL;

char filename[12] = "dat0bla.txt\0";
////
    FILE *fp;
////
    //Setup check
    if (argv[1] == NULL) {
	printf
	    ("Please specify (on the command line) the path to the dev event interface device\n");
	exit(0);
    }

    if ((getuid()) != 0)
	printf("You are not root! This may not work...\n");

    if (argc > 1)
	device = argv[1];

    //Open Device
    if ((fd = open(device, O_RDONLY)) == -1)
	printf("%s is not a vaild device.\n", device);

    //Print Device Name
    ioctl(fd, EVIOCGNAME(sizeof(name)), name);
    printf("Reading From : %s (%s)\n", device, name);

    while (1) {


	if ((rd = read(fd, ev, size * 64)) < size)
	    perror_exit("read()");

	value = ev[0].value;
	if (value != ' ' && ev[1].type == 1 && ((ev[1].value == 1) || (ev[1].value == 2))) {	// Only read the key press event
////////////// code here
	    if (ev[1].code == 30) {	//'a' means a real touch event is being received, not 'a' means, that the touch hasn't touched
		touchcnt++;
		if(touchcnt > 3){
			touchcnt = 0;
		if(recording == 0){
			start_recording = 1;		//if button pressed and not recording -> start recording
			recording = 0;
			stop_recording = 0;
		}
		if(recording == 1){
			recording = 0;			//if button pressed and already recording -> stop recording
			stop_recording = 1;
			start_recording = 0;
		}

	   }
           }
	   if(ev[1].code == 31){
		touchcnt = 0;
		if(recording == 1){
			recording = 1;
			start_recording = 0;
			stop_recording = 0;
		}
		if(recording == 0){
			recording = 0;
			start_recording = 0;
			stop_recording = 0;

		}

	   }
//	   if(ev[1].code == 33)


	    if (start_recording == 1) {
		filename[3]++;
                fp = fopen(filename, "a");
		    if(fp == NULL) {
		        perror("failed to open sample.txt");
		        return EXIT_FAILURE;
		    }
                fputs("AAAAAAAAAAAA STARTING AAAAAAAAAAAA\n",fp);
		printf("starting");
		stop_recording = 0;
		start_recording = 0;
		recording = 1;

	    }
////
	    if (recording == 1) {
		printf(" recording");
                fputs("AAAAAAAAAAAA RECORDING AAAAAAAAAAAA\n",fp);
	    }
////
	    if (stop_recording == 1) {
		  printf(" stopping");
                fputs( "AAAAAAAAAAAA STOP AAAAAAAAAAAAAAAA\n", fp);
                fclose(fp);
		recording = 0;
		start_recording = 0;
		stop_recording = 0;
	    }
printf("\n");

	}
//////////////
    }
    return 0;
}
