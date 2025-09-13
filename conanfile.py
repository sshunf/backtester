from conan import ConanFile

class BacktesterRecipe(ConanFile):
    name = "backtester"
    version = "0.1.0"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps", "VirtualRunEnv"

    def layout(self):
        # keep Conan-generated files in build/conan/
        self.folders.generators = "conan"

    def requirements(self):
        self.requires("fmt/11.2.0")
        self.requires("spdlog/1.15.3")
        self.requires("gtest/1.15.0")
