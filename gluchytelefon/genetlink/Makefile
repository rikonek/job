obj-m+=genetlink.o

KERNEL_DIR=/lib/modules/$(shell uname -r)/build

all: uninstall build install

build:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) clean

install:
	-sudo insmod genetlink.ko

uninstall:
	-sudo rmmod genetlink