# krCEF
krkr嵌入CEF插件

## 编译方式（VS2019为例）：

1. 下载cef二进制预构建包：https://pan.baidu.com/s/1TmzjLPSafPkqrbAeG-qfIQ 提取码：sora（这个是带了视频播放功能的）如有需要，可以自行下载（没有视频播放功能）：https://cef-builds.spotifycdn.com/index.html#windows32 或在这里clone下来自行编译 https://github.com/chromiumembedded/cef
2. 在环境变量中配置CEF_HOME指向下载下来的cef的解压目录。
3. 安装cmake（3.18以上版本）用cmake-gui构建libcef_dll_wrapper.lib的工程：https://blog.csdn.net/csdnyonghu123/article/details/87982333 这一步实在不行的话，可以试试在这里下载我编译好的libcef_dll_wrapper.lib静态库（/MT x86 32位）：https://pan.baidu.com/s/1SfDfmuCLYVopeysTw5HBhg 提取码：sora
4. 链接器里配置libcef_dll_wrapper.lib和libcef.lib静态库的目录（工程里已配置，但是可能路径不太对，需要重新调整一下）
5. 打开krcef.sln，解决方案中引用第三步中生成的libcef_dll_wrapper和ZERO_CHECK两个项目
4. 生成解决方案，编译完成。

## 运行方式：

1. 把预构建包中的bin文件下所有的文件拷贝到和krBodyAI.dll相同目录下。
2. example文件下有对用的tjs层调用方式（ps：把里面的`Plugins.link("json.dll");`注释掉）

运行krkr.exe主程序，在onframe中即可得到人体17个点的数据每帧回调，x为横坐标，y为纵坐标，score为该点坐标的可信度，数组一共由17个字典组成，样例里面附带了一个识别人体深蹲动作的简单算法