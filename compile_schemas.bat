:: windows needs to have the schemas compiled, because we are using vckpg
vcpkg_installed\x64-windows\tools\glib\glib-compile-schemas.exe vcpkg_installed\x64-windows\share\glib-2.0\schemas
:: XDG_DATA_DIRS needs to be set as a environment var else gtk will not find the schemas for the dialogs
setx XDG_DATA_DIRS "%1\vcpkg_installed\x64-windows\share"