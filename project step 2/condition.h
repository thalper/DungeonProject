#ifndef CONDITION_H_
#define CONDITION_H_
#include <string>
#include <vector>

class Condition {
public:
    Condition();
    void setHas(bool has);
    void setName(std::string name);
    void setOwner(std::string owner);
    void setStatus(std::string status);
    void setObject(std::string object);
    std::string getType();
    int getHas();
    std::string getObject();
    std::string getStatus();
    std::string getOwner();
   

private:
    bool Has;
    std::string Name; // Name of object 
    std::string Owner; // owner of object
    std::string Status; // status of object
    std::string Object; 
};


#endif /* CONDITION_H_ */