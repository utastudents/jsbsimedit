#include <XML/XMLWriter.hpp>

JSBEdit::XMLWriter::XMLWriter([[maybe_unused]] JSBEdit::XMLDoc& doc) {

}
JSBEdit::XMLWriter::~XMLWriter() {

}
JSBEdit::XMLDoc JSBEdit::XMLWriter::Write([[maybe_unused]] const std::filesystem::path& path) {
    return JSBEdit::XMLDoc();
}
