#include <cmath>

#include <Ellipse.hpp>

namespace curves {

Ellipse::Ellipse(const double radius_x, const double radius_y)
    : m_radius_x(radius_x), m_radius_y(radius_y) {
  if (std::min(m_radius_x, m_radius_y) < 0.) {
    throw std::runtime_error("Negative radius is not allowed.");
  }
}

Vector3 Ellipse::get_point(const double t) const noexcept {
  return Vector3(std::cos(t) * get_radius_x(), std::sin(t) * get_radius_y(),
                 0.);
}

Vector3 Ellipse::get_first_derivative(const double t) const noexcept {
  return Vector3(-std::sin(t) * get_radius_x(), std::cos(t) * get_radius_y(),
                 0.);
}

std::string_view Ellipse::get_name() const noexcept { return "Ellipse"; }

double Ellipse::get_radius_x() const noexcept { return m_radius_x; }
double Ellipse::get_radius_y() const noexcept { return m_radius_y; }

} // namespace curves