#pragma once

#include <cstdint>
#include <vector>
#include <string_view>

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

    /// check for equality
    bool operator==(const BigInt& other) const;
    /// check for inequality
    bool operator!=(const BigInt& other) const;

  private:
    /// check if magnitude has leading zeros
    bool hasLeadingZeros() const;
    /// remove leading zeros from magnitude
    void removeLeadingZeros();
};
} // namespace arbimath
