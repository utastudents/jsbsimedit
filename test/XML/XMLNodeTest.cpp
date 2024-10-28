#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_session.hpp>
#include <pugixml.hpp>

#include <iostream>
#include <string>
#include <XML/XMLDoc.hpp>
#include <XML/XMLNode.hpp>

TEST_CASE("Testing GetAttributes")
{
    JSBEdit::XMLDoc doc;
    doc.LoadFileAndParse({"../../../../test/TestFiles/book.xml"});
    JSBEdit::XMLNode node = doc.GetNode("catalog/testattributes");

    std::vector <AttributeKV> attributes = node.GetAttributes();
    REQUIRE(attributes.size() == 4);
    // the vector should contain the elements id="bk100" test="yes/no" placement="yeah" random="10"
    // id
    REQUIRE(attributes[0].first == "id");
    REQUIRE(attributes[0].second == "bk100");
    // test
    REQUIRE(attributes[1].first == "test");
    REQUIRE(attributes[1].second == "yes/no");
    // placement
    REQUIRE(attributes[2].first == "placement");
    REQUIRE(attributes[2].second == "yeah");
    // random
    REQUIRE(attributes[3].first == "random");
    REQUIRE(attributes[3].second == "10");

}

TEST_CASE("Testing GetAttribute")
{
    JSBEdit::XMLDoc doc;
    doc.LoadFileAndParse({"../../../../test/TestFiles/book.xml"});
    JSBEdit::XMLNode node = doc.GetNode("catalog/testattributes");

    auto attribute = node.GetAttribute("id");

    REQUIRE(attribute.first == "id");
    REQUIRE(attribute.second == "bk100");
}

TEST_CASE("Testing AddAttributes")
{
    JSBEdit::XMLDoc doc;
    doc.LoadFileAndParse({"../../../../test/TestFiles/book.xml"});
    JSBEdit::XMLNode node = doc.GetNode("catalog/testattributes");

    std::vector<AttributeKV> newAttributes;
    newAttributes.push_back({"air", "apple"});
    newAttributes.push_back({"tractor", "deer"});
    newAttributes.push_back({"road", "concrete"});

    node.AddAttributes(newAttributes);

    // get all the attributes
    std::vector <AttributeKV> attributes = node.GetAttributes();

    REQUIRE(attributes.size() == 7);

    // the vector should contain the elements id="bk100" test="yes/no" placement="yeah" random="10"
    // air="apple" tractor="deer" road="concrete"
    // id
    REQUIRE(attributes[0].first == "id");
    REQUIRE(attributes[0].second == "bk100");
    // test
    REQUIRE(attributes[1].first == "test");
    REQUIRE(attributes[1].second == "yes/no");
    // placement
    REQUIRE(attributes[2].first == "placement");
    REQUIRE(attributes[2].second == "yeah");
    // random
    REQUIRE(attributes[3].first == "random");
    REQUIRE(attributes[3].second == "10");
    // air
    REQUIRE(attributes[4].first == "air");
    REQUIRE(attributes[4].second == "apple");
    // tractor
    REQUIRE(attributes[5].first == "tractor");
    REQUIRE(attributes[5].second == "deer");
    //road
    REQUIRE(attributes[6].first == "road");
    REQUIRE(attributes[6].second == "concrete");
}

TEST_CASE("Testing AddAttribute")
{
    JSBEdit::XMLDoc doc;
    doc.LoadFileAndParse({"../../../../test/TestFiles/book.xml"});
    JSBEdit::XMLNode node = doc.GetNode("catalog/testattributes");

    AttributeKV newAttributes{"air", "apple"};

    node.AddAttribute(newAttributes);

    // get all the attributes
    std::vector <AttributeKV> attributes = node.GetAttributes();

    REQUIRE(attributes.size() == 5);

    // the vector should contain the elements id="bk100" test="yes/no" placement="yeah" random="10"
    // air="apple" tractor="deer" road="concrete"
    // id
    REQUIRE(attributes[0].first == "id");
    REQUIRE(attributes[0].second == "bk100");
    // test
    REQUIRE(attributes[1].first == "test");
    REQUIRE(attributes[1].second == "yes/no");
    // placement
    REQUIRE(attributes[2].first == "placement");
    REQUIRE(attributes[2].second == "yeah");
    // random
    REQUIRE(attributes[3].first == "random");
    REQUIRE(attributes[3].second == "10");
    // air
    REQUIRE(attributes[4].first == "air");
    REQUIRE(attributes[4].second == "apple");

}

