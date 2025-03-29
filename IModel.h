#ifndef IMODEL_H
#define IMODEL_H

#include <vector>

using Port = int;
using Ports = std::vector<Port>;
class IModel {
public:
    // returns vector of opened ports
    virtual Ports GetOpenedPorts(Port from, Port to) = 0;
};

#endif // IMODEL_H
