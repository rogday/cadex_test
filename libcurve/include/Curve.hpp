#pragma once

#include <string_view>

#include <Vector3.hpp>

namespace curves {

class Curve {
public:
  virtual Vector3 get_point(const double) const noexcept = 0;
  virtual Vector3 get_first_derivative(const double) const noexcept = 0;
  virtual std::string_view get_name() const noexcept = 0;

  virtual ~Curve() = default;
};

} // namespace curves