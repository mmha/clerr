#include <CL/cl.h>
#include <system_error>

namespace clerr {
enum class error : cl_int {
  success = CL_SUCCESS,
  device_not_found = CL_DEVICE_NOT_FOUND,
  device_not_available = CL_DEVICE_NOT_AVAILABLE,
  compiler_not_available = CL_COMPILER_NOT_AVAILABLE,
  mem_object_allocation_failure = CL_MEM_OBJECT_ALLOCATION_FAILURE,
  out_of_resources = CL_OUT_OF_RESOURCES,
  out_of_host_memory = CL_OUT_OF_HOST_MEMORY,
  profiling_info_not_available = CL_PROFILING_INFO_NOT_AVAILABLE,
  mem_copy_overlap = CL_MEM_COPY_OVERLAP,
  image_format_mismatch = CL_IMAGE_FORMAT_MISMATCH,
  image_format_not_supported = CL_IMAGE_FORMAT_NOT_SUPPORTED,
  build_program_failure = CL_BUILD_PROGRAM_FAILURE,
  map_failure = CL_MAP_FAILURE,
#ifdef CL_VERSION_1_1
  misaligned_sub_buffer_offset = CL_MISALIGNED_SUB_BUFFER_OFFSET,
  exec_status_error_for_events_in_wait_list = CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST,
#endif
#ifdef CL_VERSION_1_2
  compile_program_failure = CL_COMPILE_PROGRAM_FAILURE,
  linker_not_available = CL_LINKER_NOT_AVAILABLE,
  link_program_failure = CL_LINK_PROGRAM_FAILURE,
  device_partition_failed = CL_DEVICE_PARTITION_FAILED,
  kernel_arg_info_not_available = CL_KERNEL_ARG_INFO_NOT_AVAILABLE,
#endif
  invalid_value = CL_INVALID_VALUE,
  invalid_device_type = CL_INVALID_DEVICE_TYPE,
  invalid_platform = CL_INVALID_PLATFORM,
  invalid_device = CL_INVALID_DEVICE,
  invalid_context = CL_INVALID_CONTEXT,
  invalid_queue_properties = CL_INVALID_QUEUE_PROPERTIES,
  invalid_command_queue = CL_INVALID_COMMAND_QUEUE,
  invalid_host_ptr = CL_INVALID_HOST_PTR,
  invalid_mem_object = CL_INVALID_MEM_OBJECT,
  invalid_image_format_descriptor = CL_INVALID_IMAGE_FORMAT_DESCRIPTOR,
  invalid_image_size = CL_INVALID_IMAGE_SIZE,
  invalid_sampler = CL_INVALID_SAMPLER,
  invalid_binary = CL_INVALID_BINARY,
  invalid_build_options = CL_INVALID_BUILD_OPTIONS,
  invalid_program = CL_INVALID_PROGRAM,
  invalid_program_executable = CL_INVALID_PROGRAM_EXECUTABLE,
  invalid_kernel_name = CL_INVALID_KERNEL_NAME,
  invalid_kernel_definition = CL_INVALID_KERNEL_DEFINITION,
  invalid_kernel = CL_INVALID_KERNEL,
  invalid_arg_index = CL_INVALID_ARG_INDEX,
  invalid_arg_value = CL_INVALID_ARG_VALUE,
  invalid_arg_size = CL_INVALID_ARG_SIZE,
  invalid_kernel_args = CL_INVALID_KERNEL_ARGS,
  invalid_work_dimension = CL_INVALID_WORK_DIMENSION,
  invalid_work_group_size = CL_INVALID_WORK_GROUP_SIZE,
  invalid_work_item_size = CL_INVALID_WORK_ITEM_SIZE,
  invalid_global_offset = CL_INVALID_GLOBAL_OFFSET,
  invalid_event_wait_list = CL_INVALID_EVENT_WAIT_LIST,
  invalid_event = CL_INVALID_EVENT,
  invalid_operation = CL_INVALID_OPERATION,
  invalid_gl_object = CL_INVALID_GL_OBJECT,
  invalid_buffer_size = CL_INVALID_BUFFER_SIZE,
  invalid_mip_level = CL_INVALID_MIP_LEVEL,
  invalid_global_work_size = CL_INVALID_GLOBAL_WORK_SIZE,
#ifdef CL_VERSION_1_1
  invalid_property = CL_INVALID_PROPERTY,
#endif
#ifdef CL_VERSION_1_2
  invalid_image_descriptor = CL_INVALID_IMAGE_DESCRIPTOR,
  invalid_compiler_options = CL_INVALID_COMPILER_OPTIONS,
  invalid_linker_options = CL_INVALID_LINKER_OPTIONS,
  invalid_device_partition_count = CL_INVALID_DEVICE_PARTITION_COUNT,
#endif
#ifdef CL_VERSION_2_0
  invalid_pipe_size = CL_INVALID_PIPE_SIZE,
  invalid_device_queue = CL_INVALID_DEVICE_QUEUE,
#endif
#ifdef CL_VERSION_2_2
  invalid_spec_id = CL_INVALID_SPEC_ID,
  max_size_restriction_exceeded = CL_MAX_SIZE_RESTRICTION_EXCEEDED,
#endif
};

static_assert(CL_SUCCESS == 0, "Success error code must be 0");
} // namespace clerr

