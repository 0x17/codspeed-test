#include <benchmark/benchmark.h>

// Define the function under test
static void BM_StringCopy(benchmark::State &state)
{
    std::string x = "hello";

    // Google benchmark relies on state.begin() and state.end() to run the benchmark and count iterations
    for (auto _ : state)
    {
        std::string copy(x);

        // Use DoNotOptimize and ClobberMemory to prevent the compiler optimizing away your benchmark
        // See: https://google.github.io/benchmark/user_guide.html#preventing-optimization
        benchmark::DoNotOptimize(copy);
        benchmark::ClobberMemory();
    }
}
// Register the benchmarked to be called by the executable
BENCHMARK(BM_StringCopy);

static void BM_memcpy(benchmark::State &state)
{
    char *src = new char[state.range(0)];
    char *dst = new char[state.range(0)];
    memset(src, 'x', state.range(0));
    for (auto _ : state)
    {
        memcpy(dst, src, state.range(0));
        benchmark::DoNotOptimize(dst);
        benchmark::ClobberMemory();
    }
    delete[] src;
    delete[] dst;
}

BENCHMARK(BM_memcpy)->Range(8, 8 << 10);

// Entrypoint of the benchmark executable
BENCHMARK_MAIN();