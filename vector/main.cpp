#include "Vector.h"
#include "Matrix.h"

void line()
{
  std::cout << "\n===========================================================================\n\n";
}

int main()
{
  TVector<int> vec1;
  TVector<int> vec2(5, 2);
  TVector<int> vec3(vec2);
  vec1.Resize(5);
  std::cin >> vec2;
  for (int i = 0; i < vec1.GetLength(); i++)
	vec1[i] = rand() % 50 + 10;
  line();

  vec3 = vec1 + vec2;
  std::cout << "vec3 = vec1 + vec2 =\n" << vec1 << "+  " << vec2 << "=  " << vec3 << "\n";
  line();
  vec3 = vec1 - vec2;
  std::cout << "vec3 = vec1 - vec2 =\n" << vec1 << "-  " << vec2 << "=  " << vec3 << "\n";
  line();
  vec1 = vec2 * vec3;
  std::cout << "vec1 = vec2 * vec3 =\n" << vec2 << "*  " << vec3 << "=  " << vec1 << "\n";
  line();
  vec3 = vec1 / vec2;
  std::cout << "vec3 = vec1 / vec2 =\n" << vec1 << "/  " << vec2 << "=  " << vec3 << "\n";
  line();

  TMatrix<int> Matrix1;
  TMatrix<int> Matrix2(2, 3);
  TMatrix<int> Matrix3(Matrix2);
  TMatrix<int> Matrix4(4, 5);
  int** indexes;
  std::cin >> Matrix2;
  std::cout << Matrix2;
  line();

  for (int i = 0; i < Matrix3.GetWidth(); i++)
	for (int j = 0; j < Matrix3.GetLength(); j++)
	  Matrix3[i][j] = rand();
  std::cout << "Matrix3 = \n" << Matrix3;
  line();

  Matrix1 = Matrix2 + Matrix3;
  std::cout << "Matrix1 = Matrix2 + Matrix3 =\n"
	<< Matrix2 << "\n + \n\n" << Matrix3 << "\n = \n\n" << Matrix1 << "\n";
  line();

  Matrix2 = Matrix3 - Matrix1;
  std::cout << "Matrix2 = Matrix3 - Matrix1 =\n"
	<< Matrix3 << "\n - \n\n" << Matrix1 << "\n = \n\n" << Matrix2 << "\n";
  line();

  Matrix1.Resize(2, 2);
  Matrix2.Resize(2, 2);
  Matrix3.Resize(2, 2);
  Matrix3 = Matrix2 * Matrix1;
  std::cout << "Matrix3 = Matrix2 * Matrix1 =\n"
	<< Matrix2 << "\n * \n\n" << Matrix1 << "\n = \n\n" << Matrix3 << "\n";
  line();
  
  for (int i = 0; i < Matrix4.GetWidth(); i++)
	for (int j = 0; j < Matrix4.GetLength(); j++)
	  Matrix4[i][j] = rand() % 50;
  vec1 = Matrix4 * vec2;
  std::cout << "vec1 = Matrix4 * vec2 = \n" << Matrix4 << "\n *\n\n" << vec2 << "\n\n =\n\n" << vec1;
  line();

  //std::cout << "Matrix2 = \n" << Matrix2;
  //indexes = Matrix2.FindValues(-24);
  //Matrix2.PrintFindValues(indexes);
  
  vec1.QuickSort();
  std::cout << "vec1 = " << vec1;
  line();

  TMatrix<int> Matrix5(vec2.GetLength(), Matrix4.GetLength());
  Matrix4.Resize(1, Matrix4.GetLength());
  Matrix5 = vec2 * Matrix4;
  std::cout << "Matrix5 = vec2 * Matrix4 = \n" << vec2 << "\n *\n\n" << Matrix4
	<< "\n\n = \n\n" << Matrix5;
  line();

  return 0;
}