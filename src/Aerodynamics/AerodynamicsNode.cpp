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

Property::Property()
{
    type = PROPERTY;
    
}

const std::string &Property::getDescription() const
{
    return description;
}

const std::string &Property::getUnit() const
{
    return unit;
}

const std::string &Property::getAccess() const
{
    return access;
}

const std::string &Property::getComment() const
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

const std::string &Table::getColumnProperty() const
{
    return columnProperty;
}

const std::vector<double> &Table::getTableData() const
{
    return tableData;
}

void Table::setTableData(const std::vector<double> &tableData)
{
    this->tableData = tableData;
}

Axis::Axis()
{
    type = AXIS;
}

Axis::AxisName Axis::getname() const
{
    return name;
}

void Axis::setAxisName(AxisName name)
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
