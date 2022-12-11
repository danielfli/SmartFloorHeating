.PHONY : clean 

clean: 
	rm -rf out/

build-zero:
	mkdir -p out/build/cross
	cmake -DBUILDING_RASPI_ZERO=true -DPATH_CMAKE_MODUL=crossarmv6l.cmake \
	-DCMAKE_TOOLCHAIN_FILE:FILEPATH=cmake/crossarmv6l.cmake\
	-DPATH_INSTALLDIR=out/build/cross/install \
	-DCMAKE_BUILD_TYPE=Debug -DIPTARGET=192.168.2.145 -DUSER=root -DPASSWORD=123 \
	-DCMAKE_INSTALL_PREFIX=out/build/cross/install \
	-S . -B out/build/cross -G Ninja
	cd out/build/cross && ninja
