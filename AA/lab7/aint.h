#define MAX 100

struct ant {

    int current_city, next_city, path_index;
    double path_probability[MAX] = {0.0};
    int path[MAX];
    double path_length = 0;
};

//void ChooseNextCity(const double alpha, const double beta);
int aint_search(double **dist, double **pher, double alpha, double p, double beta, int MAX_CITIES, int TIMES);


/*
class WorldMap{
private:
  int size;
  double** dist_map;
  double** fer_map;

public:
  WorldMap();
  ~WorldMap();

  void PrintDistMap();
  void PrintFerMap();

  double GetDistData(int, int);
  double GetFerData(int, int);
};
*/
