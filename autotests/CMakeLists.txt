remove_definitions(-DQT_NO_CAST_FROM_ASCII)
remove_definitions(-DQT_NO_CAST_TO_ASCII)

find_package(Qt5 ${REQUIRED_QT_VERSION} CONFIG REQUIRED Test)

include(ECMAddTests)

ecm_add_test(klistwidgetsearchlinetest.cpp TEST_NAME kitemviews-klistwidgetsearchlinetest LINK_LIBRARIES Qt5::Test KF5::ItemViews)
