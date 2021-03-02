#pragma once

#include <Curve.hpp>

namespace curves {

class Ellipse : public Curve {
private:
  const double m_radius_x;
  const double m_radius_y;

public:
  Ellipse(const double, const double);

  Ellipse(const Ellipse &) = delete;
  Ellipse(Ellipse &&) = delete;

  Ellipse &operator=(const Ellipse &) = delete;
  Ellipse &operator=(Ellipse &&) = delete;

  Vector3 get_point(const double) const noexcept override;

  Vector3 get_first_derivative(const double) const noexcept override;

  std::string_view get_name() const noexcept override;

  double get_radius_x() const noexcept;
  double get_radius_y() const noexcept;
};

} // namespace curves