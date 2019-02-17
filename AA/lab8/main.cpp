#include <stdio.h>
#include <iostream>

#include <vector>
#include <string>
#include <unordered_map>

std::vector<int> searchKMP(std::string string, std::string substring) {
  //concatenates
  std::string concStr = substring + "@" + string ;
  int len = concStr.length();

  std::vector<int> resV;
  resV.push_back(0);

  int j;
  for(int i = 1; i < len; i++) {
    j = resV[i-1];
      while(j > 0 && concStr[i] != concStr[j])
        j = resV[j - 1];

      if (concStr[i] == concStr[j])
        j++;

      resV.push_back(j);
  }

  resV.erase(resV.begin(), resV.begin() + substring.length() + 1);

  for(int i = 0; i < resV.size(); i++)
    std::cout << resV[i] << " ";
  std::cout << "\n";

  std::cout << "Подстрока найдена с индексов: ";
  for(int i = 0; i < resV.size(); i++)
    if(resV[i] == substring.length())
      std::cout << i-substring.length()+1 << "; ";
  std::cout << "\n";
  return resV;
}

//***************************************************//

std::vector<int> bcVSearch(std::string substring) {

  int len = substring.length();
  int* res = new int[len];

  for(int i = len - 2; i >= 0; i--) {
    res[i] = len - 1 - i;
    for(int j = i+1; j < len-1; j++) {
      if(substring[i] == substring[j])
        res[i] = res[j];
    }
  }
  res[len-1] = len;
  for(int i = len-2; i > 0; i--)
    if(substring[len-1] == substring[i]) {
      res[len-1] = res[i];
      break;
    }

  std::vector<int> resV;
  for(int i = 0; i < len; i++)
    resV.push_back(res[i]);

  return resV;
}

std::vector<int> gsVSearch(std::string substring) {

  int m = substring.length();
  std::string s = substring;

  std::vector<int> suffshift(m + 1, m);
  std::vector<int> z(m, 0);


  for (int j = 1, maxZidx = 0, maxZ = 0; j < m; ++j) { // 1 to len
    if (j <= maxZ)
      z[j] = std::min(maxZ - j + 1, z[j - maxZidx]);
    while (j + z[j] < m && s[m - 1 - z[j]] == s[m - 1 - (j + z[j])])
     z[j]++;
    if (j + z[j] - 1 > maxZ) {
      maxZidx = j;
      maxZ = j + z[j] - 1;
    }
  }

  for (int j = m - 1; j > 0; j--)
    suffshift[m - z[j]] = j; //цикл №1

  for (int j = 1, r = 0; j <= m - 1; j++) //цикл №2
    if (j + z[j] == m)
      for (; r <= j; r++)
        if (suffshift[r] == m)
          suffshift[r] = j;



  std::vector<int> resV;

  for(int i = s.length(); i > 0; i--)
    resV.push_back(suffshift[i]);

  for(int i = 0; i < s.length(); i++)
    std::cout << resV[i] << " ";
  std::cout << "\n";

  return resV;
}

void searchBM(std::string string, std::string substring) {
    std::vector<int> bcV = bcVSearch(substring);
    std::vector<int> gsV = gsVSearch(substring);

    int i = 0, j = 0;
    while(i < string.length() - substring.length() + 1) {
      j = substring.length()-1;
      std::cout << string << "\n";
      for(int q = 0; q < i; q++)
        std::cout << "~";

      std::cout <<substring <<"\n";

      while(j >= 0 && substring[j] == string[i+j])
        j--;
      if(j == -1) {
        std::cout << "Подстрока найдена с " << i << "\n";
        i++;
      }
      else {
        int isin = substring.length();
        for(int k = 0; k < substring.length(); k ++) {
          if(string[i+j] == substring[k]) {
            isin = bcV[k];
            break;
          }
        }
        printf("bc=%d and gs=%d\n", isin, gsV[substring.length() - 1 - j] );
        i+= std::max(isin,gsV[substring.length() - 1 - j]);
      }

    }

    //for(int i = 0; i < bcV.size(); i++)
    //  std::cout << bcV[i] << " ";
    //std::cout << "\n";

}

//*****************************************************//

int main () {

  std::string string = "ororaoraoraazawarudaaararaoorroraoraara";
  std::string substring = "oraoraa";

  std::cout << "\nBMSearch\n";
  searchBM(string, substring);

  std::cout << "\nKMPSearch\n";
  searchKMP(string, substring);

  return 0;
}

/*
  std::vector<int> res = searchKMP(string, substring);

  //for(int i = 0; i < res.size(); i++)
  //  std::cout << res[i] << " ";

  std::cout << "Подстрока начинается с индексов: ";
  for(int i = 0; i < res.size(); i++)
    if (res[i] == substring.size())
      std::cout << i - substring.size() + 1 << "; ";

  std::cout << "\n";
*/

/*

std::vector<int> prefix_func(const std::string &s) {
	std::vector<int> p(s.length());

	int k = 0;
	p[0] = 0;
	for (int i = 1; i < s.length(); ++i) {
		while (k > 0 && s[k] != s[i]) {
			k = p[k - 1];
		}
		if (s[k] == s[i]) {
			++k;
		}
		p[i] = k;
	}
  puts("HERE");
  for(int i = 0; i < s.length(); i++)
    std::cout << p[i];
  std::cout << "\n";

	return p;
}

std::vector<int> gsVSearch(std::string substring) {

  typedef  std::unordered_map<int, int> TSufficsTable;
	TSufficsTable suffics_table;

  std::string t = substring;

  std::string rt(t.rbegin(), t.rend());
	std::vector<int> p = prefix_func(t), pr = prefix_func(rt);
	for (int i = 0; i < t.length() + 1; ++i) {
		suffics_table[i] = t.length() - p.back();
	}

	for (int i = 1; i < t.length(); ++i) {
		int j = pr[i];
		suffics_table[j] = std::min(suffics_table[j], i - pr[i] + 1);
	}

    for(int i = 0; i < t.length(); i++)
      std::cout << suffics_table[i] << " ";


  /*
  int len = substring.length();
  int* res = new int[len];

  res[0] = 1;

  for(int i = 1; i < len; i++) { //длина подстроки
    for(int j = 0; j < len-1-i; j++) { //поиск по подстрокам
      int k = 0;
      while(k <= i && substring[len-k] == substring[j+i-k]) {
        k++;
      }
      if(k == i+1) {

      }
    }
  }
  */

/*
  int len = substring.length();
  int* res = new int[len];

  std::string st1;
  std::string st2;

  res[0] = 1;
  for(int i = 1; i < len-1; i++) {
    for(int j = 0; j < len - i - 1 ; j++) {
      st1 = substring.substr(len-i-1, i+1);
      st2 = substring.substr(j, i+1);

      if(st1 == st2) {
        //std::cout<< "string< " <<st1 << " > and < " << st2 << " >\n";
        //std::cout <<len<< " and " << i << "\n";
        res[i] = len - i - 1;
      }
    }
  }

  for(int i = 0; i < len; i++)
    std::cout<< res[i] <<" ";
  puts("");

  std::vector<int> resV;

  return resV;
  */
