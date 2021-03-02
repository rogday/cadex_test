#include <iostream>
#include <iomanip>

#include <vector>
#include <string_view>
#include <cmath>
#include <random>
#include <algorithm>
#include <numeric>
#include <functional>
#include <memory>

#include <Curves.hpp>
#include <tbb/tbb.h>

std::vector<std::shared_ptr<curves::Curve>> gen_curves(const std::size_t N) {
  std::mt19937 gen(std::random_device{}());

  std::uniform_real_distribution<double> dist(0.1, 5.);
  std::uniform_int_distribution<std::uint16_t> curve(0, 2);

  std::vector<std::shared_ptr<curves::Curve>> curves;
  curves.reserve(N);

  auto generator = [&](auto &&f) -> std::shared_ptr<curves::Curve> {
    switch (f()) {
    case 0:
      return std::make_shared<curves::Circle>(dist(gen));
    case 1:
      return std::make_shared<curves::Ellipse>(dist(gen), dist(gen));
    default:
      return std::make_shared<curves::Helix>(dist(gen), dist(gen));
    }
  };

  std::generate_n(std::back_inserter(curves), 3,
                  std::bind(generator, [i = 0]() mutable { return i++; }));

  std::generate_n(std::back_inserter(curves), N - 3,
                  std::bind(generator, [&]() { return curve(gen); }));

  return curves;
}

std::vector<std::shared_ptr<curves::Circle>>
get_circles(const std::vector<std::shared_ptr<curves::Curve>> &curves) {
  std::vector<std::shared_ptr<curves::Circle>> circles;
  circles.reserve(std::size(curves));

  // there is no transform_if sadly
  for (const auto &curve : curves) {
    if (auto &&circle = std::dynamic_pointer_cast<curves::Circle>(curve);
        circle) {
      circles.emplace_back(circle);
    }
  }

  std::sort(std::begin(circles), std::end(circles),
            [](const auto &lhs, const auto &rhs) {
              return lhs->get_radius() < rhs->get_radius();
            });

  return circles;
}

template <typename T>
void print_curves(std::string_view title,
                  const std::vector<std::shared_ptr<T>> &curves,
                  const double t) {
  std::cout << title << std::endl;

  for (const auto &curve : curves) {
    std::cout << std::left << std::setw(14) << curve->get_name()
              << " point = " << curve->get_point(t)
              << "; derivative = " << curve->get_first_derivative(t)
              << std::endl;
  }

  std::cout << std::endl;
}

class Adder {
  const std::vector<std::shared_ptr<curves::Circle>> &m_data;
  double m_sum;

public:
  Adder(const std::vector<std::shared_ptr<curves::Circle>> &data)
      : m_data(data), m_sum(0.) {}

  Adder(Adder &x, tbb::split) : Adder(x.m_data) {}

  double get_sum() const noexcept { return m_sum; }

  void join(const Adder &y) { m_sum += y.m_sum; }

  void operator()(const tbb::blocked_range<size_t> &r) {
    for (size_t i = r.begin(); i != r.end(); ++i)
      m_sum += m_data[i]->get_radius();
  }
};

int main() {
  constexpr std::size_t N = 100;

  const std::vector<std::shared_ptr<curves::Curve>> curves = gen_curves(N);
  const std::vector<std::shared_ptr<curves::Circle>> circles =
      get_circles(curves);

  constexpr double t = M_PI_4;

  print_curves("All curves", curves, t);
  print_curves("Sorted circles", circles, t);

  Adder adder(circles);
  tbb::parallel_reduce(tbb::blocked_range<size_t>(0, std::size(circles)),
                       adder);
  std::cout << "Circles radius_sum: " << adder.get_sum() << std::endl;

  return 0;
}