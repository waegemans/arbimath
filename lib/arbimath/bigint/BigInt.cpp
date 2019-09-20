#include "BigInt.hpp"
#include "VectorUtil.hpp"

#include <cassert>
#include <string>
#include <x86intrin.h>

namespace arbimath {

BigInt::BigInt() : sign(false), magnitude({}) {}

BigInt::BigInt(uint64_t value) : sign(false), magnitude({value}) {
    /// remove entry if value is zero
    if (value == 0) {
        magnitude.clear();
    }
}

BigInt::BigInt(std::string_view value) : sign(false), magnitude({}) {
    if (value[0] == '-' || value[0] == '+') {
        if (value[0] == '-') {
            sign = true;
        }
        value.remove_prefix(1);
    }
    assert(value[0] == '0' && value[1] == 'x');
    value.remove_prefix(2);
    magnitude = vector_util::fromHexStringView(value);
}

BigInt::BigInt(const BigInt& other) : sign(other.sign), magnitude(other.magnitude) {}

BigInt::BigInt(BigInt&& other) noexcept : sign(other.sign), magnitude(std::move(other.magnitude)) {}

BigInt::BigInt(bool sign, const std::vector<uint64_t>& magnitude) : sign(sign), magnitude(magnitude) {}

bool BigInt::operator==(const BigInt& other) const {
    assert(!vector_util::hasLeadingZeros(magnitude));
    assert(!vector_util::hasLeadingZeros(other.magnitude));

    /// different magnitude sizes
    if (magnitude.size() != other.magnitude.size()) {
        return false;
    }
    /// non zero with different signs
    if (!magnitude.empty() && sign != other.sign) {
        return false;
    }
    for (size_t i = 0; i < magnitude.size(); ++i) {
        /// magnitudes not equal
        if (magnitude[i] != other.magnitude[i]) {
            return false;
        }
    }
    /// magnitudes are equal
    return true;
}

bool BigInt::operator!=(const BigInt& other) const {
    return !(*this == other);
}

BigInt BigInt::operator-() const {
    return {!this->sign, this->magnitude};
}

BigInt BigInt::operator+() const {
    return *this;
}

BigInt operator+(const BigInt& lhs, const BigInt& rhs) {
    auto [s, mag] = vector_util::add(lhs.sign, lhs.magnitude, rhs.sign, rhs.magnitude);
    return {s, mag};
}

BigInt operator-(const BigInt& lhs, const BigInt& rhs) {
    auto [s, mag] = vector_util::sub(lhs.sign, lhs.magnitude, rhs.sign, rhs.magnitude);
    return {s, mag};
}
} // namespace arbimath