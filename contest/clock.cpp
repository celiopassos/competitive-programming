clock_t start_time;
double get_current_time() {
  return (double)(std::clock() - startTime) / CLOCKS_PER_SEC;
}
// in main:
start_time = clock();
