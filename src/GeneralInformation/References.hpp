#pragma once

#include <string>

class References {
private:
    std::string refID;
    std::string author;
    std::string title;
    std::string date;

public:
    References();

    void setRefID(const std::string& refID);
    std::string getRefID() const;

    void setAuthor(const std::string& author);
    std::string getAuthor() const;

    void setTitle(const std::string& title);
    std::string getTitle() const;

    void setDate(const std::string& date);
    std::string getDate() const;
};