#ifndef BOOM_BOOMEXCEPTIONS_H
#define BOOM_BOOMEXCEPTIONS_H
#include <exception>

class BoomExceptions : public std::exception{ };

class InvalidInput : public BoomExceptions{ };

class NodeAlreadyExists : public BoomExceptions { };

class NodeDoesntExist : public BoomExceptions { };

#endif //BOOM_BOOMEXCEPTIONS_H
