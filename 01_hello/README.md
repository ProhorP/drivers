Задание:  
Создать модуль ядра, который при регистрации выведет 5 раз сообщение "Hello, Mom"  
А при выгрузке выведет сообщение "Goodbye, cruel world"
```
make
sudo insmod hello.ko number=5 whom="Mom"
sudo journalctl -r
sudo rmmod hello.ko
make clean
```
