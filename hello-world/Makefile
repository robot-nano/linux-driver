TARGET_MODULE:=helloworld

ifneq ($(KERNELRELEASE),)
	$(TARGET_MODULE)-objs:=helloworld_imx.o
	obj-m:=$(TARGET_MODULE).o
else
	BUILDSYSTEM_DIR:=/lib/modules/$(shell uname -r)/build
	PWD:=$(shell pwd)

all:
	$(MAKE) -C $(BUILDSYSTEM_DIR) M=$(PWD) modules
clean:
	$(MAKE) -C $(BUILDSYSTEM_DIR) M=$(PWD) clean
endif