cmake_minimum_required(VERSION 3.5.0)
project(coursework VERSION 0.1.0 LANGUAGES C CXX)

# Установка CMake для загрузки GLM через Git
include(FetchContent)

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG        master  # или укажите конкретный тег, например 0.9.9.8
)

FetchContent_MakeAvailable(glm)
    
# Убедитесь, что путь к заголовочным файлам добавлен
include_directories(${glm_SOURCE_DIR}/glm)

# Добавьте ваш исполняемый файл
add_executable(coursework src/main.cpp)

# Подключите GLM к вашему исполняемому файлу
target_link_libraries(coursework glm::glm)



