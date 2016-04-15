#CC=${HOST_GCC}

#export CC BUILD_DIR STAGING_DIR TARGET_DIR
all:
	mkdir -p $(shell pwd)/../../staging/usr/lib/libplayer
	-$(MAKE) -C amffmpeg all
	-$(MAKE) -C amffmpeg install
	-$(MAKE) -C amplayer all
	-$(MAKE) -C amplayer install
	-$(MAKE) -C streamsource all
	-$(MAKE) -C streamsource install
	-$(MAKE) -C examples all
    
install:
	-$(MAKE) -C examples install

clean:
	-$(MAKE) -C amffmpeg clean
	-$(MAKE) -C streamsource clean
	-$(MAKE) -C examples clean

