# x64-linux-mix

cmake_minimum_required(VERSION 3.5)

set(VCPKG_TARGET_ARCHITECTURE x64)
set(VCPKG_CRT_LINKAGE dynamic)
set(VCPKG_LIBRARY_LINKAGE static)
set(VCPKG_CMAKE_SYSTEM_NAME Linux)

# set(VCPKG_KEEP_ENV_VARS PATH)
set(VCPKG_ENV_PASSTHROUGH_UNTRACKED PATH)

set(DEPS_DYNAMIC assimp)
if((PORT IN_LIST DEPS_DYNAMIC) OR (PORT MATCHES "^qt-.*"))
    # Dynamic
    set(VCPKG_LIBRARY_LINKAGE dynamic)
    set(VCPKG_POLICY_DLLS_WITHOUT_LIBS enabled)
else()
    # Static
    set(VCPKG_LIBRARY_LINKAGE static)
endif()
