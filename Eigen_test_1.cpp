#include<iostream>
#include<Eigen/Dense>

using namespace Eigen;
using namespace std;
int main()
{
	MatrixXf a(4, 1);
	a = MatrixXf::Zero(4, 1);
	cout << "初始化为0" << endl << a << endl;
	a = MatrixXf::Ones(4, 1);
	cout << "初始化为1" << endl << a << endl;
	a.setZero();
	a << 1, 2, 3, 4;
	MatrixXf b(1, 4);
	b.setRandom();
	MatrixXf c(3, 3);
	c.setIdentity();
	cout << "置单位矩阵：" << endl << c << endl;
	c.setRandom();
	MatrixXf d = c;
	d = d.inverse();
	cout << "矩阵c：" << endl << c << endl;
	cout << "矩阵a：" << endl << a << endl;
	cout << "矩阵b：" << b << endl;
	cout << "访问a(0)：" << endl << a(0) << endl;
	cout << "矩阵相乘：" << endl << a*b << endl;
	cout << "矩阵数乘：" << endl << 2 * a << endl;
	cout << "矩阵c求逆d：" << endl << d << endl;
	cout << "逆矩阵回乘：" << endl << d*c << endl;
	cout << "逆矩阵d转置：" << endl << d.transpose() << endl;
	Vector3d v(1, 2, 3);
	Vector3d w(1, 0, 0);
	cout << "向量相加：" << endl << v + w << endl;
	getchar();
	system("pause");
	return 0;
}
