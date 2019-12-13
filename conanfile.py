from conans import ConanFile, tools, CMake


class ClerrConan(ConanFile):
    name = "clerr"
    version = "1.0"
    description = "system_error integration for OpenCL"
    url = "https://github.com/mmha/ocl-errc"
    license = "MIT"
    author = "Morris Hafner <hafnermorris@gmail.com>"
    topics = ('opencl', 'gpu', 'gpgpu')
    generators = "cmake_find_package", "cmake"
    exports_sources = [
        "CMakeLists.txt",
        "cmake/*",
        "include/*",
        "LICENSE"
    ]

    requires = ("khronos-opencl-icd-loader/20191007@bincrafters/stable",
                "khronos-opencl-headers/20190806@bincrafters/stable")

    def build_requirements(self):
        if not self.in_local_cache:
            self.build_requires("boost/1.71.0")
            self.build_requires("doctest/2.3.5")

    _cmake = None
    @property
    def cmake(self):
        if self._cmake is None:
            self._cmake = CMake(self)
            self._cmake.definitions["BUILD_TESTING"] = not self.in_local_cache
            self._cmake.configure()
        return self._cmake

    def build(self):
        self.cmake.build()

    def package(self):
        self.cmake.install()
        self.copy("LICENSE", dst="share/licenses/clerr")
