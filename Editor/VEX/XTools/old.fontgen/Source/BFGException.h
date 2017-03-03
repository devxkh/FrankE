// BFG license goes here

#ifndef BFGEXCEPTION_H
#define BFGEXCEPTION_H


#include <exception>
#include <string>


namespace BFG
{
    /// An exception with a description string
    class Exception :
        public std::exception
    {
    public:
        /// Standard constructor
        Exception (const std::string& message): mMessage(message) {}
        /// Standard destructor
        virtual ~Exception () throw () {}
        //-------------------------------------------------
        /// Return the exception's payload message
        virtual const char* what () const throw () { return mMessage.data(); }
    private:
        std::string mMessage;
    };
}


#endif