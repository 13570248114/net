# net--一个仿muduo的简单网络库
输入make,自动生成静态库,把静态库和存放头文件的文件夹net拷贝到适当的地方即可.

net是仿照muduo[1]实现的一个基于Reactor模式的多线程C++网络库，经过适当简化以后代码量约为2000行。简化的部分如下：

- 多线程依赖于C++11提供的std::thread库，而不是重新封装POSIX thread API。

- 定时器依赖于C++11提供的std::chrono库，而不是自己实现Timstamp类，也不用直接调用`gettimeofday()`。这样写的好处之一是我们不必再为定时器API的时间单位操心[2]：

  ```c++
  using namespace std::literals::chrono_literals;
  loop.runEvery(10s, [](){INFO("run every 10 seconds");});
  loop.runAfter(24h, [](){INFO("run after 24 hours");});
  loop.runAt(Clock::nowAfter(15min), [](){INFO("run 15 minutes later");});
  ```

- 默认为accept socket开启SO_RESUEPORT选项，这样每个线程都有自己的Acceptor，就不必在线程间传递connection socket。开启该选项后内核会将TCP连接分摊给各个线程，因此不必担心负载均衡的问题。

- 仅具有简单的日志输出功能，用于调试。

- 仅使用epoll，不使用poll和select。


