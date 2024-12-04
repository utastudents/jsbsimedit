#include "GraphArea.hpp"
#include <algorithm> // for std::min, std::max

GraphArea::GraphArea(const std::vector<std::pair<double, double>>& data_points)
    : points(data_points) {}

bool GraphArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
    // Get the dimensions of the drawing area
    auto allocation = get_allocation();
    double width = allocation.get_width();
    double height = allocation.get_height();

    // Clear the background
    cr->set_source_rgb(1.0, 1.0, 1.0); // White background
    cr->paint();

    // Draw axes and graph
    draw_axes(cr, width, height);
    draw_graph(cr, width, height);

    return true;
}

void GraphArea::draw_axes(const Cairo::RefPtr<Cairo::Context>& cr, double width, double height) {
    cr->set_source_rgb(0.0, 0.0, 0.0); // Black color for axes
    cr->set_line_width(2.0);

    // Draw x-axis
    cr->move_to(50, height - 50);
    cr->line_to(width - 50, height - 50);

    // Draw y-axis
    cr->move_to(50, height - 50);
    cr->line_to(50, 50);

    cr->stroke();
}

void GraphArea::draw_graph(const Cairo::RefPtr<Cairo::Context>& cr, double width, double height) {
    if (points.empty()) return;

    // Find data range
    double x_min = points[0].first, x_max = points[0].first;
    double y_min = points[0].second, y_max = points[0].second;

    for (const auto& point : points) {
        x_min = std::min(x_min, point.first);
        x_max = std::max(x_max, point.first);
        y_min = std::min(y_min, point.second);
        y_max = std::max(y_max, point.second);
    }

    // Calculate scaling factors
    double x_scale = (width - 100) / (x_max - x_min);
    double y_scale = (height - 100) / (y_max - y_min);

    cr->set_source_rgb(0.0, 0.0, 1.0); // Blue for the graph
    cr->set_line_width(1.5);

    // Draw points
    bool first = true;
    for (const auto& point : points) {
        double x = 50 + (point.first - x_min) * x_scale;
        double y = height - 50 - (point.second - y_min) * y_scale;

        if (first) {
            cr->move_to(x, y);
            first = false;
        } else {
            cr->line_to(x, y);
        }
    }

    cr->stroke();
}
