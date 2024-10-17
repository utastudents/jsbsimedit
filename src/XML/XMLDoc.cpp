#include <XML/XMLDoc.hpp>



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
    // Glib::Markup needs a context to parse
    //Glib::Markup::ParseContext parseContext{*m_pParser};
    //try {
    //    parseContext.parse(m_xmlData);
    //} catch (Glib::MarkupError& error) 
    //{
    //    std::cerr << "Error: " << error.what() << "\n";
    //   return false;
    //}
    //return true;

    pugi::xml_parse_result result = doc.load_string(m_xmlData.data());
    return result;
}

void JSBEdit::XMLDoc::CreateMetrics()
{
    m_pMetrics = new JSBEdit::Metrics();

    // get the metrics node
    pugi::xpath_node metricData = doc.select_node("/fdm_config/metrics");

    if (!metricData)
    {
        return;
    }

    // alright now get the data
    pugi::xpath_node wingAreaNode = doc.select_node("/fdm_config/metrics/wingarea");
    pugi::xpath_node wingSpanNode = doc.select_node("/fdm_config/metrics/wingspan");
    pugi::xpath_node wingIncidenceNode = doc.select_node("/fdm_config/metrics/wing_incidence");
    pugi::xpath_node chordNode = doc.select_node("/fdm_config/metrics/chord");
    pugi::xpath_node hTailArmNode = doc.select_node("/fdm_config/metrics/htailarea");
    pugi::xpath_node hTailAreaNode = doc.select_node("/fdm_config/metrics/htailarm");
    pugi::xpath_node vTailArmNode = doc.select_node("/fdm_config/metrics/vtailarea");
    pugi::xpath_node vTailAreaNode = doc.select_node("/fdm_config/metrics/vtailarm");
    pugi::xpath_node_set LocationNodeSet = doc.select_nodes("/fdm_config/metrics/location");

    // wingarea
    m_pMetrics->wingarea.GetWingArea() = wingAreaNode.node().text().as_double();
    m_pMetrics->wingarea.GetUnit() = wingAreaNode.node().attribute("unit").as_string();

    // wingspan
    m_pMetrics->wingspan.GetWingSpan() = wingSpanNode.node().text().as_double();
    m_pMetrics->wingspan.GetUnit() = wingSpanNode.node().attribute("unit").as_string();

    // wing Incidence
    m_pMetrics->wingincidence.GetWindIncidence() = wingIncidenceNode.node().text().as_double();
    m_pMetrics->wingincidence.GetUnit() = wingIncidenceNode.node().attribute("unit").as_string();

    // chord
    m_pMetrics->chord.GetChordLength() = chordNode.node().text().as_double();
    m_pMetrics->chord.GetUnit() = chordNode.node().attribute("unit").as_string();

    // hTailArmNode
    m_pMetrics->htailarm.GetHTailArm() = hTailArmNode.node().text().as_double();
    m_pMetrics->htailarm.GetUnit() = hTailArmNode.node().attribute("unit").as_string();

    // hTailAreaNode
    m_pMetrics->htailarea.GetHTailArea() = hTailAreaNode.node().text().as_double();
    m_pMetrics->htailarea.GetUnit() = hTailAreaNode.node().attribute("unit").as_string();

    // vTailArmNode
    m_pMetrics->vtailarm.GetVTailArm() = vTailArmNode.node().text().as_double();
    m_pMetrics->vtailarm.GetUnit() = vTailArmNode.node().attribute("unit").as_string();

    // vTailAreaNode
    m_pMetrics->vtailarea.GetVTailArea() = vTailAreaNode.node().text().as_double();
    m_pMetrics->wingarea.GetUnit() = vTailAreaNode.node().attribute("unit").as_string();

    for (pugi::xpath_node node : LocationNodeSet)
    {
        double x = node.node().child("x").text().as_double();
        double y = node.node().child("y").text().as_double();
        double z = node.node().child("z").text().as_double();
        Glib::ustring name = node.node().name();
        Glib::ustring unit = node.node().attribute("unit").as_string();


        
        m_pMetrics->locations.push_back({x, y, z, name, unit});
    }
}

JSBEdit::XMLDoc::XMLDoc()
{
    m_pParser = new JSBEdit::XMLParser();
}

JSBEdit::XMLDoc::~XMLDoc()
{
    delete m_pParser;
}

void JSBEdit::XMLDoc::LoadFileAndParse(const std::filesystem::path& path)
{
    GetFileContexts(path);
    ParseData();
    CreateMetrics();
}