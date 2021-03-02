#include <iomanip>
#include <Vector3.hpp>

namespace curves {

Vector3 &Vector3::with_x(const double x) noexcept {
  m_x = x;
  return *this;
}

Vector3 &Vector3::with_y(const double y) noexcept {
  m_y = y;
  return *this;
}

Vector3 &Vector3::with_z(const double z) noexcept {
  m_z = z;
  return *this;
}

std::ostream &operator<<(std::ostream &s, const Vector3 &p) {
  return s << "( " << std::setw(9) << p.m_x << ", " << std::setw(9) << p.m_y
           << ", " << std::setw(9) << p.m_z << ")";
}

} // namespace curves