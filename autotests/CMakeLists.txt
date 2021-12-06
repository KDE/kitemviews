remove_definitions(-DQT_NO_CAST_FROM_ASCII)
remove_definitions(-DQT_NO_CAST_TO_ASCII)

find_package(Qt${QT_MAJOR_VERSION} ${REQUIRED_QT_VERSION} CONFIG REQUIRED Test)

include(ECMAddTests)

ecm_add_test(klistwidgetsearchlinetest.cpp TEST_NAME kitemviews-klistwidgetsearchlinetest LINK_LIBRARIES Qt${QT_MAJOR_VERSION}::Test KF5::ItemViews)
