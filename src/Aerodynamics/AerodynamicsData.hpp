#pragma once

#include <vector>
#include "AerodynamicsNode.hpp"

class AerodynamicsData {
private:
    std::vector<AerodynamicsNode> AerodynamicsNodes;
public:
    AerodynamicsData();

    const std::vector<AerodynamicsNode> getAerodynamicsNodes() const;
    void setAerodynamicsNodes(std::vector<AerodynamicsNode> AerodynamicsNodes);

    void fetchData();
    void saveData();
};
