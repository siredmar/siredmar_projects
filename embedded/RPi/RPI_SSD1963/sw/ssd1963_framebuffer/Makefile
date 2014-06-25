TARGET = ssd1963
ARCH   ?= arm
CROSS_COMPILE ?= arm-linux-gnueabihf-
export ARCH CROSS_COMPILE

obj-m += $(TARGET).o

KDIR = /home/armin/dev/RPi_SSD1963/misc/linux-3.6.11

KBUILD_TARGETS	:= clean help modules modules_install

.PHONY: all $(KBUILD_TARGETS)
all: modules

$(KBUILD_TARGETS):
	$(MAKE) -C $(KDIR) M=$(shell pwd) $@
copy:
	scp ssd1963.ko root@pi:/lib/modules/3.6.11+/kernel/drivers/video
mod: 
	ssh root@pi  'modprobe ssd1963'
reboot: 
	ssh root@pi 'reboot'
con:
	ssh root@pi 'con2fbmap 1 1'
kill:
	killall -9 ssh

