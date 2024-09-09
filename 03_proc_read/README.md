Задание:  
Создать модуль ядра, который при регистрации сохранит строку, которую нужно вывести при вызове /proc/proc_read
```
make
sudo insmod proc_read.ko str="Hello"
cat /proc/proc_read
sudo rmmod proc_read.ko
make clean
```
