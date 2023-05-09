#include <cstdlib>
#include <cstdio>
#include <mutex>
#include <omp.h>
#include <thread>

inline auto
randf()
{
  return float(std::rand()) / RAND_MAX;
}

void
mul(const float* a, const float* b, int n, float* c)
{
  for (int i = 0; i < n; ++i)
	c[i] = a[i] * b[i];
}

constexpr auto maxThreads = 8;
std::thread threadPool[maxThreads];

void
par_mul(const float* a, const float* b, int n, float* c, int p)
{
  if (p - 1 > maxThreads)
    p = maxThreads;

  auto m = n / p;
  auto r = n - m * p;
  auto f = m + r;

  for (int s = f, i = 0; i < p - 1; ++i, s += m)
    threadPool[i] = std::move(std::thread{mul, a + s, b + s, m, c + s});
  mul(a, b, f, c);
  for (int i = 0; i < p - 1; ++i)
	threadPool[i].join();
}

void
omp_par_mul(const float* a, const float* b, int n, float* c)
{
#pragma omp parallel for
  for (int i = 0; i < n; ++i)
	c[i] = a[i] * b[i];
}

auto
reduce(const float* a, int n)
{
  float s{};

  for (int i = 0; i < n; ++i)
    s += a[i];
  return s;
}

struct Result
{
  float s;
  std::mutex mutex;
};

void
par_reduce_aux(const float* a, int n, Result* result)
{
  auto s = reduce(a, n);
  std::lock_guard<std::mutex> lock(result->mutex);

  //result->mutex.lock();
  result->s += s;
  //result->mutex.unlock();
}

auto
par_reduce(const float* a, int n, int p)
{
  if (p - 1 > maxThreads)
	p = maxThreads;

  auto m = n / p;
  auto r = n - m * p;
  auto f = m + r;
  Result result;

  result.s = 0;
  for (int s = f, i = 0; i < p - 1; ++i, s += m)
	threadPool[i] = std::move(std::thread{par_reduce_aux, a + s, m, &result});
  par_reduce_aux(a, f, &result);
  for (int i = 0; i < p - 1; ++i)
    threadPool[i].join();
  return result.s;
}

auto
omp_par_reduce(const float* a, int n)
{
  float s{};

#pragma omp parallel for shared(a, n) reduction(+:s)
  for (int i = 0; i < n; ++i)
	s += a[i];
  return s;
}

void
mv_mul(const float* A, const float* b, float* c, int n)
{
  auto p = A;

  for (int i = 0; i < n; ++i)
  {
    float s{};

	for (int j = 0; j < n; ++j)
	  s += *p++ * b[j];
	c[i] = s;
  }
}

auto
test(int n)
{
  auto a = new float[n];
  auto b = new float[n];

  for (int i = 0; i < n; ++i)
  {
	a[i] = randf();
	b[i] = randf();
  }

  auto c = new float[n];

  mul(a, b, n, c);
  par_mul(a, b, n, c, 4);

  auto s = reduce(c, n);

  delete []a;
  delete []b;
  delete []c;
  return s;
}

int
main()
{
  printf("%g\n", test(1000));
  printf("%g\n", test(1000 * 1000));
  printf("%g\n", test(1000 * 1000 * 10));
  return 0;
}