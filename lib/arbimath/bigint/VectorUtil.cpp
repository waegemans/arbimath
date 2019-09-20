#include "VectorUtil.hpp"

#include <cassert>
#include <string>
#include <x86intrin.h>

namespace arbimath::vector_util {
std::pair<bool, std::vector<uint64_t>> add(bool lhs_sign, const std::vector<uint64_t>& lhs, bool rhs_sign, const std::vector<uint64_t>& rhs) {
    if (lhs_sign == rhs_sign) {
        return {lhs_sign, addMagnitude(lhs, rhs)};
    }
    if (lhs_sign) {
        assert(!rhs_sign);
        return sub(false, rhs, false, lhs);
    }
    assert(!lhs_sign);
    assert(rhs_sign);
    return sub(false, lhs, false, rhs);
}

std::pair<bool, std::vector<uint64_t>> sub(bool lhs_sign, const std::vector<uint64_t>& lhs, bool rhs_sign, const std::vector<uint64_t>& rhs) {
    if (lhs_sign == rhs_sign) {
        /// both sides are positive
        if (!lhs_sign) {
            /// result will be in valid range
            if (less(rhs, lhs)) {
                return {false, subMagnitude(lhs, rhs)};
            }
            /// result will underflow -> swap operands and sign
            return {true, subMagnitude(rhs, lhs)};
        }
        /// both sides negative -> swap operands
        return sub(false, rhs, false, lhs);
    }
    /// different signs
    /// -a - b -> -a + -b
    if (lhs_sign) {
        assert(!rhs_sign);
        return add(true, lhs, true, rhs);
    }
    /// a - -b -> a + b
    return add(false, lhs, false, rhs);
}

std::vector<uint64_t> addMagnitude(const std::vector<uint64_t>& lhs, const std::vector<uint64_t>& rhs) {
    if (lhs.size() < rhs.size()) {
        return addMagnitude(rhs, lhs);
    }
    std::vector<uint64_t> res(lhs.size());
    unsigned char carry = 0;
    size_t i = 0;
    for (; i < rhs.size(); ++i) {
        carry = _addcarry_u64(carry, lhs[i], rhs[i], reinterpret_cast<unsigned long long int*>(&res[i]));
    }
    while (carry && i < lhs.size() && ~lhs[i] == 0) {
        ++i;
    }
    for (; i < lhs.size(); ++i) {
        res[i] = lhs[i];
    }
    if (carry) {
        res.push_back(1);
    }
    return res;
}

std::vector<uint64_t> subMagnitude(const std::vector<uint64_t>& lhs, const std::vector<uint64_t>& rhs) {
    assert(lhs.size() >= rhs.size());
    assert(less(rhs, lhs));
    unsigned char carry = 0;
    std::vector<uint64_t> res(lhs.size());

    for (size_t i = 0; i < lhs.size(); ++i) {
        uint64_t rhs_local = i < rhs.size() ? rhs[i] : 0;
        carry = _subborrow_u64(carry, lhs[i], rhs_local, reinterpret_cast<unsigned long long int*>(&res[i]));
    }
    removeLeadingZeros(res);
    return res;
}

std::vector<uint64_t> fromHexStringView(std::string_view stringView) {
    std::vector<uint64_t> res;
    for (size_t i = 16; i <= stringView.size(); i += 16) {
        res.push_back(std::stoull(std::string(stringView.substr(stringView.size() - i, 16)), nullptr, 16));
    }
    if (stringView.size() % 16 != 0) {
        res.push_back(std::stoull(std::string(stringView.substr(0, stringView.size() % 16)), nullptr, 16));
    }
    removeLeadingZeros(res);
    return res;
}

bool less(const std::vector<uint64_t>& lhs, const std::vector<uint64_t>& rhs) {
    assert(!hasLeadingZeros(lhs));
    assert(!hasLeadingZeros(rhs));
    if (lhs.size() < rhs.size())
        return true;
    if (lhs.size() > rhs.size())
        return false;
    for (size_t i = lhs.size(); i != 0; --i) {
        if (lhs[i - 1] == rhs[i - 1])
            continue;
        if (lhs[i - 1] < rhs[i - 1])
            return true;
        if (lhs[i - 1] > rhs[i - 1])
            return false;
    }
    /// equality
    return false;
}

bool hasLeadingZeros(const std::vector<uint64_t>& x) {
    if (x.empty()) {
        return false;
    }
    return x.back() == 0;
}

void removeLeadingZeros(std::vector<uint64_t>& x) {
    while (!x.empty() && x.back() == 0) {
        x.pop_back();
    }
}
} // namespace arbimath::vector_util
