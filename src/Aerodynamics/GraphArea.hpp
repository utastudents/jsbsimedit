#pragma once

#include <gtkmm.h>
#include <vector>
#include <utility> // for std::pair

class GraphArea : public Gtk::DrawingArea {
public:
    GraphArea(const std::vector<std::pair<double, double>>& data_points);

protected:
    // Override the draw method
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);

private:
    std::vector<std::pair<double, double>> points;

    void draw_axes(const Cairo::RefPtr<Cairo::Context>& cr, double width, double height);
    void draw_graph(const Cairo::RefPtr<Cairo::Context>& cr, double width, double height);
};
