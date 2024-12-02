#include "AerodynamicsNode.hpp"

const std::string &AerodynamicsNode::getName() const
{
    return name;
}

void AerodynamicsNode::setName(const std::string &name)
{
    this->name = name;
}

const std::string &AerodynamicsNode::getPath() const
{
    return path;
}

void AerodynamicsNode::setPath(const std::string &path)
{
    this->path = path;
}

AerodynamicsNode::Type AerodynamicsNode::getType() const
{
    return type;
}

AeroProperty::AeroProperty()
{
    type = PROPERTY;
    
}

const std::string &AeroProperty::getDescription() const
{
    return description;
}

const std::string &AeroProperty::getUnit() const
{
    return unit;
}

const std::string &AeroProperty::getAccess() const
{
    return access;
}

const std::string &AeroProperty::getComment() const
{
    return comment;
}

Value::Value()
{
    type = VALUE;
}

double Value::getInput() const
{
    return input;
}

void Value::setInput(double input)
{
    this->input = input;
}

Function::Function()
{
    type = FUNCTION;
}

const std::string &Function::getFunctionType() const
{
    return functionType;
}

void Function::setFunctionType(const std::string &functionType)
{
    this->functionType = functionType;
}

const std::string &Function::getDescription() const
{
    return description;
}

void Function::setDescription(const std::string &description)
{
    this->description = description;
}

Table::Table()
{
    type = TABLE;
}

const std::string &Table::getRowProperty() const
{
    return rowProperty;
}

void Table::setRowProperty(const std::string &rowProperty)
{
    this->rowProperty = rowProperty;
}

const std::string &Table::getColumnProperty() const
{
    return columnProperty;
}

void Table::setColumnProperty(const std::string &columnProperty)
{
    this->columnProperty = columnProperty;
}

const std::string &Table::getTableData() const
{
    return tableData;
}

void Table::setTableData(const std::string &tableData)
{
    this->tableData = tableData;
}

Axis::Axis()
{
    type = AXIS;
}

Axis::AxisName Axis::getName() const
{
    return name;
}

void Axis::setName(AxisName name)
{
    this->name = name;
}

Axis::UnitName Axis::getUnit() const
{
    return unit;
}

void Axis::setUnit(UnitName unit)
{
    this->unit = unit;
}

// Initializing static maps
std::map<Axis::AxisName, std::string> Axis::axisNameToString = {
    { DRAG, "DRAG" },
    { SIDE, "SIDE" },
    { LIFT, "LIFT" },
    { ROLL, "ROLL" },
    { PITCH, "PITCH" },
    { YAW, "YAW" },
    { FORWARD, "FORWARD" },
    { RIGHT, "RIGHT" },
    { DOWN, "DOWN" }
};
std::map<std::string, Axis::AxisName> Axis::stringToAxisName = {
    { "DRAG", DRAG },
    { "SIDE", SIDE },
    { "LIFT", LIFT },
    { "ROLL", ROLL },
    { "PITCH", PITCH },
    { "YAW", YAW },
    { "FORWARD", FORWARD },
    { "RIGHT", RIGHT },
    { "DOWN", DOWN }
};
std::map<Axis::UnitName, std::string> Axis::unitNameToString = {
    { NONE, "NONE" },
    { LBS, "LBS" },
    { N, "N" },
    { LBSFT, "LBSFT" },
    { NM, "NM" }
};
std::map<std::string, Axis::UnitName> Axis::stringToUnitName = {
    { "NONE", NONE },
    { "LBS", LBS },
    { "N", N },
    { "LBSFT", LBSFT },
    { "NM", NM }
};