#pragma once

#include <string>
#include <vector>
#include <map>

class AerodynamicsNode {
public:
    enum Type {
        PROPERTY,
        VALUE,
        FUNCTION,
        TABLE,
        AXIS
    };

    const std::string& getName() const;
    void setName(const std::string& name);
    
    const std::string& getPath() const;
    void setPath(const std::string& path);
    
    Type getType() const;
protected:
    std::string name, path;
    Type type;
};

class AeroProperty: public AerodynamicsNode {
public:
    AeroProperty();

    const std::string& getDescription() const;
    const std::string& getUnit() const;
    const std::string& getAccess() const;
    const std::string& getComment() const;
private:
    std::string description, unit, access, comment;
};

class Value: public AerodynamicsNode {
public:
    Value();

    double getInput() const;
    void setInput(double input);
private:
    double input;
};

class Function: public AerodynamicsNode {
public:
    Function();

    const std::string& getFunctionType() const;
    void setFunctionType(const std::string& functionType);

    const std::string& getDescription() const;
    void setDescription(const std::string& description);
private:
    std::string functionType, description;
};

class Table: public AerodynamicsNode {
public:
    Table();

    const std::string& getRowProperty() const;
    void setRowProperty(const std::string& rowProperty);

    const std::string& getColumnProperty() const;
    void setColumnProperty(const std::string& columnProperty);

    const std::string& getTableData() const;
    void setTableData(const std::string& tableData);
private:
    std::string rowProperty, columnProperty;
    std::string tableData;
};

class Axis : public AerodynamicsNode {
public:
    Axis();

    enum AxisName {
        DRAG,
        SIDE,
        LIFT,
        ROLL,
        PITCH,
        YAW,
        FORWARD,
        RIGHT,
        DOWN
    };
    static std::map<AxisName, std::string> axisNameToString;
    static std::map<std::string, AxisName> stringToAxisName;
    enum UnitName {
        LBS,
        N,
        LBSFT,
        NM
    };
    static std::map<UnitName, std::string> unitNameToString;
    static std::map<std::string, UnitName> stringToUnitName;

    AxisName getName() const;
    void setName(AxisName name);

    UnitName getUnit() const;
    void setUnit(UnitName unit);

private:
    AxisName name;
    UnitName unit;
    std::string scaleType;
};