namespace std {
template <> struct is_error_code_enum<clerr::error> : true_type {};
} // namespace std

namespace clerr {
struct opencl_error_category : std::error_category {
  const char *name() const noexcept override { return "opencl"; }

  std::string message(int e) const override {
	switch (static_cast<error>(e)) {
	case error::success:
	  return "success";
	case error::device_not_found:
	  return "device not found";
	case error::device_not_available:
	  return "device not available";
	case error::compiler_not_available:
	  return "compiler not available";
	case error::mem_object_allocation_failure:
	  return "mem object allocation failure";
	case error::out_of_resources:
	  return "out of resources";
	case error::out_of_host_memory:
	  return "out of host memory";
	case error::profiling_info_not_available:
	  return "profiling info not available";
	case error::mem_copy_overlap:
	  return "mem copy overlap";
	case error::image_format_mismatch:
	  return "image format mismatch";
	case error::image_format_not_supported:
	  return "image format not supported";
	case error::build_program_failure:
	  return "build program failure";
	case error::map_failure:
	  return "map failure";
#ifdef CL_VERSION_1_1
	case error::misaligned_sub_buffer_offset:
	  return "misaligned sub buffer offset";
	case error::exec_status_error_for_events_in_wait_list:
	  return "exec status error for events in wait list";
#endif
#ifdef CL_VERSION_1_2
	case error::compile_program_failure:
	  return "compile program failure";
	case error::linker_not_available:
	  return "linker not available";
	case error::link_program_failure:
	  return "link program failure";
	case error::device_partition_failed:
	  return "device partition failed";
	case error::kernel_arg_info_not_available:
	  return "kernel arg info not available";
#endif
	case error::invalid_value:
	  return "invalid value";
	case error::invalid_device_type:
	  return "invalid device type";
	case error::invalid_platform:
	  return "invalid platform";
	case error::invalid_device:
	  return "invalid device";
	case error::invalid_context:
	  return "invalid context";
	case error::invalid_queue_properties:
	  return "invalid queue properties";
	case error::invalid_command_queue:
	  return "invalid command queue";
	case error::invalid_host_ptr:
	  return "invalid host ptr";
	case error::invalid_mem_object:
	  return "invalid mem object";
	case error::invalid_image_format_descriptor:
	  return "invalid image format descriptor";
	case error::invalid_image_size:
	  return "invalid image size";
	case error::invalid_sampler:
	  return "invalid sampler";
	case error::invalid_binary:
	  return "invalid binary";
	case error::invalid_build_options:
	  return "invalid build options";
	case error::invalid_program:
	  return "invalid program";
	case error::invalid_program_executable:
	  return "invalid program executable";
	case error::invalid_kernel_name:
	  return "invalid kernel name";
	case error::invalid_kernel_definition:
	  return "invalid kernel definition";
	case error::invalid_kernel:
	  return "invalid kernel";
	case error::invalid_arg_index:
	  return "invalid arg index";
	case error::invalid_arg_value:
	  return "invalid arg value";
	case error::invalid_arg_size:
	  return "invalid arg size";
	case error::invalid_kernel_args:
	  return "invalid kernel args";
	case error::invalid_work_dimension:
	  return "invalid work dimension";
	case error::invalid_work_group_size:
	  return "invalid work group size";
	case error::invalid_work_item_size:
	  return "invalid work item size";
	case error::invalid_global_offset:
	  return "invalid global offset";
	case error::invalid_event_wait_list:
	  return "invalid event wait list";
	case error::invalid_event:
	  return "invalid event";
	case error::invalid_operation:
	  return "invalid operation";
	case error::invalid_gl_object:
	  return "invalid gl object";
	case error::invalid_buffer_size:
	  return "invalid buffer size";
	case error::invalid_mip_level:
	  return "invalid mip level";
	case error::invalid_global_work_size:
	  return "invalid global work size";
#ifdef CL_VERSION_1_1
	case error::invalid_property:
	  return "invalid property";
#endif
#ifdef CL_VERSION_1_2
	case error::invalid_image_descriptor:
	  return "invalid image descriptor";
	case error::invalid_compiler_options:
	  return "invalid compiler options";
	case error::invalid_linker_options:
	  return "invalid linker options";
	case error::invalid_device_partition_count:
	  return "invalid device partition count";
#endif
#ifdef CL_VERSION_2_0
	case error::invalid_pipe_size:
	  return "invalid pipe size";
	case error::invalid_device_queue:
	  return "invalid device queue";
#endif
#ifdef CL_VERSION_2_2
	case error::invalid_spec_id:
	  return "invalid spec id";
	case error::max_size_restriction_exceeded:
	  return "max size restriction exceeded";
#endif
	}
  }
};

#if __cplusplus >= 201703L
const inline opencl_error_category cl_error_category;
#elif defined(_MSC_VER)
const __declspec(selectany) opencl_error_category cl_error_category;
#elif defined(__GNUC__)
[[gnu::weak]] opencl_error_category cl_error_category;
#else
#error "Unsupported compiler. Use gcc, clang, MSVC or enable C++17 mode"
#endif

inline std::error_code make_error_code(error e) { return {static_cast<int>(e), cl_error_category}; }
} // namespace clerr
