//
// (c) Jakub Melka 2023
//
// This source file is part of the licensed software between Jakub Melka
// and the users utilizing the software under the specified License Agreement.
// Usage of this source code is subject to the Software License Agreement.
//
// This source code is provided solely for educational, research, or teaching purposes,
// including paid ones. Licensee may modify, adapt, and create derivative works,
// but all modifications must be released as Public Domain or under a license having
// the same legal effect as publishing as Public Domain under US jurisdiction.
//
// The Software is provided "as is," without warranty of any kind. Licensor shall not be liable
// for any damages arising from the use or performance of this source code.
//
// Ownership and intellectual property rights to this source code remain with Licensor.
// It is important for the Licensee to read and understand the complete Software License Agreement.
//

#include "custom_vector.h"

#include "custom_vector.h"
#include "custom_array.h"
#include "custom_stack.h"
#include "custom_queue.h"
#include "custom_search.h"

#include <iostream>

int example1()
{
    std::cout << "Example 1. Custom vector - push_back" << std::endl;

    // Create an empty vector of integers
    course_l01::vector<int> numbers;

    // Add elements to the vector using push_back()
    numbers.push_back(1);
    numbers.push_back(2);
    numbers.push_back(3);

    // Access elements using indexing
    std::cout << "  First element: " << numbers[0] << std::endl;
    std::cout << "  Second element: " << numbers[1] << std::endl;
    std::cout << "  Third element: " << numbers[2] << std::endl;

    // Iterate over the vector using a range-based for loop
    std::cout << "  Elements: ";
    for (int number : numbers)
    {
        std::cout << number << " ";
    }
    std::cout << std::endl << std::endl;

    return 0;
}

int example2()
{
    std::cout << "Example 2. Custom vector - push_back and resize" << std::endl;

    course_l01::vector<int> numbers;

    // Add elements to the vector
    numbers.push_back(100);
    numbers.push_back(200);
    numbers.push_back(300);

    std::cout << "  Initial size: " << numbers.size() << std::endl;

    // Resize the vector to hold 5 elements
    numbers.resize(5);

    std::cout << "  New size after resize: " << numbers.size() << std::endl;

    // Access the new elements (default-initialized to zero)
    std::cout << "  New elements: ";
    for (int number : numbers)
    {
        std::cout << number << " ";
    }
    std::cout << std::endl << std::endl;

    return 0;
}

int example3()
{
    std::cout << "Example 3. Custom vector - initialize array and remove elements" << std::endl;

    course_l01::vector<int> numbers;

    // Add elements to the vector
    numbers.push_back(100);
    numbers.push_back(200);
    numbers.push_back(300);
    numbers.push_back(400);
    numbers.push_back(500);

    // Remove the third element
    numbers.erase(numbers.begin() + 2);

    // Remove the last element
    numbers.pop_back();

    std::cout << "  Updated elements: ";
    for (int number : numbers)
    {
        std::cout << number << " ";
    }
    std::cout << std::endl << std::endl;

    return 0;
}

int example4()
{
    std::cout << "Example 4. Custom vector - reserve elements and shrink to fit" << std::endl;

    course_l01::vector<int> numbers;
    std::cout << "  Vector capacity: " << numbers.capacity() << std::endl;
    numbers.reserve(5);
    std::cout << "  Vector capacity: " << numbers.capacity() << std::endl;

    // Add elements to the vector
    numbers.push_back(100);
    numbers.push_back(200);
    numbers.push_back(300);
    numbers.push_back(400);
    numbers.push_back(500);

    // Remove the third element
    numbers.erase(numbers.begin() + 2);

    // Remove the last element
    numbers.pop_back();

    std::cout << "  Updated elements: ";
    for (int number : numbers)
    {
        std::cout << number << " ";
    }
    std::cout << std::endl;

    std::cout << "  Vector capacity after erase: " << numbers.capacity() << std::endl;
    numbers.shrink_to_fit();
    std::cout << "  Vector capacity after shrink to fit: " << numbers.capacity() << std::endl;

    std::cout << std::endl << std::endl;

    return 0;
}

int example5()
{
    std::cout << "Example 5. Custom array" << std::endl;

    // Create an array of integers with size 6
    course_l01::array<int, 6> numbers = {1, 2, 3, 4};

    // Access elements using indexing
    std::cout << "Element 0: " << numbers[0] << std::endl;

    // Iterate over the array using a range-based for loop
    std::cout << "Elements: ";
    for (int num : numbers)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl << std::endl;

    return 0;
}

int example6()
{
    std::cout << "Example 6. Custom stack (LIFO)" << std::endl;

    // Create empty stack
    course_l01::stack<int> stack;

    // Push onto stack
    std::cout << "Pushed elements: ";
    for (int num : { 1, 2, 3, 4, 5})
    {
        stack.push(num);
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // Pop elements from stack
    std::cout << "Popped elements: ";
    while (!stack.empty())
    {
        std::cout << stack.top() << " ";
        stack.pop();
    }
    std::cout << std::endl << std::endl;

    return 0;
}

int example7()
{
    std::cout << "Example 7. Custom queue (FIFO)" << std::endl;

    // Create empty queue
    course_l01::queue<int> queue;

    // Push onto queue
    std::cout << "Inserted into queue: ";
    for (int num : { 1, 2, 3, 4, 5})
    {
        queue.push(num);
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // Pop elements from queue
    std::cout << "Removed from queue: ";
    while (!queue.empty())
    {
        std::cout << queue.front() << " ";
        queue.pop();
    }
    std::cout << std::endl << std::endl;

    return 0;
}

int example8()
{
    std::cout << "Example 8. Searching" << std::endl;
    static constexpr course_l01::array<int, 6> array { 10, 20, 30, 40, 50, 60 };

    {
        auto it = course_l01::linear_search(array.begin(), array.end(), 30);
        if (it != array.end())
            std::cout << "Value 30 found!" << std::endl;
        else
            std::cout << "Value 30 not found!" << std::endl;

        it = course_l01::linear_search(array.begin(), array.end(), 55);
        if (it != array.end())
            std::cout << "Value 55 found!" << std::endl;
        else
            std::cout << "Value 55 not found!" << std::endl;
    }

    {
        auto it = course_l01::binary_search(array.begin(), array.end(), 30);
        if (it != array.end())
            std::cout << "Value 30 found!" << std::endl;
        else
            std::cout << "Value 30 not found!" << std::endl;

        it = course_l01::binary_search(array.begin(), array.end(), 55);
        if (it != array.end())
            std::cout << "Value 55 found!" << std::endl;
        else
            std::cout << "Value 55 not found!" << std::endl;
    }

    return 0;
}

int main()
{
    example1();
    example2();
    example3();
    example4();
    example5();
    example6();
    example7();
    example8();

    return 0;
}
