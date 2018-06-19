#include <cstdio>
#include <cmath>
#undef _DEBUG
struct matrix{
	double m[3][3];
	matrix(){
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				m[i][j] = 0;
		for (int i = 0; i < 3; i++)
			m[i][i] = 1;
	}
	void zero(){
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				m[i][j] = 0;
	}
	const double *operator[] (const int p) const{
		return m[p];
	} 
	double *operator[] (const int p) {
		return m[p];
	} 
	static matrix Rotate(double angle){
		matrix x;
		x[0][0] = cos(angle);
		x[0][1] = -sin(angle);
		x[1][0] = sin(angle);
		x[1][1] = cos(angle);
		return x;
	}
	static matrix Move(double dx, double dy){
		matrix x;
		x[0][2] = dx;
		x[1][2] = dy;
		return x;
	}
	void print(){
		#ifdef _DEBUG
		for (int i = 0; i < 3; i++){
			for (int j = 0; j < 3; j++)
				printf("%lf ", m[i][j]);
			puts("");
		}
		#endif
	}
};
matrix operator *(const matrix &lhs, const matrix &rhs){
	matrix x;x.zero();
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			for (int k = 0; k < 3; k++){
				x[i][j] += lhs[i][k] * rhs[k][j];
			}
		}
	}
	return x;
}
const int MaxN = 50055;
const int MaxT = MaxN * 4 + 100;
matrix T[MaxT];
void change(int x, int cur, int L, int R, const matrix & val){
	//~ fprintf(stderr, "Change:%d %d %d %d\n", x, cur, L, R);
	if (L == x && R == x){
		T[cur] = val;
		return ;
	}
	int mid = (L + R) / 2;
	if (x <= mid)
		change(x, cur * 2, L, mid, val);
	else
		change(x, cur * 2 + 1, mid + 1, R, val);
	T[cur] = matrix();
	if (cur * 2 + 1 < MaxT)
		T[cur] = T[cur] * T[cur * 2 + 1];
	if (cur * 2 < MaxT)
		T[cur] = T[cur] * T[cur * 2];
}
matrix query(int l, int r, int cur, int L, int R){
	//~ fprintf(stderr, "Query:%d %d %d %d %d\n", l, r, cur, L, R);
	if (L == l && R == r){
		return T[cur];
	}
	int mid = (L + R) / 2;
	if (r <= mid)
		return query(l, r, cur * 2, L, mid);
	if (l > mid)
		return query(l, r, cur * 2 + 1, mid + 1, R);
	return query(mid + 1, r, cur * 2 + 1, mid + 1, R) * query(l, mid, cur * 2, L, mid);
}
int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	#ifdef _DEBUG
	matrix mat1;
	mat1[0][0] = 1, mat1[0][1] = -1, mat1[0][2] = 0, 
	mat1[1][0] = 1, mat1[1][1] = 1, mat1[1][2] = 0, 
	mat1[2][0] = 0, mat1[2][1] = 0, mat1[2][2] = 1;
	matrix mat2;
	mat2[0][0] = 1, mat2[0][1] = 0, mat2[0][2] = 5, 
	mat2[1][0] = 0, mat2[1][1] = 1, mat2[1][2] = 5, 
	mat2[2][0] = 0, mat2[2][1] = 0, mat2[2][2] = 1;
	matrix mat3 = mat2 * mat1;
	mat3.print();
	#endif
	for (int i = 1; i <= n; i++){
		int k;
		scanf("%d", &k);
		if (k == 1){
			double x, y;
			scanf("%lf%lf", &x, &y);
			matrix mat = matrix::Move(x, y);
			#ifdef _DEBUG
			mat.print();
			puts("=============");
			#endif
			change(i, 1, 1, n + 1, mat);
		}
		if (k == 2){
			double angle;
			scanf("%lf", &angle);
			angle=angle*2*acos(-1.0)/360;
			matrix mat = matrix::Rotate(angle);
			#ifdef _DEBUG
			mat.print();
			puts("=============");
			#endif
			change(i, 1, 1, n + 1, mat);
		}
	}

	for (int i = 1; i <= m; i++){
		int l, r;scanf("%d%d", &l, &r);
		matrix mat = query(l, r, 1, 1, n + 1);
		#ifdef _DEBUG
		mat.print();
		puts("=============");
		#endif
		double x = mat[0][2], y = mat[1][2];
		printf("%.3lf %.3lf\n", x, y);
	}
}
