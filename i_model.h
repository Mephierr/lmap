#ifndef IMODEL_H
#define IMODEL_H

#include <string>
#include <vector>

using Port = int;
using Ports = std::vector<Port>;
using IPAddress = std::string;
class IModel {
public:
    virtual ~IModel(){};
    // returns vector of opened ports
    virtual Ports GetOpenedPorts(const IPAddress& address, Port from, Port to) = 0;
};

#endif // IMODEL_H
