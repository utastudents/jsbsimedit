#pragma once

#include <vector>
#include <AerodynamicsNode.hpp>

class AerodynamicsData {
private:
    std::vector<AerodynamicsNode> AerodynamicsNodes;
public:
    AerodynamicsData();

    std::vector<AerodynamicsNode> getAerodynamicsNodes();
    void setAerodynamicsNodes(std::vector<AerodynamicsNode> AerodynamicsNodes);

    void fetchData();
    void saveData();
};