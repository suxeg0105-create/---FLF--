
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

vector<vector<int>> Matrix(size_t x, size_t y)
{
    vector<vector<int>> matrix(y, vector<int>(x));
    for (int i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++)
        {
            matrix[i][j] = 1;
        }
    }

    return matrix;
}

double model_izing(vector<vector<int>>& x, double T, double J, double H)
{
    int x1 = rand() % x[0].size();
    int y1 = rand() % x[0].size();

    double summa = 0;

    for (int l = -1; l <= 1; l++)
    {
        for (int k = -1; k <= 1; k++)
        {
            if (x1 + l >= 0 && y1 + k >= 0 && x1 + l < x[0].size() && y1 + k < x[0].size())
            {
                if (abs(l) != abs(k))
                {
                    summa += x[x1 + l][y1 + k] * x[x1][y1];
                }
            }
        }
    }

    double mb = 0;
    for (int i = 0; i < x[0].size(); i++)
    {
        for (int j = 0; j < x[0].size(); j++)
        {
            mb += x[i][j];
        }
    }

    x[x1][y1] = (-1) * x[x1][y1];

    double summa2 = 0;

    for (int l = -1; l <= 1; l++)
    {
        for (int k = -1; k <= 1; k++)
        {
            if (x1 + l >= 0 && y1 + k >= 0 && x1 + l < x[0].size() && y1 + k < x[0].size())
            {
                if (abs(l) != abs(k))
                {
                    summa2 += x[x1 + l][y1 + k] * x[x1][y1];
                }
            }
        }
    }

    double mb_ = 0;
    for (int i = 0; i < x[0].size(); i++)
    {
        for (int j = 0; j < x[0].size(); j++)
        {
            mb_ += x[i][j];
        }
    }


    double dE = -J * (summa2 - summa) - 2 * H * x[x1][y1];

    if (dE < 0)
    {
        return mb_ / (x[0].size() * x[0].size());
    }
    else
    {
        double P = exp(-dE / T);
        double random = static_cast<double>(rand()) / RAND_MAX;
        if (random < P)
        {
            return  mb_ / (x[0].size() * x[0].size());
        }
        else
        {
            x[x1][y1] = (-1) * x[x1][y1];
            return  mb / (x[0].size() * x[0].size());
        }
    }


}

double Zm_(double T, int n, double H, double J, double z, double m_)
{
    int N = pow(n, 2);
    double l = z * J / (1 - 1 / N);
    double F = N * ((pow((m_ - H), 2) / (2 * l)) - T * log(2 * cosh(m_ / T)));
    return exp(-F / T);
}

double integrall(double T, int n, double H, double J, double z)
{
    double integrall = 0;
    double x = -10;
    while (x <= 10)
    {
        integrall += Zm_(T, n, H, J, z, x) * 0.001;
        x += 0.001;

    }

    return integrall;
}

double izing(double T, int n, double H, double J, double z)
{


    double Z_v = integrall(T, n, H + 1e-6, J, z);
    double Z_v_dv = integrall(T, n, H - 1e-6, J, z);

    return T / (n * n) * (log(Z_v) - log(Z_v_dv)) / (2 * 1e-6);


}

int main()
{
    double T;
    cout << "T: ";
    cin >> T;
    cout << "\n";

    int n;
    cout << "n: ";
    cin >> n;
    cout << "\n";

    double H;
    cout << "H: ";
    cin >> H;
    cout << "\n";

    double J;
    cout << "J: ";
    cin >> J;
    cout << "\n";

    double z;
    cout << "z: ";
    cin >> z;
    cout << "\n";

    double x = -1;

    double t = 0.0000001;
    double dt = 0.01;

    cout << Zm_(T, n, H, J, z, -1000);
    vector<vector<int>> izi = Matrix(n, n);



    while (t <= T or x > 1)
    {
 
        cout << t << " " << izing(t, n, H, J, z) << " " << abs(model_izing(izi, t, J, H)) << "\n";
        t += dt;
        x += 0.001;
    }


}
