const int N = 20 + 10;

int n;
double b[N], c[N][N];
//c：系数矩阵，b：常数； 二者一起构成增广矩阵

void Gaussian_Elimination()
{
	for(int i = 1; i <= n; i ++)
	{
		//找到x[i]的系数不为0的一个方程
		for(int j = i; j <= n; j ++) if(fabs(c[j][i]) > 1e-8)
		{
			for(int k = 1; k <= n; k ++) swap(c[i][k], c[j][k]);
			swap(b[i], b[j]);
		}
		//消去其他方程的x[i]的系数
		for(int j = 1; j <= n; j ++)
		{
			if(i == j) continue;
			double rate = c[j][i] / c[i][i];
			for(int k = i; k <= n; k ++) c[j][k] -= c[i][k] * rate;
			b[j] -= b[i] * rate;
		}
	}
}