# lmap
The tool for discovering active ports in network. Written on C++ using Qt for graphics.

# Build yourself
## Install Qt Creator
To build the application, you need to install Qt. In this guide we will only discuss the *Qt Creator* installation.
If you are lucky guy, you don't have any problems with downloading it from [official website](https://www.qt.io/download-dev). There is a [way](https://vc.ru/dev/1125830-kak-ustanovit-qt-qt5-qt6-v-rossii-cherez-onlain-installyator-pri-blokirovke-ip-adresov) to work around the country blocking. Follow this guide to install Qt Creator from Russia.
## Build using Qt Creator
After you finished with installation (you probably need to make an account using VPN), launch Qt and press **Open Project...**, select your project's directory and click on **CMakeLists.txt** file. Press the Hammer button at the bottom-left corner of the IDE. Make sure that build finished successfully. Now you can run an application.
## Build using Bash
If you are the nerdos and want to build the application using bash and CMake, follow these steps: 
* `cd` to your directory with the application.
* `mkdir build && cd build`
* You need to add some environment variables to show cmake where the Qt is installed. You can skip this step if you already built the application with Qt Creator. 
```bash
export Qt6_DIR=/home/USERNAME/Qt/VERSION/gcc_64/lib/cmake/Qt6
export Qt5_DIR=/home/USERNAME/Qt/VERSION/gcc_64/lib/cmake/Qt6
```
* Configure cmake using `cmake ..`.
* Build the project using `cmake --build . --target all`
Your executable will be in the build directory called `lmap`.
