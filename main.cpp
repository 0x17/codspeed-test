#include <benchmark/benchmark.h>
#include <string>
#include <gdx.hpp>

using namespace std::literals::string_literals;

constexpr int numSymbols{2*10}, numRecords{2*5000};

static void BM_gdxWriteReadRaw(benchmark::State &state)
{
    std::string msg;
    std::array<int, 20> keys{};
    std::array<double, 5> values{};
    int errNr{}, nrRecs {}, dimFrst {};
    const std::string fn{"bigfile.gdx"};
    for (auto _ : state)
    {
        {
            gdx::TGXFileObj gdx{msg};
            gdx.gdxOpenWrite(fn.c_str(), "benchmark", errNr);
            for (int j{}; j < numSymbols; j++)
            {
                gdx.gdxDataWriteRawStart(("a"s + std::to_string(j)).c_str(), "", 0, 0, 0);
                for (int i{}; i < numRecords; i++)
                    gdx.gdxDataWriteRaw(keys.data(), values.data());
                gdx.gdxDataWriteDone();
            }
            gdx.gdxClose();
        }
        {
            gdx::TGXFileObj gdx{msg};
            gdx.gdxOpenRead(fn.c_str(), errNr);
            for (int j{}; j < numSymbols; j++)
            {
                gdx.gdxDataReadRawStart(j + 1, nrRecs);
                for (int i{}; i < numRecords; i++)
                    gdx.gdxDataReadRaw(keys.data(), values.data(), dimFrst);
                gdx.gdxDataWriteDone();
            }
            gdx.gdxClose();
        }
    }
}
BENCHMARK(BM_gdxWriteReadRaw);

// Entrypoint of the benchmark executable
BENCHMARK_MAIN();