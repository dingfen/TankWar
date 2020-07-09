/*
 * Exception class
 * Throw exception in try catch statement
 */
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <exception>

using std::exception;

#ifndef _DF_TANKWAR_EXCEPTION_H
#define _DF_TANKWAR_EXCEPTION_H

class SDLErrorException : public exception {
public:   
    virtual const char* what() const throw() {
        return SDL_GetError();
    }
};

class TTFErrorException : public exception {
public:
    virtual const char *what() const throw() {
        return TTF_GetError();
    }
};

#endif // _DF_TANKWAR_EXCEPTION_H