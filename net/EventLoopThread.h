
#ifndef EVENTLOOPTHREAD_H
#define EVENTLOOPTHREAD_H

#include <thread>
#include "Callbacks.h"
#include "CountDownLatch.h"

namespace net
{

class EventLoop;

class EventLoopThread: noncopyable
{
public:
    EventLoopThread() = default;
    ~EventLoopThread();

    EventLoop* startLoop();

private:
    void runInThread();

    bool started_ = false;
    EventLoop* loop_ = nullptr;
    std::thread thread_;
    CountDownLatch latch_{1};
};

}

#endif //EVENTLOOPTHREAD_H
