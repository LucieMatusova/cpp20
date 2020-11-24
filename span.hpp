#include <iostream>
#include <span>
#include <vector>
#include <array>

// https://en.cppreference.com/w/cpp/container/span
// std::span

/* Use cases:
  void readInto(span<int> buffer);
    instead of
  void readInto(int* buffer, size_t bufferSize);

  for (auto& x : mySpan) { .. }
  std::find_if(mySpan.cbegin(), mySpan.cend(), predicate);
  std::ranges::find_if(mySpan, predicate);
 */
 
template<class T, std::size_t N, std::size_t M>
constexpr bool contains(std::span<T,N> span, std::span<T,M> sub) {
    return std::search(span.begin(), span.end(), sub.begin(), sub.end())
        != span.end();
}

void printContent(std::span<int> container) {
    std::cout << "container.size(): " << container.size() << '\n';
    for(auto e : container) std::cout << e << ' ';
    std::cout << "\n";
}

int span(void)
{
    int arr[]{1, 2, 3, 4};            
    printContent(arr);
    printContent(std::span{arr, 2});
    
    std::vector vec{1, 2, 3, 4, 5};   
    printContent(vec);

    std::array arr2{1, 2, 3, 4, 5, 6};
    printContent(arr2);
    
    constexpr int a[] { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
    constexpr int b[] { 8, 7, 6 };
    
    static_assert(contains(std::span{a}, std::span{a+1,4}));
    static_assert(!contains(std::span{a}, std::span{b}));
    
    return 0;
}
