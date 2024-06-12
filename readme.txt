莫明昊21307147
screenshot/下为四次运行的截图。
src/main.cpp即为主程序入口，也是Funny_JSON_Explorer领域模型中的FunnyJSONExplorer。
src/下为源文件和CMakeLists.txt
include/下为头文件。
run/bin/下为json文件和作为图标族来源的配置文件。

运行程序，首先要修改根目录下的 CMakeLists.txt 中的以下语句改为自己的c、c++编译器路径：
set (CMAKE_C_COMPILER "D:/compliers/mingw64_posix_seh/bin/gcc.exe")
set (CMAKE_CXX_COMPILER "D:/compliers/mingw64_posix_seh/bin/g++.exe")

运行根目录下的make_build.bat，运行完毕后，run/bin/下会出现main.exe ，运行main.exe即可看到运行结果