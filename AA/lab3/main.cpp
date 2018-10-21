#include <cstdio>
#include <cstdlib>
#include <algorithm>    // std::swap

#include <vector>
#include <ctime>

using namespace std;

template <typename T>
void combSort(vector<T> &sort)
{
  int n = 0; // количество перестановок
  double fakt = 1.2473309; // фактор уменьшения
  double step = sort.size() - 1;

  while (step >= 1) {
    for (int i = 0; i + step < sort.size(); ++i)
      if (sort[i] > sort[i + step])
        swap(sort[i], sort[i + step]);

    step /= fakt;
  }

  for (int i = 0; i < sort.size() - 1; i++) {
    bool swapped = false;
    for (int j = 0; j < sort.size() - i - 1; j++)
      if (sort[j] > sort[j + 1]) {
        swap(sort[j], sort[j + 1]);
        swapped = true;
      }

    if (!swapped)
      break;
  }
}

int main() {
	std::srand(std::time(0)); //use current time as seed for random generator

	for(int i = 0; i < 1; i++) {
		int vsize = 100 + i*100;

		vector<int> v_orig(vsize), v_sorted(vsize);

		for(int i = 0; i < vsize; i++)
			v_orig[i] = std::rand()%10;
		v_sorted = v_orig;
		//printf("%d and %d\n", v_orig[7],v_sorted_ref[7]);

		combSort(v_sorted);

		for(int i = 0; i < v_sorted.size(); i++)
			printf("%d ", v_sorted[i]);
	}
}
