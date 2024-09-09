# drivers
Туториал по созданию модулей ядра на основании данных из книги "Linux_Device_Drivers" 3-го издания.  
Все модули являются псевдоустройствами и выполняют примитивную работу в оперативной памяти.  
Некоторые задания придуманы ChatGPT с полным описанием задачи. Эти задачи будут иметь "ii" в имени папки(искуственный интеллект).  
Цель туториала: познакомиться с api ядра для работы с драйверами + освоить приемы отладки. Все драйвера являются псевдоустройствами(они что-то простое делают в оперативной памяти).  
Цель подключения ChatGPT: получить задание максимально приближенное к текущей реальности.  

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

Примеры сделаны по следующим главам:
* 01_hello - Глава 2 "Сборка и запуск модулей"
* 02_chrdev_simple - Глава 3 "Символьные драйверы"
* 03_proc_rw - Глава 4 "Техники отладки"