#pragma once

#include <cstdint>
#include <string_view>
#include <vector>

namespace arbimath {
class BigInt {
  private:
    /// sign is set if number is negative
    bool sign;
    /// absolute value. least significant bytes first
    std::vector<uint64_t> magnitude;

  public:
    /// Default constructor. Create a BigInt with value 0
    BigInt();
    /// Construct from 64_bit int
    explicit BigInt(uint64_t value);
    /// Construct from hex string_view
    explicit BigInt(std::string_view value);
    /// copy constructor
    BigInt(const BigInt& other);
    /// move constructor
    BigInt(BigInt&& other) noexcept;

  private:
    /// Construct from sign and magnitude
    BigInt(bool sign, const std::vector<uint64_t>& magnitude);

  public:
    /// check for equality
    bool operator==(const BigInt& other) const;
    /// check for inequality
    bool operator!=(const BigInt& other) const;

    /// unary minus
    BigInt operator-() const;
    /// unary plus (effectively only copies the number)
    BigInt operator+() const;

    /// binary plus
    friend BigInt operator+(const BigInt& lhs, const BigInt& rhs);
    /// binary plus
    friend BigInt operator-(const BigInt& lhs, const BigInt& rhs);
};
} // namespace arbimath
