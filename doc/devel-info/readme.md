# Devel Infomation & Links

## Raspberry Pi CPU 

### Datesheet

[https://www.raspberrypi.org/app/uploads/2012/02/BCM2835-ARM-Peripherals.pdf](Link)

### Library for bcm2835

[https://www.airspayce.com/mikem/bcm2835/index.html](Link)


## Setup Cross Building Env Linux

[https://github.com/tttapa/docker-arm-cross-toolchain](Link)

[https://github.com/Pro/raspi-toolchain](Link)

[https://github.com/robamu-org/raspberrypi-crosscompiling#rootfs](Link)

### Cross Debugging Libs env Workflow

[https://tttapa.github.io/Pages/Raspberry-Pi/C++-Development-RPiOS/Development-setup.html](Full example)

Install utils for the env

```bash
sudo apt install ubuntu-dev-tools
```

Build Raspberry rootfs:

```bash
wget -qO- https://archive.raspbian.org/raspbian.public.key | gpg --import -

mk-sbuild --arch=armhf bullseye --debootstrap-mirror=http://raspbian.raspberrypi.org/raspbian --name=rpizero-bullseye --debootstrap-keyring "$HOME/.gnupg/pubring.kbx --merged-usr" --skip-proposed --skip-updates --skip-security
```

Create Raspberry roofs with debootstrap. This command build a minimal filesystem for raspberry pi called (rpizero-bullseye-armhf)

```bash
mk-sbuild --arch=armhf bullseye --debootstrap-mirror=http://raspbian.raspberrypi.org/raspbian --name=rpizero-bullseye --debootstrap-keyring "$HOME/.gnupg/pubring.kbx --merged-usr" --skip-proposed --skip-updates --skip-security
```

Path to filesystem: /var/lib/schroot/chroots/rpizero-bullseye-armhf

Delete the Filesystem with:

```bash
 sudo sbuild-destroychroot rpizero-bullseye-armhf
```

Some Output after building rootfs:
Done building rpizero-bullseye-armhf.

```bash
 sudo schroot -c source:rpizero-bullseye-armhf -u root
 To ENTER an image snapshot: schroot -c rpizero-bullseye-armhf
 To BUILD within a snapshot: sbuild -A -d rpizero-bullseye-armhf PACKAGE*.dsc
 To BUILD for : sbuild -A -d rpizero-bullseye-armhf --host  PACKAGE*.dsc
```
Get Toolchain for the pi device (zero):

[https://github.com/tttapa/docker-arm-cross-toolchain/releases/tag/0.0.9](Download)

```bash
mkdir -p /opt
wget -qO- https://github.com/tttapa/docker-arm-cross-toolchain/releases/download/0.0.9/x-tools-armv6-rpi-linux-gnueabihf.tar.xz | tar xJ -C /opt
```

Bring the pi compilier to the same on the toolchain:

```bash
scp /opt/x-tools/armv6-rpi-linux-gnueabihf/armv6-rpi-linux-gnueabihf/sysroot/lib/libstdc++.so.6.0.30 root@192.168.3.145:~
ssh root@192.168.3.145 bash << 'EOF'
    sudo mkdir -p /usr/local/lib/arm-linux-gnueabihf
    sudo mv libstdc++.so.6.0.30 $_
    sudo ldconfig
EOF
```

Get the Cross-Compilier path:

Path: /opt/x-tools/armv6-rpi-linux-gnueabihf/bin/...-g++

Entering the chroot:

```bash
sudo schroot -c source:rpizero-bullseye-armhf -u root
```

Update the chroot:

```bash
sudo schroot -c source:rpizero-bullseye-armhf -u root
apt update
```


**Update the libstdc++ in the chroot:**

[https://manpages.debian.org/testing/schroot/schroot.1.de.html(schroot)

```bash
sudo mkdir -p /var/lib/schroot/chroots/rpizero-bullseye-armhf/usr/local/lib/arm-linux-gnueabihf

sudo cp /opt/x-tools/armv6-rpi-linux-gnueabihf/armv6-rpi-linux-gnueabihf/sysroot/lib/libstdc++.so.6.0.30 $_

sudo schroot -c source:rpizero-bullseye-armhf -u root -d / ldconfig
```

### Add Libraries

Note that the crossbuild-env shoud be the same as the raspi-env.

Installing Lib von apt Repo like so:

```bash
sudo sbuild-apt rpizero-buster-armhf apt-get install libboost-all-dev
```

