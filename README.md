# clerr: `system_error` Integration For OpenCL Error Codes

<table>
<tr>
<td>Conan</td>
<td><pre>
conan remote add mmha https://api.bintray.com/conan/mmha/public-conan
conan install clerr/1.0@mmha/stable
</pre></td>
</tr>
<tr>
<td>CMake</td>
<td><pre>
find_package(clerr REQUIRED)
target_link_libraries(app PRIVATE clerr::clerr)
</pre></td>
</tr>
</table>

This small header-only library provides an `enum class` for all OpenCL error codes and makes it possible to create `std::error_code`s from OpenCL. This bridges OpenCL errors with C++ exceptions (if desired) and `expected`-like types, provides human-readable error messages and generalises error transport to be API-agnostic. ([Further Reading](https://akrzemi1.wordpress.com/2017/07/12/your-own-error-code/))

## Examples

Use with exceptions:
```c++
#include <clerr.hpp>

try {
	auto ec = std::error_code(clGetPlatformIDs(0, nullptr, nullptr), clerr::cl_error_category);
	if(!ec) {
		throw std::system_error{ec};
	}
} catch(std::system_error &e) {
	assert(e.code() == static_cast<int>(clerr::error::invalid_value));
	assert(e.code() == CL_INVALID_VALUE);
	std::cout << e.what() << '\n'; // "invalid value"
}
```

Use with Boost.outcome:
```c++
#include <clerr.hpp>
#include <boost/outcome.hpp>

template<typename T>
using result = BOOST_OUTCOME_V2_NAMESPACE::result<T, std::error_code>;

result<std::string> get_platform_info(cl_platform_id platform, cl_platform_info param_name) {
	char const *result;
	auto err = std::error_code(clGetPlatformInfo(platform, param_name, sizeof(result), &result, nullptr), clerr::cl_error_category);
	if(err) {
		return err;
	}
	return std::string{result};
}

auto const platform_info = get_platform_info(platform, CL_PLATFORM_NAME);
if(platform_info) {
	std::cout << "Platform name: " << platform_info.value() << '\n';
}
else {
	std::cout << "failed to get platform name: " << platform_info.error().message();
}
```
