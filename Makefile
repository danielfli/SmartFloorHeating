.PHONY : clean 


clean: 
	rm -rf out/

build-zero:
	mkdir -p out/build/zeroarm6l-debug-cross
	cmake -DCMAKE_TOOLCHAIN_FILE:FILEPATH=cmake/crossarmv6l.cmake \
	-DPATH_INSTALLDIR=out/build/linux-debug-cross/install \
	-DRASPIZERO_TOOLCHAIN=/opt/x-tools/armv6-rpi-linux-gnueabihf/ -DCMAKE_BUILD_TYPE=Debug \
	-DBUILDING_RASPI_ZERO=true -DIPTARGET=192.168.3.145 \
	-DPATH_SYSROOT=/opt/x-tools/armv6-rpi-linux-gnueabihf/armv6-rpi-linux-gnueabihf/sysroot \
	-DCMAKE_CROSS_ZERO_MODULE=crossarmv6l -DCMAKE_TOOLCHAIN_FILE=/opt/x-tools/armv6-rpi-linux-gnueabihf \
	 -DCMAKE_INSTALL_PREFIX=out/install/linux-debug-cross \
	 -S . -B out/build/zeroarm6l-debug-cross -G "Unix 
