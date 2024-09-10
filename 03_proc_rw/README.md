Задание:  
Создать модуль ядра, который создаст /proc/proc_rw с буфером задаваемым при загрузке  
В него можно будет писать и читать из него строки.  
Не используется функции из книги "create_proc_read_entry" и "create_proc_entry" 
т.к. они были вырезаны из ядра версии 3.10 
```
make
sudo insmod proc_rw.ko size=100
echo 'Hello proc file!' > /proc/proc_rw
cat /proc/proc_rw
sudo rmmod proc_rw.ko
make clean
```
