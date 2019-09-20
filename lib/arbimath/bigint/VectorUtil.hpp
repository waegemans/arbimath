#pragma once

#include <cstdint>
#include <string_view>
#include <vector>

namespace arbimath::vector_util {
/// add two vectors with given signs together and return resulting sign and magnitude
std::pair<bool, std::vector<uint64_t>> add(bool lhs_sign, const std::vector<uint64_t>& lhs, bool rhs_sign, const std::vector<uint64_t>& rhs);
/// subtract two vectors with given signs together and return resulting sign and magnitude
std::pair<bool, std::vector<uint64_t>> sub(bool lhs_sign, const std::vector<uint64_t>& lhs, bool rhs_sign, const std::vector<uint64_t>& rhs);
/// add two vectors together and returns the result
std::vector<uint64_t> addMagnitude(const std::vector<uint64_t>& lhs, const std::vector<uint64_t>& rhs);
/// subs two vectors together and returns the result. lhs must be larger then rhs
std::vector<uint64_t> subMagnitude(const std::vector<uint64_t>& lhs, const std::vector<uint64_t>& rhs);
/// converts an hex string without prefix to
std::vector<uint64_t> fromHexStringView(std::string_view stringView);

/// check if lhs is smaller then rhs
bool less(const std::vector<uint64_t>& lhs, const std::vector<uint64_t>& rhs);

bool hasLeadingZeros(const std::vector<uint64_t>& x);
void removeLeadingZeros(std::vector<uint64_t>& x);

} // namespace arbimath::vector_util
