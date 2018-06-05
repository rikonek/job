LKM=lkm
GENETLINK=genetlink
APP=src

all: uninstall chardev compileapp genetlink install run

chardev:
	cd $(LKM) && $(MAKE) build

compileapp:
	cd $(APP) && $(MAKE)

genetlink:
	cd $(GENETLINK) && $(MAKE) build

install:
	$(MAKE) -C $(LKM) install
	$(MAKE) -C $(GENETLINK) install

uninstall:
	$(MAKE) -C $(LKM) uninstall
	$(MAKE) -C $(GENETLINK) uninstall

clean:
	cd $(LKM) && $(MAKE) clean
	cd $(APP) && $(MAKE) clean
	cd $(GENETLINK) && $(MAKE) clean

run:
	cd $(APP) && ./1konsola.py

.PHONY: genetlink