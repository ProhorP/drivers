Задание:  
Создать модуль ядра, который создаст /proc/proc_read  
В него можно будет писать и читать из него строки
```
make
sudo insmod proc_read.ko
echo 'Hello proc file!' > /proc/proc_read
cat /proc/proc_read
sudo rmmod proc_read.ko
make clean
```
