#include <atomic>
#include <cstddef>
#include <cstdint>

std::atomic<uint8_t> value8{0};
std::atomic<uint16_t> value16{0};
std::atomic<uint32_t> value32{0};
std::atomic<uint64_t> value64{0};

template <typename T>
int TestAtomic(std::atomic<T>* value) {
  value->store(1);
  T expected = value->load();
  value->exchange(2);
  value->fetch_add(1);
  value->compare_exchange_strong(expected, 3);
  return value->is_lock_free();
}

int main() {
  int result = 0;

  result += TestAtomic(&value8);
  result += TestAtomic(&value16);
  result += TestAtomic(&value32);
  result += TestAtomic(&value64);

  return result;
}
