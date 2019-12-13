from conans import ConanFile, CMake, tools
import os


class TestPackageConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake_find_package", "cmake"

    build_requires = "boost/1.71.0", "doctest/2.3.5"

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def test(self):
        if not tools.cross_building(self.settings):
            for testrunner in ["cxx11", "cxx17"]:
                bin_path = os.path.join(".", testrunner)
                if tools.os_info.is_windows:
                    bin_path += ".exe"
                self.run(bin_path, run_environment=True)
