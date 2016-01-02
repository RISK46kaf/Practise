#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H
#include <exception>

struct MyException : public std::exception
{
    explicit MyException(const char* exeptionName) : name(exeptionName) {}
    const char* name;

    const char * what () const throw ()
    {
        return name;
    }
};
#endif // MYEXCEPTION_H

