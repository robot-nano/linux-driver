TARGET_MODULE:=platform-driver

ifneq ($(KERNELRELEASE),)
	$(TARGET_MODULE)-objs:=platform_driver.o
	obj-m:=$(TARGET_MODULE).o
else
	BUILDSYSTEM_DIR:=/lib/modules/$(shell uname -r)/build
	PWD:=$(shell pwd)

all:
	$(MAKE) -C $(BUILDSYSTEM_DIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(BUILDSYSTEM_DIR) M=$(PWD) clean
endif