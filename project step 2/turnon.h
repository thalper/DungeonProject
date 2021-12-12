#ifndef TURNON_H_
#define TURNON_H_
#include <string>
#include <vector>
#include <iostream>


class Turnon {
public:
    Turnon();
    void setPrint(std::string print);
    void setAction(std::string action);
    void setUsed();
    std::string getPrint();
    std::string getAction();
    int getUsed();

   

private:
    std::string Print;
    std::string Action;
    int Used;
};


#endif /* TURNON_H_ */