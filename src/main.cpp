#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Функция для вывода матрицы
void printMatrix(const glm::mat3& matrix) {
    const float* p = glm::value_ptr(matrix);
    for (int i = 0; i < 3; ++i) {
        std::cout << "| ";
        for (int j = 0; j < 3; ++j) {
            std::cout << p[i * 3 + j] << " ";
        }
        std::cout << "|\n";
    }
}

int main() {
    glm::vec3 v1(1.0f, 2.0f, 3.0f);
    glm::vec3 v2(4.0f, 5.0f, 6.0f);

    // Сложение
    glm::vec3 sum = v1 + v2;

    // Вычитание
    glm::vec3 difference = v1 - v2;

    std::cout << "\nSum: ("
              << sum.x << ", "
              << sum.y << ", "
              << sum.z << ")" << std::endl;

    std::cout << "Difference: ("
              << difference.x << ", "
              << difference.y << ", "
              << difference.z << ")" << std::endl;

    glm::vec3 v(1.0f, 2.0f, 3.0f);

    // Умножение на скаляр
    float scalar = 2.0f;
    glm::vec3 scaledVector = v * scalar;

    std::cout << "Scaled Vector: ("
              << scaledVector.x << ", "
              << scaledVector.y << ", "
              << scaledVector.z << ")" << std::endl;

    // Инициализация двух матриц
    glm::mat3 matrixA(2.0f); // 1 матрица
    glm::mat3 matrixB = glm::mat3(
        1.0f, 2.0f, 3.0f,
        2.0f, 1.0f, 3.0f,
        2.0f, 3.0f, 1.0f
    );
    printMatrix(matrixB);

    // сложение
    glm::mat3 sumMatrix = matrixA + matrixB;
    std::cout << "\nSum matrix:\n";
    printMatrix(sumMatrix);

    // умножение
    glm::mat3 multiplyMatrix = matrixA * matrixB;
    std::cout << "\nMultiply matrix:\n";
    printMatrix(multiplyMatrix);

    // транспонирование
    glm::mat3 transposedMatrix = glm::transpose(matrixB);
    std::cout << "\nTransposed matrix:\n";
    printMatrix(transposedMatrix);
    return 0;
}