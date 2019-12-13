#include <boost/outcome.hpp>
#include <clerr.hpp>
#include <doctest/doctest.h>
#include <iostream>
#include <vector>

TEST_CASE("opencl_call") {
  // enum construction from int requires C++17
  clerr::error err{clGetPlatformIDs(0, nullptr, nullptr)};
  CHECK(err == clerr::error::invalid_value);
  CHECK(make_error_code(err).message() == "invalid value");
}

template <typename T> using result = BOOST_OUTCOME_V2_NAMESPACE::result<T, std::error_code>;

result<std::string> get_platform_info(cl_platform_id platform, cl_platform_info param_name) {
  char const *result;
  auto err = std::error_code(clGetPlatformInfo(platform, param_name, sizeof(result), &result, nullptr),
                             clerr::cl_error_category);
  if (err) {
	return err;
  }
  return std::string{result};
}

TEST_CASE("boost_outcome") {
  auto const platform_info = get_platform_info(nullptr, CL_PLATFORM_NAME);
  if (platform_info) {
	INFO("get_platform_info succeeded with value " << platform_info.value());
  } else {
	CHECK(platform_info.error() == clerr::error::invalid_platform);
	CHECK(platform_info.error().message() == "invalid platform");
  }
}