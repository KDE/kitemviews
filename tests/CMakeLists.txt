remove_definitions(-DQT_NO_CAST_FROM_ASCII)
remove_definitions(-DQT_NO_CAST_TO_ASCII)

include(ECMMarkAsTest)

find_package(Qt${QT_MAJOR_VERSION} ${REQUIRED_QT_VERSION} CONFIG REQUIRED Test)

macro(kitemviews_executable_tests)
  foreach(_testname ${ARGN})
    add_executable(${_testname} ${_testname}.cpp)
    target_link_libraries(${_testname} Qt${QT_MAJOR_VERSION}::Test KF5::ItemViews)
    ecm_mark_as_test(${_testname})
  endforeach(_testname)
endmacro()

kitemviews_executable_tests(
  kcategorizedviewtest
  kwidgetitemdelegatetest
  ktreewidgetsearchlinetest
)