TEST_CASE("Testing SetAttributes")
{
    JSBEdit::XMLDoc doc;
    doc.LoadFileAndParse({"../../../../test/TestFiles/book.xml"});
    JSBEdit::XMLNode node = doc.GetNode("catalog/testattributes");

    std::vector<AttributeKV> newAttributes;
    newAttributes.push_back({"air", "apple"});
    newAttributes.push_back({"tractor", "deer"});
    newAttributes.push_back({"road", "concrete"});

    // SetAttributes removes existing Attributes, then adds the new ones
    node.SetAttributes(newAttributes);

    // get all the attributes
    std::vector <AttributeKV> attributes = node.GetAttributes();

    REQUIRE(attributes.size() == 3);
        // air
    REQUIRE(attributes[0].first == "air");
    REQUIRE(attributes[0].second == "apple");
    // tractor
    REQUIRE(attributes[1].first == "tractor");
    REQUIRE(attributes[1].second == "deer");
    //road
    REQUIRE(attributes[2].first == "road");
    REQUIRE(attributes[2].second == "concrete");
}

TEST_CASE("Testing SetAttribute")
{
    JSBEdit::XMLDoc doc;
    doc.LoadFileAndParse({"../../../../test/TestFiles/book.xml"});
    JSBEdit::XMLNode node = doc.GetNode("catalog/testattributes");

    AttributeKV newAttributes{"air", "apple"};

    node.SetAttribute(newAttributes);

    // get all the attributes
    std::vector <AttributeKV> attributes = node.GetAttributes();

    REQUIRE(attributes.size() == 1);

    // the vector should contain the elements air="apple"
    // air
    REQUIRE(attributes[0].first == "air");
    REQUIRE(attributes[0].second == "apple");

}

TEST_CASE("Testing RemoveAttributes")
{
    JSBEdit::XMLDoc doc;
    doc.LoadFileAndParse({"../../../../test/TestFiles/book.xml"});
    JSBEdit::XMLNode node = doc.GetNode("catalog/testattributes");

    node.RemoveAttributes();

    // get all the attributes
    std::vector <AttributeKV> attributes = node.GetAttributes();

    REQUIRE(attributes.size() == 0);
}

TEST_CASE("Testing RemoveAttribute")
{
    JSBEdit::XMLDoc doc;
    doc.LoadFileAndParse({"../../../../test/TestFiles/book.xml"});
    JSBEdit::XMLNode node = doc.GetNode("catalog/testattributes");

    node.RemoveAttribute("id");

    // get all the attributes
    std::vector <AttributeKV> attributes = node.GetAttributes();

    REQUIRE(attributes.size() == 3);

    // the vector should contain the elements test="yes/no" placement="yeah" random="10"
    // test
    REQUIRE(attributes[0].first == "test");
    REQUIRE(attributes[0].second == "yes/no");
    // placement
    REQUIRE(attributes[1].first == "placement");
    REQUIRE(attributes[1].second == "yeah");
    // random
    REQUIRE(attributes[2].first == "random");
    REQUIRE(attributes[2].second == "10");
}

TEST_CASE("Testing GetText")
{
    JSBEdit::XMLDoc doc;
    doc.LoadFileAndParse({"../../../../test/TestFiles/book.xml"});
    JSBEdit::XMLNode node = doc.GetNode("catalog/testattributes");

    REQUIRE(node.GetText() == "Text Data");
}

TEST_CASE("Testing SetText")
{
    JSBEdit::XMLDoc doc;
    doc.LoadFileAndParse({"../../../../test/TestFiles/book.xml"});
    JSBEdit::XMLNode node = doc.GetNode("catalog/testattributes");

    node.SetText("Set Text Data");

    REQUIRE(node.GetText() == "Set Text Data");
}

TEST_CASE("Testing GetName")
{
    JSBEdit::XMLDoc doc;
    doc.LoadFileAndParse({"../../../../test/TestFiles/book.xml"});
    JSBEdit::XMLNode node = doc.GetNode("catalog/testattributes");

    REQUIRE(node.GetName() == "testattributes");
}

TEST_CASE("Testing SetName")
{
    JSBEdit::XMLDoc doc;
    doc.LoadFileAndParse({"../../../../test/TestFiles/book.xml"});
    JSBEdit::XMLNode node = doc.GetNode("catalog/testattributes");

    node.SetName("newtestattributes");

    REQUIRE(node.GetName() == "newtestattributes");
}

