#include "AerodynamicsNode.hpp"

const std::string &AerodynamicsNode::getName() const
{
}

void AerodynamicsNode::setName(const std::string &name)
{
}

const std::string &AerodynamicsNode::getPath() const
{
}

void AerodynamicsNode::setPath(const std::string &path)
{
}

AerodynamicsNode::Type AerodynamicsNode::getType() const
{
}

Property::Property()
{
}

const std::string &Property::getDescription() const
{
}

const std::string &Property::getUnit() const
{
}

const std::string &Property::getAccess() const
{
}

const std::string &Property::getComment() const
{
}

Value::Value()
{
}

double Value::getInput() const
{
}

void Value::setInput(double input)
{
}

Function::Function()
{
}

const std::string &Function::getFunctionType() const
{
}

void Function::setFunctionType(const std::string &functionType)
{
}

const std::string &Function::getDescription() const
{
}

void Function::setDescription(const std::string &description)
{
}

Table::Table()
{
}

const std::string &Table::getRowProperty() const
{
}

const std::string &Table::getColumnProperty() const
{
}

const std::vector<double> &Table::getTableData() const
{
}

void Table::setTableData(const std::vector<double> &tableData)
{
}

Axis::Axis()
{
}

Axis::AxisName Axis::getname() const
{
}

void Axis::setAxisName(AxisName name)
{
}

Axis::UnitName Axis::getUnit() const
{
}

void Axis::setUnit(UnitName unit)
{
}
