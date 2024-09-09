Задание:  
Создать модуль ядра, который создаст /proc/proc_rw с буфером задаваемым при загрузке  
В него можно будет писать и читать из него строки  
Не используется функция из книги "create_proc_read_entry" т.к. она была вырезана из ядра  
```
make
sudo insmod proc_rw.ko size=100
echo 'Hello proc file!' > /proc/proc_rw
cat /proc/proc_rw
sudo rmmod proc_rw.ko
make clean
```