TEST_CASE("Testing AddChild")
{
    JSBEdit::XMLDoc doc;
    doc.LoadFileAndParse({"../../../../test/TestFiles/book.xml"});
    JSBEdit::XMLNode node = doc.GetNode("catalog/testattributes");

    JSBEdit::XMLNode childNode(doc);
    childNode.SetName("child1");
    childNode.SetText("child1 data");

    node.AddChild(childNode);

    std::vector<JSBEdit::XMLNode> nodes = node.GetChildren();
    // Testing for added node
    REQUIRE(nodes.size() == 2);
    // pcdata, plain / parsed character data
    REQUIRE(nodes[0].GetName() == "");
    REQUIRE(nodes[0].GetText() == "Text Data");
    // now test name
    REQUIRE(nodes[1].GetName() == "child1");
    // test data
    REQUIRE(nodes[1].GetText() == "child1 data");

}

TEST_CASE("Testing AddChildren")
{
    JSBEdit::XMLDoc doc;
    doc.LoadFileAndParse({"../../../../test/TestFiles/book.xml"});
    JSBEdit::XMLNode node = doc.GetNode("catalog/testattributes");
    
    std::vector<JSBEdit::XMLNode> children;
    std::vector<AttributeKV> attributes;
    children.push_back(JSBEdit::XMLNode{doc, "child1", attributes, "child1 data"});
    children.push_back(JSBEdit::XMLNode{doc, "child2", attributes, "child2 data"});
    children.push_back(JSBEdit::XMLNode{doc, "child3", attributes, "child3 data"});
    children.push_back(JSBEdit::XMLNode{doc, "child4", attributes, "child4 data"});

    node.AddChildren(children);

    std::vector<JSBEdit::XMLNode> nodes = node.GetChildren();
    // Testing for added node
    REQUIRE(nodes.size() == 5);
    // pcdata, plain / parsed character data
    REQUIRE(nodes[0].GetName() == "");
    REQUIRE(nodes[0].GetText() == "Text Data");
    // now test name
    REQUIRE(nodes[1].GetName() == "child1");
    // test data
    REQUIRE(nodes[1].GetText() == "child1 data");
    // now test name
    REQUIRE(nodes[2].GetName() == "child2");
    // test data
    REQUIRE(nodes[2].GetText() == "child2 data");
    // now test name
    REQUIRE(nodes[3].GetName() == "child3");
    // test data
    REQUIRE(nodes[3].GetText() == "child3 data");
    // now test name
    REQUIRE(nodes[4].GetName() == "child4");
    // test data
    REQUIRE(nodes[4].GetText() == "child4 data");

}

TEST_CASE("Testing FindChild")
{
    JSBEdit::XMLDoc doc;
    doc.LoadFileAndParse({"../../../../test/TestFiles/book.xml"});
    JSBEdit::XMLNode node = doc.GetNode("catalog");

    JSBEdit::XMLNode child = node.FindChild("book");
    REQUIRE(child.GetName() == "book");
    REQUIRE(child.GetAttribute("id").second == "bk101");

    // test with a bad name
    child = node.FindChild("null");
    REQUIRE(!child);
}

TEST_CASE("Testing GetChild")
{
    JSBEdit::XMLDoc doc;
    doc.LoadFileAndParse({"../../../../test/TestFiles/book.xml"});
    JSBEdit::XMLNode node = doc.GetNode("catalog/testattributes");

    JSBEdit::XMLNode child = node.GetChild(0);
    REQUIRE(child.GetName() == "");
    REQUIRE(child.GetText() == "Text Data");

    // test with a large index
    child = node.GetChild(INT32_MAX);
    REQUIRE(!child);
}

TEST_CASE("Testing GetChildren")
{
    JSBEdit::XMLDoc doc;
    doc.LoadFileAndParse({"../../../../test/TestFiles/book.xml"});
    JSBEdit::XMLNode bookNode = doc.GetNodes("catalog/book")[0];

    std::vector<JSBEdit::XMLNode> children = bookNode.GetChildren();

    REQUIRE(children.size() == 6);

    REQUIRE(children[0].GetName() == "author");
    REQUIRE(children[0].GetText() == "Gambardella, Matthew");

    REQUIRE(children[1].GetName() == "title");
    REQUIRE(children[1].GetText() == "XML Developer's Guide");

    REQUIRE(children[2].GetName() == "genre");
    REQUIRE(children[2].GetText() == "Computer");

    REQUIRE(children[3].GetName() == "price");
    REQUIRE(children[3].GetText() == "44.95");

    REQUIRE(children[4].GetName() == "publish_date");
    REQUIRE(children[4].GetText() == "2000-10-01");

    REQUIRE(children[5].GetName() == "description");
    REQUIRE(children[5].GetText() == "An in-depth look at creating applications with XML.");

}

