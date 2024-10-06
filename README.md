# Qt_thread
Для запуска проекта нужно выполнить следующие действия:
- Собрать проект:
```sh
mkdir build
cd build
cmake ..
cmake --build .
cd ..
```
- Для работы эмулятора com-порта необходима программа socat. Для эмуляции ввести команду:
```sh
sudo socat -d -d pty,raw,echo=0,link=/dev/ttyV0,b115200 pty,raw,echo=0,link=/dev/ttyV1,b115200
```

- Запуск приложений:
```sh
sudo ./Receiver 8080 8081 /dev/ttyV0
sudo ./Sender 8080 8081 /dev/ttyV1
```
