cmake_minimum_required(VERSION 3.10)  # Устанавливаем минимально необходимую версию CMake

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")  # Определяем переменную PATCH_VERSION с значением "1"
set(PROJECT_VERSION 0.0.${PATCH_VERSION})  # Определяем переменную PROJECT_VERSION как 0.0.1

project(helloworld VERSION ${PROJECT_VERSION})  # Объявляем проект helloworld с заданной версией

find_package(Boost COMPONENTS unit_test_framework REQUIRED)  # Ищем библиотеку Boost, компонент unit_test_framework, обязательно

configure_file(version.h.in version.h)  # Конфигурируем файл заголовка version.h из шаблона version.h.in

add_executable(helloworld_cli main.cpp)  # Добавляем исполняемый файл helloworld_cli, исходный файл main.cpp
add_library(helloworld lib.cpp)  # Создаём библиотеку helloworld из исходного файла lib.cpp
add_executable(test_version test_version.cpp)  # Добавляем исполняемый файл test_version, исходный файл test_version.cpp

set_target_properties(helloworld_cli helloworld test_version PROPERTIES  # Устанавливаем свойства для нескольких целей
    CXX_STANDARD 14  # Используем стандарт C++14
    CXX_STANDARD_REQUIRED ON  # Стандарт C++14 обязателен
)

target_include_directories(helloworld  # Указываем директории для включения для библиотеки helloworld
    PRIVATE "${CMAKE_BINARY_DIR}"  # Директория сборки является приватной для этой цели
)

set_target_properties(test_version PROPERTIES  # Устанавливаем свойства для цели test_version
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK  # Определяем BOOST_TEST_DYN_LINK для динамической линковки Boost
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}  # Включаем директории Boost
)

target_link_libraries(helloworld_cli PRIVATE  # Линкуем библиотеку helloworld к исполняемому файлу helloworld_cli
    helloworld
)

target_link_libraries(test_version  # Линкуем библиотеки к исполняемому файлу test_version
    ${Boost_LIBRARIES}  # Линкуем библиотеки Boost
    helloworld  # Линкуем библиотеку helloworld
)

if (MSVC)  # Если используется компилятор MSVC (Microsoft Visual C++)
    target_compile_options(helloworld_cli PRIVATE  # Устанавливаем параметры компиляции для helloworld_cli
        /W4  # Уровень предупреждений /W4
    )
    target_compile_options(helloworld PRIVATE  # Устанавливаем параметры компиляции для библиотеки helloworld
        /W4  
    )
    target_compile_options(test_version PRIVATE  # Устанавливаем параметры компиляции для test_version
        /W4  
    )
else ()  # Если используется другой компилятор
    target_compile_options(helloworld_cli PRIVATE  # Устанавливаем параметры компиляции для helloworld_cli
        -Wall -Wextra -pedantic -Werror  # Включаем все предупреждения и ошибки при их наличии
    )
    target_compile_options(helloworld PRIVATE  # Устанавливаем параметры компиляции для библиотеки helloworld
        -Wall -Wextra -pedantic -Werror  
    )
    target_compile_options(test_version PRIVATE  # Устанавливаем параметры компиляции для test_version
        -Wall -Wextra -pedantic -Werror  
    )
endif()

install(TARGETS helloworld_cli RUNTIME DESTINATION bin)  # Устанавливаем исполняемый файл helloworld_cli в директорию bin

# Установки для CPack (CPack settings)
include(CPack)  # Подключаем CPack для создания пакетов

# Проверяем операционную систему (Check operating system)
if(APPLE)  
    set(CPACK_GENERATOR "productbuild")  # Для macOS используем productbuild для создания .pkg
    set(CPACK_PACKAGE_FILE_NAME "helloworld-${CMAKE_PROJECT_VERSION}-macOS")  # Имя пакета для macOS
    set(CPACK_PRODUCTBUILD_IDENTITY "Developer ID Installer")  # Идентификатор для кодовой подписи (если используется)
elseif(UNIX)  
    set(CPACK_GENERATOR "DEB")  # Для Linux используем DEB пакеты
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Your Name")  # Установите ваше имя как мейнтейнера пакета
    set(CPACK_PACKAGE_FILE_NAME "helloworld-${CMAKE_PROJECT_VERSION}-Linux")  # Имя пакета для Linux
endif()

# Общие настройки для всех ОС (Common settings for all OS)
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})  # Основная версия пакета
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})  # Минорная версия пакета
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})  # Патч версия пакета

set(CPACK_PACKAGE_NAME "helloworld")  # Имя пакета

# Добавляем CPack (Add CPack)
include(CPack)  

set(CPACK_PACKAGE_CONTACT example@example.com)  # Контактная информация мейнтейнера пакета

enable_testing()  # Включаем поддержку тестирования в CMake

add_test(test_version test_version)  # Регистрируем тест с именем test_version, который будет запускать исполняемый файл test_version