TEST_CASE("Testing RemoveChild index")
{
    JSBEdit::XMLDoc doc;
    doc.LoadFileAndParse({"../../../../test/TestFiles/book.xml"});
    JSBEdit::XMLNode node = doc.GetNode("catalog");

    auto children = node.GetChildren();

    REQUIRE(children.size() == 13);

    node.RemoveChild(1);
    
    children = node.GetChildren();

    REQUIRE(children.size() == 12);

    REQUIRE(children[0].GetName() == "testattributes");
    REQUIRE(children[0].GetAttributes()[0].second == "bk100");

    REQUIRE(children[1].GetName() == "book");
    REQUIRE(children[1].GetAttributes()[0].second == "bk102");

    REQUIRE(children[2].GetName() == "book");
    REQUIRE(children[2].GetAttributes()[0].second == "bk103");

    REQUIRE(children[3].GetName() == "book");
    REQUIRE(children[3].GetAttributes()[0].second == "bk104");

    REQUIRE(children[4].GetName() == "book");
    REQUIRE(children[4].GetAttributes()[0].second == "bk105");

    REQUIRE(children[5].GetName() == "book");
    REQUIRE(children[5].GetAttributes()[0].second == "bk106");

    REQUIRE(children[6].GetName() == "book");
    REQUIRE(children[6].GetAttributes()[0].second == "bk107");

    REQUIRE(children[7].GetName() == "book");
    REQUIRE(children[7].GetAttributes()[0].second == "bk108");

    REQUIRE(children[8].GetName() == "book");
    REQUIRE(children[8].GetAttributes()[0].second == "bk109");

    REQUIRE(children[9].GetName() == "book");
    REQUIRE(children[9].GetAttributes()[0].second == "bk110");

    REQUIRE(children[10].GetName() == "book");
    REQUIRE(children[10].GetAttributes()[0].second == "bk111");

    REQUIRE(children[11].GetName() == "book");
    REQUIRE(children[11].GetAttributes()[0].second == "bk112");

}

TEST_CASE("Testing RemoveChild node")
{
    JSBEdit::XMLDoc doc;
    doc.LoadFileAndParse({"../../../../test/TestFiles/book.xml"});
    JSBEdit::XMLNode node = doc.GetNode("catalog");
    JSBEdit::XMLNode booknode = doc.GetNodes("catalog/book")[0];

    auto children = node.GetChildren();

    REQUIRE(children.size() == 13);

    node.RemoveChild(booknode);
    
    children = node.GetChildren();

    REQUIRE(children.size() == 12);

    REQUIRE(children[0].GetName() == "testattributes");
    REQUIRE(children[0].GetAttributes()[0].second == "bk100");

    REQUIRE(children[1].GetName() == "book");
    REQUIRE(children[1].GetAttributes()[0].second == "bk102");

    REQUIRE(children[2].GetName() == "book");
    REQUIRE(children[2].GetAttributes()[0].second == "bk103");

    REQUIRE(children[3].GetName() == "book");
    REQUIRE(children[3].GetAttributes()[0].second == "bk104");

    REQUIRE(children[4].GetName() == "book");
    REQUIRE(children[4].GetAttributes()[0].second == "bk105");

    REQUIRE(children[5].GetName() == "book");
    REQUIRE(children[5].GetAttributes()[0].second == "bk106");

    REQUIRE(children[6].GetName() == "book");
    REQUIRE(children[6].GetAttributes()[0].second == "bk107");

    REQUIRE(children[7].GetName() == "book");
    REQUIRE(children[7].GetAttributes()[0].second == "bk108");

    REQUIRE(children[8].GetName() == "book");
    REQUIRE(children[8].GetAttributes()[0].second == "bk109");

    REQUIRE(children[9].GetName() == "book");
    REQUIRE(children[9].GetAttributes()[0].second == "bk110");

    REQUIRE(children[10].GetName() == "book");
    REQUIRE(children[10].GetAttributes()[0].second == "bk111");

    REQUIRE(children[11].GetName() == "book");
    REQUIRE(children[11].GetAttributes()[0].second == "bk112");
}

TEST_CASE("Testing RemoveChildren")
{
    JSBEdit::XMLDoc doc;
    doc.LoadFileAndParse({"../../../../test/TestFiles/book.xml"});
    JSBEdit::XMLNode node = doc.GetNode("catalog");

    auto children = node.GetChildren();

    REQUIRE(children.size() == 13);

    node.RemoveChildren();
    
    children = node.GetChildren();

    REQUIRE(children.size() == 0);
}

