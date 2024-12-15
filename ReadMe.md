# Vcpkg, CMake, Protobuf, DLL/so

```
cmake --preset=default && cmake --build build && cmake --install build && ./install/bin/Demo
```

## CMakeUserPresets.json template:

linux:
```json
{
  "version": 2,
  "configurePresets": [
    {
      "name": "default",
      "inherits": ["vcpkg", "linux-dynamic"],
      "environment": {
        "VCPKG_ROOT": "/home/yda/sdk/vcpkg",
        "CMAKE_EXPORT_COMPILE_COMMANDS": "ON"
      }
    }
  ]
}
```
windows:
```json
{
  "version": 2,
  "configurePresets": [
    {
      "name": "default",
      "inherits": ["vcpkg", "windows-dynamic"],
      "environment": {
        "VCPKG_ROOT": "D:/vcpkg",
        "CMAKE_EXPORT_COMPILE_COMMANDS": "ON"
      }
    }
  ]
}
```