/*
ID: wanggen3
PROG: rockers
LANG: C++
*/
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;
ifstream fin("rockers.in");
ofstream fout("rockers.out");

int main()
{
    int N, T, M;
    int tape[21];
    fin >> N >> T >> M;
    for (int i = 0; i < N; ++i)fin >> tape[i + 1];
    int f[21][21][21];
    for (int i = 0; i <= T;++i)
    for (int j = 0; j <= N; ++j) f[0][i][j] = 0;
    for (int iM = 1; iM <= M; ++iM)
    {
        for (int iT = 0; iT <= T; ++iT)
        {
            for (int iN = 0; iN <= N; ++iN)
            {
                if (iN == 0) f[iM][iT][iN] = 0;
                else
                {
                    f[iM][iT][iN] = f[iM][iT][iN - 1];
                    f[iM][iT][iN] = max(f[iM][iT][iN], f[iM-1][T][iN]);
                    if (iT > 0)f[iM][iT][iN] = max(f[iM][iT][iN], f[iM][iT - 1][iN]);
                    if (iT-tape[iN] >= 0)f[iM][iT][iN] = max(f[iM][iT][iN], f[iM][iT-tape[iN]][iN-1]+1);
                }
            }
        }
    }
    fout << f[M][T][N] << endl;

    return 0;
}

