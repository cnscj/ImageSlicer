#include "Dispatcher.h"
Dispatcher *Dispatcher::s_instance = nullptr;

Dispatcher *Dispatcher::getInstance()
{
    if (!s_instance)
    {
        s_instance = new Dispatcher();
    }
    return s_instance;
}


Dispatcher::Dispatcher()
{

}
