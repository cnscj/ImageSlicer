#ifndef DISPATCHER_H
#define DISPATCHER_H


class Dispatcher
{
public:
    static Dispatcher *getInstance();
public:
    void dispatchEvent(int);
    void addEventListener();
    void removeEventListener();
private:
    Dispatcher();
private:
    static Dispatcher *s_instance;
};

#endif // DISPATCHER_H
