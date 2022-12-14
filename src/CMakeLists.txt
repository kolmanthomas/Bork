# BUILD WITH FLAGS
# If building for debug folder: -DCMAKE_BUILD_TYPE=Debug
# If building for release folder: -DCMAKE_BUILD_TYPE=Release
# To output compiler flags and other compiler-related info for clangd: 
# 	1) Build CMake project with: -DCMAKE -DCMAKE_EXPORT_COMPILE_COMMANDS=ON 
# 	2) If using debug/release folder distinction, symlink a compile_commands.json file in the root of the 	# 	      folder structure with: ln -s ./debug/compile_commands.json ./compile_commands.json 
#define SPDLOG_FMT_EXTERNAL 0
# -lboost_log, -lVulkan, -lglfw, -ldl, -lpthread, -lX11, -lXxf86vm, -lXrandr, -lXi

add_executable(bork
	main.cpp 
	window.cpp
	image.cpp
	utils/debugging.cpp
	input/keyboard.cpp
	renderer/shader.cpp
	glfw/glfw_window.cpp
)
target_include_directories(bork PRIVATE "")


#[[
find_program(GLSLC glslc)
set(shader_path ${CMAKE_HOME_DIRECTORY}/shaders/)
file(GLOB shaders RELATIVE ${CMAKE_SOURCE_DIR} "${shader_path}*.vert" "${shader_path}*.frag")
foreach(shader ${shaders})
	set(input_glsl "${CMAKE_HOME_DIRECTORY}/${shader}")
	set(output_spv "${input_glsl}.spv")
	execute_process(COMMAND "glslc" "${input_glsl}" "-o" "${output_spv}")
endforeach()
]]


find_package(spdlog REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED) 
find_package(glfw3 REQUIRED) 
find_package(Eigen3 3.4 REQUIRED NO_MODULE)
find_package(glm REQUIRED)

target_link_libraries(bork PUBLIC 
	OpenGL
	GLEW::GLEW	
	glfw
	Eigen3::Eigen
	spdlog::spdlog
	shaderc_shared
	glm::glm
)
#target_compile_definitions(fb PRIVATE SPDLOG_FMT_EXTERNAL) 
