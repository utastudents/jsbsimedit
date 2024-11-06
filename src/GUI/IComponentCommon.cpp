#include "IComponentCommon.hpp"

namespace JSBEdit{

IComponentCommon::IComponentCommon(const std::string &compName, ComponentType& type)
    : m_componentName(compName), m_componentType(type)
{
}

std::string IComponentCommon::GetName() const
{
    return m_componentName;
}

ComponentType IComponentCommon::GetComponentType() const
{
    return m_componentType;
}

void IComponentCommon::SetName(const std::string &newName)
{
    m_componentName = newName;
}

Glib::RefPtr<Gtk::Window> IComponentCommon::CreateWindow()
{
    return Glib::RefPtr<Gtk::Window>(new Gtk::Window());
}

//I still think this is better suited to stay in a external file...
const std::string IComponentCommon::COMMON_TAB = R"(<?xml version='1.0' encoding='UTF-8'?>
<!-- Created with Cambalache 0.92.1 -->
<interface>
  <!-- interface-name commonui.ui -->
  <requires lib="gtk" version="4.12"/>
  <object class="GtkWindow" id="window">
    <property name="visible">False</property>
    <child>
      <object class="GtkBox" id="windowContainer">
        <property name="hexpand">True</property>
        <property name="margin-bottom">5</property>
        <property name="margin-end">5</property>
        <property name="margin-start">5</property>
        <property name="margin-top">5</property>
        <property name="vexpand">True</property>
      </object>
    </child>
  </object>
  <object class="GtkBox" id="commonTab">
    <property name="hexpand">True</property>
    <property name="margin-bottom">5</property>
    <property name="margin-top">5</property>
    <property name="orientation">vertical</property>
    <property name="vexpand">True</property>
    <child>
      <object class="GtkBox" id="nameBox">
        <property name="margin-bottom">5</property>
        <property name="margin-end">5</property>
        <property name="margin-start">5</property>
        <property name="margin-top">5</property>
        <property name="orientation">vertical</property>
        <child>
          <object class="GtkLabel" id="nameLabel">
            <property name="label">Name:</property>
          </object>
        </child>
        <child>
          <object class="GtkEntry" id="nameEntry"/>
        </child>
      </object>
    </child>
    <child>
      <object class="GtkBox" id="typeBox">
        <property name="margin-bottom">5</property>
        <property name="margin-end">5</property>
        <property name="margin-start">5</property>
        <property name="margin-top">5</property>
        <property name="orientation">vertical</property>
        <child>
          <object class="GtkLabel" id="typeLabel">
            <property name="label">Type:</property>
          </object>
        </child>
        <child>
          <object class="GtkDropDown" id="typeDropDown">
            <property name="margin-bottom">5</property>
            <property name="margin-end">5</property>
            <property name="margin-start">5</property>
            <property name="margin-top">5</property>
          </object>
        </child>
      </object>
    </child>
    <child>
      <object class="GtkBox" id="gainBox">
        <property name="margin-bottom">5</property>
        <property name="margin-end">5</property>
        <property name="margin-start">5</property>
        <property name="margin-top">5</property>
        <property name="orientation">vertical</property>
        <child>
          <object class="GtkLabel" id="clipperLabel">
            <property name="label">Clipper:</property>
            <property name="margin-bottom">5</property>
            <property name="margin-top">5</property>
          </object>
        </child>
        <child>
          <object class="GtkBox" id="checkBoxBox">
            <property name="margin-bottom">5</property>
            <property name="margin-end">5</property>
            <property name="margin-start">5</property>
            <property name="margin-top">5</property>
            <child>
              <object class="GtkLabel" id="EnableLabel">
                <property name="label">Enable:</property>
              </object>
            </child>
            <child>
              <object class="GtkCheckButton" id="EnableCheck"/>
            </child>
          </object>
        </child>
        <child>
          <object class="GtkBox" id="minMaxBox">
            <property name="margin-bottom">5</property>
            <property name="margin-end">5</property>
            <property name="margin-start">5</property>
            <property name="margin-top">5</property>
            <property name="orientation">vertical</property>
            <child>
              <object class="GtkLabel" id="maxLabel">
                <property name="label">Max:</property>
                <property name="margin-bottom">5</property>
                <property name="margin-top">5</property>
              </object>
            </child>
            <child>
              <object class="GtkEntry" id="maxEntry"/>
            </child>
            <child>
              <object class="GtkLabel" id="minLabel">
                <property name="label">Min:</property>
                <property name="margin-bottom">5</property>
                <property name="margin-top">5</property>
              </object>
            </child>
            <child>
              <object class="GtkEntry" id="minEntry"/>
            </child>
          </object>
        </child>
      </object>
    </child>
    <child>
      <object class="GtkBox" id="buttonBox">
        <property name="margin-bottom">5</property>
        <property name="margin-end">5</property>
        <property name="margin-start">5</property>
        <property name="margin-top">5</property>
        <child>
          <object class="GtkButton" id="saveButton">
            <property name="hexpand">True</property>
            <property name="label">Accept</property>
            <property name="margin-bottom">5</property>
            <property name="margin-end">5</property>
            <property name="margin-start">5</property>
            <property name="margin-top">5</property>
          </object>
        </child>
        <child>
          <object class="GtkButton" id="cancelButton">
            <property name="hexpand">True</property>
            <property name="label">Cancel</property>
            <property name="margin-bottom">5</property>
            <property name="margin-end">5</property>
            <property name="margin-start">5</property>
            <property name="margin-top">5</property>
          </object>
        </child>
      </object>
    </child>
  </object>
</interface>)";

};