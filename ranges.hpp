#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>

// https://en.cppreference.com/w/cpp/ranges
// The ranges library brings functional concepts to C++

// sudo add-apt-repository ppa:ubuntu-toolchain-r/test
// sudo apt-get install g++-10

int ranges(void)
{
    std::vector<int> v1{ 21, 8, 3, 4, 6, 5, 1, 2 };
    auto printElem = [](auto const e) { std::cout << ' ' << e; };
   
    //--------------------------------------------------------------------------------------
    
    std::cout << "\nPrint vector elements.\n";
    // before C++20
    for(auto const i : v1)
        printElem(i); 
    // or std::for_each(std::cbegin(v1), std::cend(v1), printElem);
    printElem('\n');
    
    // with C++20
    std::ranges::for_each(v1, printElem);
    
    //--------------------------------------------------------------------------------------
    
    std::cout << "\nSkip the first 2 elements and print only even numbers in the next 3.\n";
    auto isEven = [](auto const i) { return i % 2 == 0; };
    
    // before C++20
    auto it = std::cbegin(v1);
    std::advance(it, 2);
    auto ix = 0;
    while (it != std::cend(v1) && ix++ < 3) {
        if (isEven(*it))
            printElem(*it);
        it++;
    }
    printElem('\n');
    
    // with C++20
    for (auto const i : v1 
                  | std::views::drop(2)
                  | std::views::take(3)
                  | std::views::filter(isEven))
    { printElem(i); };
    
    //--------------------------------------------------------------------------------------
    
    std::cout << "\nSkip the first two elements and sort the rest.\n";
    // Before C++20
    std::vector<int> v2{ 21, 8, 3, 4, 6, 5, 1, 2 };
    auto it2 = std::begin(v2);
    std::advance(it2, 2);
    std::sort(it2, std::end(v2));
    for(const auto r : v2) printElem(r);
    printElem('\n');
        
    // with C++20
    std::vector<int> v3{ 21, 8, 3, 4, 6, 5, 1, 2 };
    std::ranges::sort(std::views::drop(v3, 2));
    for(auto r : v3 ) printElem(r);
    printElem('\n');
    
    //--------------------------------------------------------------------------------------
    
    std::cout << "\nInfinite iota generator: Print 10 prime numbers larger than 1m.\n";
    auto isPrime = [](int i){
      for(int j = 2; j*j <= i; ++j)
        if(i % j == 0) 
          return false;      
      return true;
    };
    
    // std::views::iota = range factory generating a sequence of elements (finite and infinite)
    for (int i : std::views::iota(1000000) | std::views::filter(isPrime) | std::views::take(10))
      printElem(i);  
  
  return 0;
}
