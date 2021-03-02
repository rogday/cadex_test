#pragma once

#include <iostream>

namespace curves {

class Vector3 {
private:
  double m_x;
  double m_y;
  double m_z;

public:
  Vector3(const double x, const double y, const double z)
      : m_x(x), m_y(y), m_z(z){};

  Vector3(const Vector3 &) = default;
  Vector3(Vector3 &&) = default;

  Vector3 &operator=(const Vector3 &) = default;
  Vector3 &operator=(Vector3 &&) = default;

  Vector3 &with_x(const double) noexcept;
  Vector3 &with_y(const double) noexcept;
  Vector3 &with_z(const double) noexcept;

  friend std::ostream &operator<<(std::ostream &, const Vector3 &);
};
} // namespace curves