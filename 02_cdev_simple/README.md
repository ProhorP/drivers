Задание:  
Создать символный драйвер, который будет иметь в ядре область памяти задаваемую при загрузке.
В которым можно будет писать и из которого можно читать
```
make
sudo insmod chdev_simple.ko size=10000
sudo journalctl -r
sudo rmmod chdev_simple.ko
make clean
```
