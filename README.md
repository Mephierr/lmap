# lmap
The tool for discovering active ports in network. Written in C++ using Qt for graphics.

# Build yourself
## Install Qt Creator
To build the application, you need to install Qt. In this guide, we will only discuss the *Qt Creator* installation.
If you are lucky, you don't have any problems with downloading it from the [official website](https://www.qt.io/download-dev). There is a [way](https://vc.ru/dev/1125830-kak-ustanovit-qt-qt5-qt6-v-rossii-cherez-onlain-installyator-pri-blokirovke-ip-adresov) to work around the country blocking. Follow this guide to install Qt Creator from Russia.
## Build using Qt Creator
After you have finished with installation (you probably need to make an account using VPN), launch Qt and press **Open Project...**, select your project's directory, and click on the **CMakeLists.txt** file. Press the Hammer button in the bottom-left corner of the IDE. Make sure that build finished successfully. Now you can run an application.
## Build using Bash
If you are the nerdos and want to build the application using bash and CMake, you can ethier use bash scripts `build_gui.sh` or `build_cli.sh` to build with Qt user interface or with cli interface respectively.
