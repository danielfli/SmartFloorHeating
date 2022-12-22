# Smart Floorheating control

# Using Rasp Zero W

### uname -a:

Linux raspberrypi 5.10.63+ #1459 Wed Oct 6 16:40:27 BST 2021 armv6l GNU/Linux

### lscpu: 

Architecture:        armv6l
Byte Order:          Little Endian
CPU(s):              1
On-line CPU(s) list: 0
Thread(s) per core:  1
Core(s) per socket:  1
Socket(s):           1
Vendor ID:           ARM
Model:               7
Model name:          ARM1176
Stepping:            r0p7
CPU max MHz:         1000.0000
CPU min MHz:         700.0000
BogoMIPS:            697.95
Flags:               half thumb fastmult vfp edsp java tls

## Toolchain Cross building

https://github.com/tttapa/docker-arm-cross-toolchain

## External lib needed

- Boost property tree []()
- etl []()

### Install Lib 

boost lib

```bash
apt install libboost-all-dev
```

ETL lib (header only)

```bash
git clone https://github.com/ETLCPP/etl.git
cd etl
git checkout <targetVersion>
cmake -B build .
cmake --install build/
```

### Cross Build

install the lib to the chroot:

- /usr/local/include/etl/ /var/lib/schroot/chroots/rpizero-bullseye-armhf/usr/local/include/
- /usr/local/share/etl/ /var/lib/schroot/chroots/rpizero-bullseye-armhf/usr/local/share/

to the target:

- /usr/local/share/etl/ /usr/local/share/
- /usr/local/include/etl/ /usr/local/include/

```bash
scp -r /usr/local/include/etl/ $user@$ip:/usr/local/include/
scp -r e/usr/local/share/etl/ $user@$ip:/usr/local/share/
```