TEST_CASE("Testing GetParent")
{
    JSBEdit::XMLDoc doc;
    doc.LoadFileAndParse({"../../../../test/TestFiles/book.xml"});
    JSBEdit::XMLNode node = doc.GetNode("catalog/testattributes");

    JSBEdit::XMLNode parent = node.GetParent();

    REQUIRE(parent.GetName() == "catalog");
}

TEST_CASE("Testing IsMixedContent")
{
    JSBEdit::XMLDoc doc;
    doc.LoadFileAndParse({"../../../../test/TestFiles/book.xml"});
    JSBEdit::XMLNode node = doc.GetNode("catalog/testattributes");

    REQUIRE(node.IsMixedContent() == false);

    JSBEdit::XMLNode childNode(doc);
    childNode.SetName("child1");
    childNode.SetText("child1 data");

    node.AddChild(childNode);

    REQUIRE(node.IsMixedContent() == true);
}

TEST_CASE("Testing operator bool")
{
    JSBEdit::XMLDoc doc;
    doc.LoadFileAndParse({"../../../../test/TestFiles/book.xml"});
    JSBEdit::XMLNode node = doc.GetNode("catalog/testattributes");

    JSBEdit::XMLNode badNode{pugi::xml_node()};

    // bad node is bad basic it is basically null
    REQUIRE(!badNode);
    // node is good because it is not null and contains values
    REQUIRE(node);
}

TEST_CASE("Testing operator[]")
{
    JSBEdit::XMLDoc doc;
    doc.LoadFileAndParse({"../../../../test/TestFiles/book.xml"});
    JSBEdit::XMLNode node = doc.GetNode("catalog/testattributes");

    JSBEdit::XMLNode child = node[0];
    REQUIRE(child);
    REQUIRE(child.GetName() == "");
    REQUIRE(child.GetText() == "Text Data");
}

TEST_CASE("Testing Parser Constructor")
{
    JSBEdit::XMLDoc doc;
    JSBEdit::XMLNode parserNode{doc, "<parsertest id=\"en\">tested on macbook air</parsertest>"};

    REQUIRE(parserNode);
    REQUIRE(parserNode.GetName() == "parsertest");
    REQUIRE(parserNode.GetText() == "tested on macbook air");

    JSBEdit::XMLNode parserNodeBad{doc, "<parsertest id=\"en\">tested on macbook air"};
    REQUIRE(!parserNodeBad);
}

TEST_CASE("Testing xml_node Constructor")
{
    JSBEdit::XMLDoc doc;
    doc.LoadFileAndParse({"../../../../test/TestFiles/book.xml"});
    pugi::xml_node pugiNode = doc.GetPugiDoc().select_node("catalog/testattributes").node();
    JSBEdit::XMLNode node{pugiNode};

    REQUIRE(node);
    REQUIRE(node.GetName() == "testattributes");
    REQUIRE(node.GetText() == "Text Data");

    // testing bad nodes
    JSBEdit::XMLNode nodeBad{pugi::xml_node()};
    REQUIRE(!nodeBad);
}

TEST_CASE("Testing name attributes text Constructor")
{
    JSBEdit::XMLDoc doc;

    std::string name{"testattributes"};
    std::vector<AttributeKV> attributes;
    attributes.push_back(AttributeKV{"id", "bk100"});
    attributes.push_back(AttributeKV{"test", "yes/no"});
    attributes.push_back(AttributeKV{"placement", "yeah"});
    attributes.push_back(AttributeKV{"random", "10"});
    std::string text{"Text Data"};

    JSBEdit::XMLNode node{doc, name, attributes, text};

    REQUIRE(node);
    REQUIRE(node.GetName() == "testattributes");
    REQUIRE(node.GetText() == "Text Data");

    // attributes
    REQUIRE(attributes.size() == 4);
    // the vector should contain the elements id="bk100" test="yes/no" placement="yeah" random="10"
    // id
    REQUIRE(attributes[0].first == "id");
    REQUIRE(attributes[0].second == "bk100");
    // test
    REQUIRE(attributes[1].first == "test");
    REQUIRE(attributes[1].second == "yes/no");
    // placement
    REQUIRE(attributes[2].first == "placement");
    REQUIRE(attributes[2].second == "yeah");
    // random
    REQUIRE(attributes[3].first == "random");
    REQUIRE(attributes[3].second == "10");
}