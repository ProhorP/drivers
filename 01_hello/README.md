Задание:  
Создать модуль фдра, который при регистрации выведет 5 раз сообщение "Hello, Mom"  
А при выгрузке выведет сообщение "Goodbye, cruel world"
```
./build.sh
sudo insmod hello.ko number=5 whom="Mom"
sudo journalctl -r
sudo rmmod hello.ko
./clean.sh
```
