#include "BigInt.hpp"

#include <cassert>

namespace arbimath {

BigInt::BigInt() : sign(false), magnitude({}) {}

BigInt::BigInt(uint64_t value) : sign(false), magnitude({value}) {
    /// remove entry if value is zero
    if (value == 0) {
        magnitude.clear();
    }
}

BigInt::BigInt(std::string_view value) : sign(true), magnitude({42}) {
    // TODO
}

bool BigInt::operator==(const BigInt& other) const {
    assert(!hasLeadingZeros());
    assert(!other.hasLeadingZeros());

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

bool BigInt::hasLeadingZeros() const {
    if (magnitude.empty()) {
        return false;
    }
    return magnitude.back() == 0;
}

void BigInt::removeLeadingZeros() {
    while (!magnitude.empty() && magnitude.back() == 0) {
        magnitude.pop_back();
    }
}

} // namespace arbimath