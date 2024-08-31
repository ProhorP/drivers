# drivers
Build on Linux Debian 12.6
```
user@debian:~$ uname -r
6.1.0-23-amd64
```

build kernel
```
sudo apt-get install git fakeroot build-essential ncurses-dev xz-utils libssl-dev bc flex libelf-dev bison
wget https://mirrors.edge.kernel.org/pub/linux/kernel/v6.x/linux-6.1.tar.xz
tar -xf linux-6.1.tar.xz
cd linux-6.1
make defconfig
make -j4
```