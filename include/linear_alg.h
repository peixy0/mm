#pragma once

#include <array>
#include <gsl/gsl>
#include <initializer_list>
#include <iostream>

namespace linear_alg {
template <std::size_t Rows, std::size_t Columns, typename ValueT = float>
class M {
public:
  static constexpr std::size_t rows = Rows;
  static constexpr std::size_t columns = Columns;

  static M<Rows, Columns, ValueT> Identity() {
    M<Rows, Columns, ValueT> result;
    for (std::size_t i = 0; i < Rows && i < Columns; i++) {
      result(i, i) = 1;
    }
    return result;
  }

  M() : v{0} {}
  ~M() = default;

  M(const M<Rows, Columns, ValueT>&) = default;
  M(M<Rows, Columns, ValueT>&&) = default;
  M<Rows, Columns, ValueT>& operator=(const M<Rows, Columns, ValueT>&) = default;
  M<Rows, Columns, ValueT>& operator=(M<Rows, Columns, ValueT>&&) = default;

  M(std::initializer_list<ValueT> values) {
    std::size_t i = 0;
    for (auto& value : values) {
      if (i >= v.size()) {
        break;
      }
      v[i++] = std::move(value);
    }
  }

  bool operator==(const M<Rows, Columns, ValueT>& m) const {
    return v == m.v;
  }

  ValueT operator()(std::size_t r, std::size_t c = 0) const {
    Expects(r < Rows);
    Expects(c < Columns);
    return v[r * Columns + c];
  }

  ValueT& operator()(std::size_t r, std::size_t c = 0) {
    Expects(r < Rows);
    Expects(c < Columns);
    return v[r * Columns + c];
  }

  M<Columns, Rows, ValueT> T() const {
    M<Columns, Rows, ValueT> result;
    for (std::size_t i = 0; i < Rows; i++) {
      for (std::size_t j = 0; j < Columns; j++) {
        result(j, i) = (*this)(i, j);
      }
    }
    return result;
  }

  template <std::size_t S>
  M<Rows, S, ValueT> operator*(const M<Columns, S, ValueT>& m) const {
    M<Rows, S, ValueT> result;
    for (std::size_t i = 0; i < Rows; i++) {
      for (std::size_t k = 0; k < S; k++) {
        ValueT v{};
        for (std::size_t j = 0; j < Columns; j++) {
          v += (*this)(i, j) * m(j, k);
        }
        result(i, k) = std::move(v);
      }
    }
    return result;
  }

  M<Rows, Columns, ValueT> operator*(const ValueT& s) const {
    M<Rows, Columns, ValueT> result;
    constexpr size_t size = Rows * Columns;
    for (std::size_t i = 0; i < size; i++) {
      result.v[i] = v[i] * s;
    }
    return result;
  }

  M<Rows, Columns, ValueT> operator+(const M<Rows, Columns, ValueT>& m) const {
    M<Rows, Columns, ValueT> result;
    constexpr size_t size = Rows * Columns;
    for (std::size_t i = 0; i < size; i++) {
      result.v[i] = v[i] + m.v[i];
    }
    return result;
  }

  M<Rows, Columns, ValueT> operator+(const ValueT& s) const {
    M<Rows, Columns, ValueT> result;
    constexpr size_t size = Rows * Columns;
    for (std::size_t i = 0; i < size; i++) {
      result.v[i] = v[i] + s;
    }
    return result;
  }

  M<Rows, Columns, ValueT> operator-() const {
    M<Rows, Columns, ValueT> result;
    constexpr size_t size = Rows * Columns;
    for (std::size_t i = 0; i < size; i++) {
      result.v[i] = -v[i];
    }
    return result;
  }

  M<Rows, Columns, ValueT> operator-(const ValueT& s) const {
    return (*this) + (-s);
  }

private:
  std::array<ValueT, Rows * Columns> v;
};

template <std::size_t Rows, std::size_t Columns, typename ValueT>
std::ostream& operator<<(std::ostream& os, const M<Rows, Columns, ValueT>& m) {
  for (std::size_t i = 0; i < Rows; i++) {
    for (std::size_t j = 0; j < Columns; j++) {
      os << m(i, j) << " ";
    }
    os << std::endl;
  }
  return os;
}

template <std::size_t Rows, std::size_t Columns, typename ValueT>
M<Rows, Columns, ValueT> operator*(const ValueT& s, const M<Rows, Columns, ValueT>& m) {
  return m * s;
}

template <std::size_t Rows, std::size_t Columns, typename ValueT>
M<Rows, Columns, ValueT> operator+(const ValueT& s, const M<Rows, Columns, ValueT>& m) {
  return m + s;
}

template <std::size_t Rows, std::size_t Columns, typename ValueT>
M<Rows, Columns, ValueT> operator-(const M<Rows, Columns, ValueT>& lhs, const M<Rows, Columns, ValueT>& rhs) {
  return lhs + (-rhs);
}

template <std::size_t Rows, std::size_t Columns, typename ValueT>
M<Rows, Columns, ValueT> operator-(const ValueT& s, const M<Rows, Columns, ValueT>& m) {
  return s + (-m);
}

template <std::size_t N, typename T = float>
using V = M<N, 1, T>;
}  // namespace linear_alg
