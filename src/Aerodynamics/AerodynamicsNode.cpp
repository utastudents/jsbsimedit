#include "AerodynamicsNode.hpp"

const std::string &AerodynamicsNode::getName() const
{
    std::string *t = new std::string();
    return *t;
}

void AerodynamicsNode::setName(const std::string &name)
{
}

const std::string &AerodynamicsNode::getPath() const
{
    std::string *t = new std::string();
    return *t;
}

void AerodynamicsNode::setPath(const std::string &path)
{
}

AerodynamicsNode::Type AerodynamicsNode::getType() const
{
    return (AerodynamicsNode::Type) 0;
}

Property::Property()
{
}

const std::string &Property::getDescription() const
{
    std::string *t = new std::string();
    return *t;
}

const std::string &Property::getUnit() const
{
    std::string *t = new std::string();
    return *t;
}

const std::string &Property::getAccess() const
{
    std::string *t = new std::string();
    return *t;
}

const std::string &Property::getComment() const
{
    std::string *t = new std::string();
    return *t;
}

Value::Value()
{
}

double Value::getInput() const
{
    return 0.0;
}

void Value::setInput(double input)
{
}

Function::Function()
{
}

const std::string &Function::getFunctionType() const
{
    std::string *t = new std::string();
    return *t;
}

void Function::setFunctionType(const std::string &functionType)
{
}

const std::string &Function::getDescription() const
{
    std::string *t = new std::string();
    return *t;
}

void Function::setDescription(const std::string &description)
{
}

Table::Table()
{
}

const std::string &Table::getRowProperty() const
{
    std::string *t = new std::string();
    return *t;
}

const std::string &Table::getColumnProperty() const
{
    std::string *t = new std::string();
    return *t;
}

const std::vector<double> &Table::getTableData() const
{
    std::vector<double> *t= new std::vector<double>();
    return *t;
}

void Table::setTableData(const std::vector<double> &tableData)
{
}

Axis::Axis()
{
}

Axis::AxisName Axis::getname() const
{
    return Axis::AxisName (0);
}

void Axis::setAxisName(AxisName name)
{
}

Axis::UnitName Axis::getUnit() const
{
    return Axis::UnitName (0);
}

void Axis::setUnit(UnitName unit)
{
}
