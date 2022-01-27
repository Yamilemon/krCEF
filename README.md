# krCEF
krkr嵌入CEF插件

## 编译方式（VS2019为例）：

1. 下载cef二进制预构建包：https://pan.baidu.com/s/1TmzjLPSafPkqrbAeG-qfIQ 提取码：sora（这个是带了视频播放功能的）如有需要，可以自行下载（没有视频播放功能）：https://cef-builds.spotifycdn.com/index.html#windows32 或在这里clone下来自行编译 https://github.com/chromiumembedded/cef
2. 在环境变量中配置CEF_HOME指向下载下来的cef的解压目录。
3. 安装cmake（3.18以上版本）用cmake-gui构建libcef_dll_wrapper.lib的工程：https://blog.csdn.net/csdnyonghu123/article/details/87982333 这一步实在不行的话，可以试试在这里下载我编译好的libcef_dll_wrapper.lib静态库（/MT x86 32位）：https://pan.baidu.com/s/1SfDfmuCLYVopeysTw5HBhg 提取码：sora
4. 链接器里配置libcef_dll_wrapper.lib和libcef.lib静态库的目录（工程里已配置，但是可能路径不太对，需要重新调整一下）
5. 打开krcef.sln，解决方案中引用第三步中生成的libcef_dll_wrapper和ZERO_CHECK两个项目。（可选，如果上面cmake配置过不了这步可以跳过）
4. 生成后事件的中配置cefsimple.exe.manifest的目录还有输出这个dll的目录，其实就是第一行那个mt命令行的地方，那里要往dll里写入一个清单文件，不然打开网页会白屏，这里根据实际输出目录进行配置就好。
4. 选择win32 Release生成解决方案，编译完成。

## 运行方式：

1. 下载chromium运行依赖库：链接：https://pan.baidu.com/s/1QoeUpWqUCVlGUEXL3x7PHw 提取码：sora

2. 参考以下运行范例代码在startup.tjs中写入（或者再example里能找到）：

   ```javascript
   System.inform("I am shadow of Sora.");
   var win = new Window();
   win.width = 1280;
   win.height = 720;
   win.visible = true;
   win.caption = "我们不用很苦很累就能在krkr上运行minecraft";
   System.title = "我们不用很苦很累就能在krkr上运行minecraft";
   Plugins.link("krcef.dll");
   /*
       初始化浏览器
       @param1：命令行参数
       @param2：是否把浏览器窗口拉到最顶端（默认在最底端）
       @param3：初始网址
       @param4：left
       @param5：top
       @param6：width
       @param7：height
   */
   krCEF.init(void, false, "https://www.baidu.com", 0, 0, 1280, 720);
   // 浏览器初始化完成回调
   krCEF.onFinish = function(){
       // 把浏览器窗口拉到最顶端
       krCEF.toTop();
       // 加载url
       krCEF.loadUrl("http://mc.missthee.com/dist/index.html");
       // 关闭浏览器
       // krCEF.close();
   };
   ```

   运行krkr，即可看到对应的网页调用效果
