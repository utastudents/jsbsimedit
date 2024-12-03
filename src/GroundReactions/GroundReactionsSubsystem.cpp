#include <iostream>
#include <assert.h>
#include "inc/XML_api.hpp"
#include "GroundReactionsSubsystem.hpp"

GroundReactionsSubsystem::GroundReactionsSubsystem() {
    m_Name = "GroundReactions";
    std::cout << "In GroundReactionsSubsystem contructor" << std::endl; 
}

GroundReactionsSubsystem::LandingGearSetupDialog::LandingGearSetupDialog() {
    set_modal(true);

    set_title("Landing Gear Setup");
    set_default_size(715, 620);

    auto contentArea = get_content_area();

    // Create a grid for popup layout
    auto p_Grid = Gtk::make_managed<Gtk::Grid>();
    p_Grid->set_row_spacing(10);
    p_Grid->set_column_spacing(10);
    contentArea->append(*p_Grid);

    int p_row = 0;

    // Name
    auto nameLabel = Gtk::make_managed<Gtk::Label>("Name");
    auto nameTextbox = Gtk::make_managed<Gtk::Entry>();
    nameTextbox->set_text("Name.");
    p_Grid->attach(*nameLabel, 0, p_row);
    p_Grid->attach(*nameTextbox, 1, p_row);

    // Structure
    auto structureLabel = Gtk::make_managed<Gtk::Label>("Structure");
    auto structureTextbox = Gtk::make_managed<Gtk::Entry>();
    structureTextbox->set_text("Structure.");
    p_Grid->attach(*structureLabel, 3, p_row);
    p_Grid->attach(*structureTextbox, 4, p_row++);

    // Location
    auto locationLabel = Gtk::make_managed<Gtk::Label>("Location");
    p_Grid->attach(*locationLabel, 0, p_row++);

    auto xLabel = Gtk::make_managed<Gtk::Label>("x =");
    auto xTextbox = Gtk::make_managed<Gtk::Entry>();
    xTextbox->set_text("X.");

    auto yLabel = Gtk::make_managed<Gtk::Label>("y =");
    auto yTextbox = Gtk::make_managed<Gtk::Entry>();
    yTextbox->set_text("Y.");

    auto zLabel = Gtk::make_managed<Gtk::Label>("z =");
    auto zTextbox = Gtk::make_managed<Gtk::Entry>();
    zTextbox->set_text("Z.");

    auto coordinateUnitDropDown = Gtk::make_managed<Gtk::ComboBoxText>();
    coordinateUnitDropDown->append("IN");
    coordinateUnitDropDown->append("FT");
    coordinateUnitDropDown->append("M");
    coordinateUnitDropDown->set_active(0);

    p_Grid->attach(*xLabel, 0, p_row);
    p_Grid->attach(*xTextbox, 1, p_row);
    p_Grid->attach(*yLabel, 2, p_row);
    p_Grid->attach(*yTextbox, 3, p_row);
    p_Grid->attach(*zLabel, 4, p_row);
    p_Grid->attach(*zTextbox, 5, p_row);
    p_Grid->attach(*coordinateUnitDropDown, 6, p_row++);

    // Spring Coefficient
    auto springCoefficientLabel = Gtk::make_managed<Gtk::Label>("Spring Coefficient =");
    auto springCoefficientTextbox = Gtk::make_managed<Gtk::Entry>();
    springCoefficientTextbox->set_text("Spring Coefficient.");

    auto springCoefficientUnitDropDown = Gtk::make_managed<Gtk::ComboBoxText>();
    springCoefficientUnitDropDown->append("LBS/FT");
    springCoefficientUnitDropDown->append("N/M");
    springCoefficientUnitDropDown->set_active(0);

    p_Grid->attach(*springCoefficientLabel, 0, p_row);
    p_Grid->attach(*springCoefficientTextbox, 1, p_row);
    p_Grid->attach(*springCoefficientUnitDropDown, 2, p_row++);

    // Damping Coefficient
    auto dampingCoefficientLabel = Gtk::make_managed<Gtk::Label>("Damping Coefficient =");
    auto dampingCoefficientTextbox = Gtk::make_managed<Gtk::Entry>();
    dampingCoefficientTextbox->set_text("Damping Coefficientt.");

    auto dampingCoefficientUnitDropDown = Gtk::make_managed<Gtk::ComboBoxText>();
    dampingCoefficientUnitDropDown->append("LBS/FT/SEC");
    dampingCoefficientUnitDropDown->append("N/M/SEC");
    dampingCoefficientUnitDropDown->set_active(0);

    p_Grid->attach(*dampingCoefficientLabel, 0, p_row);
    p_Grid->attach(*dampingCoefficientTextbox, 1, p_row);
    p_Grid->attach(*dampingCoefficientUnitDropDown, 2, p_row++);

    // Static Friction
    auto staticFrictionLabel = Gtk::make_managed<Gtk::Label>("Static Friction =");
    auto staticFrictionTextbox = Gtk::make_managed<Gtk::Entry>();
    staticFrictionTextbox->set_text("Static Friction.");

    p_Grid->attach(*staticFrictionLabel, 0, p_row);
    p_Grid->attach(*staticFrictionTextbox, 1, p_row++);

    // Dynamic Friction
    auto dynamicFrictionLabel = Gtk::make_managed<Gtk::Label>("Dynamic Friction =");
    auto dynamicFrictionTextbox = Gtk::make_managed<Gtk::Entry>();
    dynamicFrictionTextbox->set_text("Dynamic Friction.");

    p_Grid->attach(*dynamicFrictionLabel, 0, p_row);
    p_Grid->attach(*dynamicFrictionTextbox, 1, p_row++);

    // Rolling Friction
    auto rollingFrictionLabel = Gtk::make_managed<Gtk::Label>("Rolling Friction =");
    auto rollingFrictionTextbox = Gtk::make_managed<Gtk::Entry>();
    rollingFrictionTextbox->set_text("Rolling Friction.");

    p_Grid->attach(*rollingFrictionLabel, 0, p_row);
    p_Grid->attach(*rollingFrictionTextbox, 1, p_row++);

    // Max Steer
    auto maxSteerLabel = Gtk::make_managed<Gtk::Label>("Max Steer =");
    auto maxSteerTextbox = Gtk::make_managed<Gtk::Entry>();
    maxSteerTextbox->set_text("Max Steer.");

    auto maxSteerUnitDropDown = Gtk::make_managed<Gtk::ComboBoxText>();
    maxSteerUnitDropDown->append("DEG");
    maxSteerUnitDropDown->append("RAD");
    maxSteerUnitDropDown->set_active(0);    

    p_Grid->attach(*maxSteerLabel, 0, p_row);
    p_Grid->attach(*maxSteerTextbox, 1, p_row);
    p_Grid->attach(*maxSteerUnitDropDown, 2, p_row++);

    // Brake Group
    auto brakeGroupLabel = Gtk::make_managed<Gtk::Label>("Brake Group =");

    auto brakeGroupUnitDropDown = Gtk::make_managed<Gtk::ComboBoxText>();
    brakeGroupUnitDropDown->append("NONE");
    brakeGroupUnitDropDown->append("LEFT");
    brakeGroupUnitDropDown->append("RIGHT");
    brakeGroupUnitDropDown->append("CENTER");
    brakeGroupUnitDropDown->append("NOSE");
    brakeGroupUnitDropDown->append("TAIL");  
    brakeGroupUnitDropDown->set_active(0);

    p_Grid->attach(*brakeGroupLabel, 0, p_row);
    p_Grid->attach(*brakeGroupUnitDropDown, 1, p_row++);

    // Retractable
    auto retractableLabel = Gtk::make_managed<Gtk::Label>("Retractable =");
    auto retractableCheckbox = Gtk::make_managed<Gtk::CheckButton>();

    p_Grid->attach(*retractableLabel, 0, p_row);
    p_Grid->attach(*retractableCheckbox, 1, p_row++);

    // Ok and Cancel Buttons
    auto okButton = Gtk::make_managed<Gtk::Button>("OK");
    okButton->signal_clicked().connect([this]() { this->close(); });
    p_Grid->attach(*okButton, 0, p_row);

    auto cancelButton = Gtk::make_managed<Gtk::Button>("Cancel");
    cancelButton->signal_clicked().connect([this]() { this->close(); });
    p_Grid->attach(*cancelButton, 1, p_row++);
}

