#include <clerr.hpp>
#include <doctest/doctest.h>
#include <iostream>

TEST_CASE("make_error_code") {
  SUBCASE("from enum") {
	std::error_code ec = make_error_code(clerr::error::success);
	CHECK(!ec);
  }
  SUBCASE("assign enum") {
	std::error_code ec = clerr::error::device_not_found;
	CHECK(ec);
  }
  SUBCASE("from int") {
	std::error_code ec = std::error_code(CL_COMPILER_NOT_AVAILABLE, clerr::cl_error_category);
	CHECK(ec);
  }
}

TEST_CASE("clear") {
  auto ec = make_error_code(clerr::error::invalid_binary);
  CHECK(ec);
  ec.clear();
  CHECK(!ec);
}

TEST_CASE("exceptions") {
  auto ec = std::error_code(clGetPlatformIDs(0, nullptr, nullptr), clerr::cl_error_category);
  CHECK(ec.value() == static_cast<int>(clerr::error::invalid_value));
  try {
	throw std::system_error{ec};
  } catch (std::system_error &e) {
	CHECK(e.code() == ec);
	CHECK(e.code() == make_error_code(clerr::error::invalid_value));
	CHECK(e.what() == std::string{"invalid value"});
  }
}