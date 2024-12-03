#include <XML/XMLDoc.hpp>
#include "XMLDoc.hpp"



void JSBEdit::XMLDoc::GetFileContexts(const std::filesystem::path& path)
{
    if(!std::filesystem::exists(path))
    {
        std::cerr << "XMLDoc Error: GetFileContexts path does not exist. Path: " << path << "\n";
    }

    // use a stream because they are fast enough, and I don't want to write alot of code
    std::ifstream inFileStream{path};
    std::stringstream buffer;
    buffer << inFileStream.rdbuf();

    m_xmlData = buffer.str();
}

bool JSBEdit::XMLDoc::ParseData()
{
    pugi::xml_parse_result result = doc.load_string(m_xmlData.data());
    return result;
}

// This was left as a reference to other groups 
//void JSBEdit::XMLDoc::CreateMetrics()
//{

    // // get the metrics node
    // pugi::xpath_node metricData = doc.select_node("/fdm_config/metrics");

    // if (!metricData)
    // {
    //     return;
    // }

    // // alright now get the data
    // pugi::xpath_node wingAreaNode = doc.select_node("/fdm_config/metrics/wingarea");
    // pugi::xpath_node wingSpanNode = doc.select_node("/fdm_config/metrics/wingspan");
    // pugi::xpath_node wingIncidenceNode = doc.select_node("/fdm_config/metrics/wing_incidence");
    // pugi::xpath_node chordNode = doc.select_node("/fdm_config/metrics/chord");
    // pugi::xpath_node hTailArmNode = doc.select_node("/fdm_config/metrics/htailarea");
    // pugi::xpath_node hTailAreaNode = doc.select_node("/fdm_config/metrics/htailarm");
    // pugi::xpath_node vTailArmNode = doc.select_node("/fdm_config/metrics/vtailarea");
    // pugi::xpath_node vTailAreaNode = doc.select_node("/fdm_config/metrics/vtailarm");
    // pugi::xpath_node_set LocationNodeSet = doc.select_nodes("/fdm_config/metrics/location");

    // // wingarea
    // auto areanodevalue = wingAreaNode.node().text().as_double();
    // auto areanodeunit = wingAreaNode.node().attribute("unit").as_string();

    // wingAreaNode.node().text().set("400");
    // wingAreaNode.node().attribute("unit").set_value("FT22");


    // // wingspan
    // auto wingspanvalue = wingSpanNode.node().text().as_double();
    // auto wingspanunit = wingSpanNode.node().attribute("unit").as_string();

    // // wing Incidence
    // auto wingIncidencevalue = wingIncidenceNode.node().text().as_double();
    // auto wingIncidenceunit = wingIncidenceNode.node().attribute("unit").as_string();

    // // chord
    // auto chordvalue = chordNode.node().text().as_double();
    // auto chordunit = chordNode.node().attribute("unit").as_string();

    // // hTailArmNode
    // auto hTailArmNodevalue = hTailArmNode.node().text().as_double();
    // auto hTailArmNodeunit = hTailArmNode.node().attribute("unit").as_string();

    // // hTailAreaNode
    // auto hTailAreaNodevalue = hTailAreaNode.node().text().as_double();
    // auto hTailAreaNodeUnit = hTailAreaNode.node().attribute("unit").as_string();

    // // vTailArmNode
    // auto vTailArmNodevalue = vTailArmNode.node().text().as_double();
    // auto vTailArmNodeunit = vTailArmNode.node().attribute("unit").as_string();

    // // vTailAreaNode
    // auto vTailAreaNodevalue = vTailAreaNode.node().text().as_double();
    // auto vTailAreaNodeunit = vTailAreaNode.node().attribute("unit").as_string();

    // for (pugi::xpath_node node : LocationNodeSet)
    // {
    //     double x = node.node().child("x").text().as_double();
    //     double y = node.node().child("y").text().as_double();
    //     double z = node.node().child("z").text().as_double();
    //     Glib::ustring name = node.node().name();
    //     Glib::ustring unit = node.node().attribute("unit").as_string();
    // }
    // metricData.node().print(std::cout);
//}

JSBEdit::XMLDoc::XMLDoc()
{
}

JSBEdit::XMLDoc::~XMLDoc()
{
}

void JSBEdit::XMLDoc::LoadFileAndParse(const std::filesystem::path& path)
{
    m_filePath = path;
    GetFileContexts(path);
    ParseData();
}
void JSBEdit::XMLDoc::LoadStringAndParse(const std::string &xmlString)
{
    m_xmlData = xmlString;
    ParseData();
}

JSBEdit::XMLNode JSBEdit::XMLDoc::GetNode(std::string search)
{  
    // empty returns the root as the node
    if(search.empty())
    {
        return XMLNode(doc);
    }

    pugi::xml_node node = doc.select_node(search.c_str()).node();
    return JSBEdit::XMLNode(node);
}

std::vector<JSBEdit::XMLNode> JSBEdit::XMLDoc::GetNodes(std::string search)
{
    std::vector<JSBEdit::XMLNode> nodes;
    if(search.empty())
    {
        return nodes;
    }

    pugi::xpath_node_set xpathSet = doc.select_nodes(search.c_str());
    if(xpathSet.empty())
    {
        // log here
        return nodes;
    }

    for(auto & node: xpathSet)
    {
        if(node.node())
        {
            nodes.push_back(node.node());
        }
    }
    return nodes;
}

bool JSBEdit::XMLDoc::SaveToFile(const std::filesystem::path &path)
{
    if(std::filesystem::exists(path.parent_path()))
    {
        return doc.save_file(path.c_str());
    }
    return false;   
}

//prints the nodes out to stdout
void JSBEdit::XMLDoc::Print()
{
    doc.print(std::cout);
}

// Definition of GetFilePath method
std::filesystem::path JSBEdit::XMLDoc::GetFilePath() const
{
    return m_filePath;
}
