#include <benchmark/benchmark.h>
#include <string>
#include <gdx.hpp>

static void BM_gdxSimpleWrite(benchmark::State &state)
{
    std::string msg;
    gdx::TGXFileObj gdx{msg};
    std::array<int, 20> keys{};
    std::array<double, 5> values{};
    int errNr{};
    gdx.gdxOpenWrite("bigfile.gdx", "benchmark", errNr);
    gdx.gdxDataWriteRawStart("a", "", 0, 0, 0);
    for (int i{}; i < 1000; i++)
    {
        gdx.gdxDataWriteRaw(keys.data(), values.data());
    }
    gdx.gdxDataWriteDone();
    gdx.gdxClose();
}
BENCHMARK(BM_gdxSimpleWrite);

// Entrypoint of the benchmark executable
BENCHMARK_MAIN();