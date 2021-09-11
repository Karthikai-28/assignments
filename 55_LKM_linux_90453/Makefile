obj-m += simple.o
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean


# obj-m += simple.o

# KERNEL_MAKE := $(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(shell pwd)

# all:
# 	$(KERNEL_MAKE) modules

# # Use install and uninstall targets for debug and developement purpose
# install:
# 	sudo insmod simple.ko

# uninstall:
# 	sudo rmmod simple.ko

# clean:
# 	$(KERNEL_MAKE) clean
# 	$(RM) *.o.ur-safe
