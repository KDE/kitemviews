cmake_minimum_required(VERSION 2.8.12)

project(KItemViews)

find_package(ECM 0.0.12 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR})

set(REQUIRED_QT_VERSION "5.2.0")
find_package(Qt5 ${REQUIRED_QT_VERSION} CONFIG REQUIRED Widgets)
include(KDEInstallDirs)
include(KDEFrameworkCompilerSettings)
include(KDECMakeSettings)

include(FeatureSummary)
include(GenerateExportHeader)
include(ECMSetupVersion)
include(ECMGenerateHeaders)

include(ECMCreateQmFromPoFiles)

set(KF5_VERSION "4.98.0") # handled by release scripts # handled by release scripts
ecm_setup_version(${KF5_VERSION} VARIABLE_PREFIX KITEMVIEWS
                        VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/kitemviews_version.h"
                        PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF5ItemViewsConfigVersion.cmake"
                        SOVERSION 5)


file(GLOB PO_FILES "po/*.po")
if (PO_FILES)
  ecm_create_qm_from_po_files(PO_FILES ${PO_FILES} CATALOG_NAME kitemviews5_qt)
endif()

add_subdirectory(src)
add_subdirectory(autotests)
add_subdirectory(tests)


# create a Config.cmake and a ConfigVersion.cmake file and install them
set(CMAKECONFIG_INSTALL_DIR "${CMAKECONFIG_INSTALL_PREFIX}/KF5ItemViews")

include(ECMPackageConfigHelpers)

ecm_configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/KF5ItemViewsConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/KF5ItemViewsConfig.cmake"
  INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
)

install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/KF5ItemViewsConfig.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/KF5ItemViewsConfigVersion.cmake"
  DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
  COMPONENT Devel
)

install(EXPORT KF5ItemViewsTargets DESTINATION "${CMAKECONFIG_INSTALL_DIR}" FILE KF5ItemViewsTargets.cmake NAMESPACE KF5:: )

install(FILES
   ${CMAKE_CURRENT_BINARY_DIR}/kitemviews_version.h
  DESTINATION ${KF5_INCLUDE_INSTALL_DIR} COMPONENT Devel
)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
