/*
 * matcher.h
 */

#ifndef MATCHER_H_
#define MATCHER_H_

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

class matcher
{
public:
	matcher() {};
	static int searchBruteF(string pattern, string text)
	{
		int n = pattern.length();
		int m = text.length();

		for (int i = 0; i <= n - m; i++) {
			int j = 0;
			while (j < m && pattern[i + j] == text[j]) {
				j++;
			}
			if (j == m) 
				return i;
		}
		return -1;
	}

	static void pre_kmp(string pattern, vector<int> & prefix)
	{
		int m = pattern.length();
		prefix[0] = -1;
		int k = -1;
		for (int q = 1; q<m; q++) {
			while (k>-1 && pattern[k + 1] != pattern[q])
				k = prefix[k];
			if (pattern[k + 1] == pattern[q]) k = k + 1;
			prefix[q] = k;
		}
	}


	static int numStringMatching(string filename, string toSearch)
	{
		ifstream fich(filename.c_str());
		if (!fich)
		{
			cout << "Erro a abrir ficheiro de leitura\n"; return 0;
		}

		string line1;
		int num = 0;

		while (!fich.eof()) {
			getline(fich, line1);
			num += kmp(line1, toSearch);
		}
		fich.close();
		return num;
	}


	static int editDistance(string pattern, string text)
	{
		int n = text.length();
		vector<int> d(n + 1);
		int old, neww;
		for (int j = 0; j <= n; j++)
			d[j] = j;
		int m = pattern.length();
		for (int i = 1; i <= m; i++) {
			old = d[0];
			d[0] = i;
			for (int j = 1; j <= n; j++) {
				if (pattern[i - 1] == text[j - 1]) neww = old;
				else {
					neww = min(old, d[j]);
					neww = min(neww, d[j - 1]);
					neww = neww + 1;
				}
				old = d[j];
				d[j] = neww;
			}
		}
		return d[n];
	}

	static int numApproximateStringMatching(string text, string toSearch)
	{
		return editDistance(toSearch, text);
	}

	static int kmp(string text, string pattern)
	{
		int num = 0;
		int m = pattern.length();
		vector<int> prefix(m);
		pre_kmp(pattern, prefix);

		int n = text.length();

		int q = -1;
		for (int i = 0; i<n; i++) {
			while (q>-1 && pattern[q + 1] != text[i])
				q = prefix[q];
			if (pattern[q + 1] == text[i])
				q++;
			if (q == m - 1) {
				num++;
				q = prefix[q];
			}
		}
		return num;
	}

};


#endif /* MATCHER_H_ */