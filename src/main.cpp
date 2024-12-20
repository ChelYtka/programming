#include <iostream>
#include <glm/glm.hpp>

int main() {
    glm::vec3 v1(1.0f, 2.0f, 3.0f);
    glm::vec3 v2(4.0f, 5.0f, 6.0f);

    // Сложение
    glm::vec3 sum = v1 + v2;
    
    // Вычитание
    glm::vec3 difference = v1 - v2;

    std::cout << "Sum: (" 
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
              
    return 0;
}