void GroundReactionsSubsystem::Create() {
    std::cout << "in GroundReactionsSubsystem::Create" << std::endl;

/*  this code is provided to help the group extract info from the xml
 *  file.
 *  "here" may or may not be the place for this code.  please
 *  understand it, and then cut and paste it, or re-write it, or
 *  whatever is needed.
 */
    assert(xmlptr());

   // these variables are local to the constructor!! be aware..
   //
   // you probably want to test the value from GetName(), before the data is used...
   //
   //
   std::vector<JSBEdit::XMLNode> nodes = xmlptr()->GetNodes("fdm_config/ground_reactions/contact");
   std::cout << "the number of nodes is " << nodes.size() << std::endl;
   for (auto& i : nodes)
   {
       std::cout << "the name is " << i.GetName() << std::endl;
       std::vector <AttributeKV> attributes = i.GetAttributes();
       std::cout << "the number of attributes in the node is " << attributes.size()  << std::endl;
       for (auto& j : attributes)
       {
           //  type and name
           std::cout  << "    " << j.first << " " << j.second << std::endl;
       }
       std::vector<JSBEdit::XMLNode> nodes = i.GetChildren();
       for (auto& k : nodes ) 
       {
           std::vector<JSBEdit::XMLNode> nodes = k.GetChildren();
           std::cout << "   " << k.GetName() << " " << k.GetText()  << std::endl;
           if (nodes.size()>1) 
           {
               for (auto& m : nodes ) 
               {
                   std::cout << m.GetName() << " "  << m.GetText() << std::endl;
               }
           }
       }
   }
#ifdef THIS_IS_AN_EXAMPLE_FROM_THE_XML_FILE
   <contact type="BOGEY" name="NOSE_LG">
   <location unit="IN">
    <x> -299.6 </x>
    <y> 0 </y>
    <z> -72 </z>
   </location>
   <static_friction> 0.8 </static_friction>
   <dynamic_friction> 0.5 </dynamic_friction>
   <rolling_friction> 0.02 </rolling_friction>
   <spring_coeff unit="LBS/FT"> 17250 </spring_coeff>
   <damping_coeff unit="LBS/FT/SEC"> 4250 </damping_coeff>
   <max_steer unit="DEG"> 80 </max_steer>
   <brake_group> NOSE </brake_group>
   <retractable>1</retractable>
  </contact>
#endif
//////////////


    m_Grid.set_row_spacing(10);
    m_Grid.set_column_spacing(10);

    // Contact buttons to open respective dialog popups
    auto buttonContact1 = Gtk::make_managed<Gtk::Button>("Contact 1 NAME at [LOCATION] in COORDINATEUNIT (in BRAKEGROUPUNIT brake group)");
    buttonContact1->signal_clicked().connect([]() {
        auto landingGearDialog1 = new LandingGearSetupDialog();
        landingGearDialog1->show();
    });

    auto buttonContact2 = Gtk::make_managed<Gtk::Button>("Contact 2 NAME at [LOCATION] in COORDINATEUNIT (in BRAKEGROUPUNIT brake group)");
    buttonContact2->signal_clicked().connect([]() {
        auto landingGearDialog2 = new LandingGearSetupDialog();
        landingGearDialog2->show();
    });

    auto buttonContact3 = Gtk::make_managed<Gtk::Button>("Contact 3 NAME at [LOCATION] in COORDINATEUNIT (in BRAKEGROUPUNIT brake group)");
    buttonContact3->signal_clicked().connect([]() {
        auto landingGearDialog3 = new LandingGearSetupDialog();
        landingGearDialog3->show();
    });

    auto buttonContact4 = Gtk::make_managed<Gtk::Button>("Contact 4 NAME at [LOCATION] in COORDINATEUNIT (in BRAKEGROUPUNIT brake group)");
    buttonContact4->signal_clicked().connect([]() {
        auto landingGearDialog4 = new LandingGearSetupDialog();
        landingGearDialog4->show();
    });

    auto buttonContact5 = Gtk::make_managed<Gtk::Button>("Contact 5 NAME at [LOCATION] in COORDINATEUNIT (in BRAKEGROUPUNIT brake group)");
    buttonContact5->signal_clicked().connect([]() {
        auto landingGearDialog5 = new LandingGearSetupDialog();
        landingGearDialog5->show();
    });

    m_Grid.attach(*buttonContact1, 0, 0);
    m_Grid.attach(*buttonContact2, 0, 1);
    m_Grid.attach(*buttonContact3, 0, 2);
    m_Grid.attach(*buttonContact4, 0, 3);
    m_Grid.attach(*buttonContact5, 0, 4);

    // Keep track of rows
    //int row = 1; unused varaible can be uncommented if needed to be used.
}
