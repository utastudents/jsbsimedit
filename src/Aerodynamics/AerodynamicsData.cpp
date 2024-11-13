#include "AerodynamicsData.hpp"

AerodynamicsData::AerodynamicsData()
{
}

const std::vector<AerodynamicsNode> AerodynamicsData::getAerodynamicsNodes() const
{
    std::vector<AerodynamicsNode> t;
    return t;
}

void AerodynamicsData::setAerodynamicsNodes(std::vector<AerodynamicsNode> nodes)
{
    AerodynamicsNodes = nodes;
}

void AerodynamicsData::fetchData()
{
}

void AerodynamicsData::saveData()
{
}
