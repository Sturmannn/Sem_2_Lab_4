#pragma once
#include "Vector.h"

template <class T>
class TMatrix : public TVector<TVector<T>>
{
public:
  TMatrix();
  TMatrix(int l);
  TMatrix(int w, int l);
  TMatrix(const TMatrix<T>& p);
  ~TMatrix();

  TMatrix<T> operator + (const TMatrix<T>& p);
  TMatrix<T> operator - (const TMatrix<T>& p);
  TMatrix<T> operator * (const TMatrix<T>& p);
  TVector<T> operator * (TVector<T>& p);
  TMatrix<T>& operator = (const TMatrix<T>& p);

  bool operator == (const TMatrix<T>& p);
  bool operator != (const TMatrix<T>& p);

  TVector<T>& operator [] (const int i);
  int GetWidth();
  void SetWidth(int w);
  void Resize(int w, int l);
  int FindValue(T p);
  int** FindValues(T p);
  int GetIndex();
  void PrintFindValues(int**& p);


  template <class T>
  friend std::ostream& operator << (std::ostream& B, TMatrix<T>& A);
  template <class T>
  friend std::istream& operator >> (std::istream& B, TMatrix<T>& A);

protected:
  int width;
  int index;
};

template<class T>
inline TMatrix<T>::TMatrix()
{
  index = 0;
  width = 0;
  this->data = nullptr;
}

template<class T>
inline TMatrix<T>::TMatrix(int l) : TMatrix()
{
  if (l < 0) throw "Error";
  this->length = l;
  width = l;
  this->data = new TVector<T>[width];
  for (int i = 0; i < length; i++)
	this->data[i].Resize(length);
}

template<class T>
inline TMatrix<T>::TMatrix(int w, int l) : TMatrix()
{
  if (l < 0 || w < 0) throw "Error";
  this->length = l;
  width = w;
  this->data = new TVector<T>[width];
  for (int i = 0; i < width; i++)
	this->data[i].Resize(length);
}

template<class T>
inline TMatrix<T>::TMatrix(const TMatrix<T>& p)
{
  this->length = p.length;
  width = p.width;
  index = p.index;
  if (p.data == nullptr) this->data = nullptr;
  else
  {
	this->data = new TVector<T>[width];
	for (int i = 0; i < width; i++)
	  this->data[i] = p.data[i];
  }
}

template<class T>
inline TMatrix<T>::~TMatrix()
{
  if (data != nullptr)
  {
	delete[] data;
	data = nullptr;
  }
  width = 0;
  index = 0;
}

template<class T>
inline TMatrix<T> TMatrix<T>::operator+(const TMatrix<T>& p)
{
  if (this->length != p.length || width != p.width) throw "Error";
  TMatrix<T> res(*this);
  for (int i = 0; i < width; i++)
	res.data[i] = this->data[i] + p.data[i];
  return res;
}

template<class T>
inline TMatrix<T> TMatrix<T>::operator-(const TMatrix<T>& p)
{
  if (this->length != p.length || width != p.width) throw "Error";
  TMatrix<T> res(width, this->length);
  for (int i = 0; i < width; i++)
	res.data[i] = this->data[i] - p.data[i];
  return res;
}

template<class T>
inline TMatrix<T> TMatrix<T>::operator*(const TMatrix<T>& p)
{
  if (this->length != p.width) throw "Error";
  TMatrix<T> res(width, p.length);
  for (int i = 0; i < width; i++)
  {
	for (int j = 0; j < p.length; j++)
	{
	  res[i][j] = 0;
	  for (int k = 0; k < length; k++)
	  {
		res[i][j] += this->data[i][k] * p.data[k][j];
	  }
	}
  }
  return res;
}

template<class T>
inline TVector<T> TMatrix<T>::operator*(TVector<T>& p)
{
  if (this->length != p.GetLength()) throw "Error";
  TVector<T> res(width, 0);
  for (int i = 0; i < width; i++)
  {
	for (int j = 0; j < this->length; j++)
	{
	  res[i] += this->data[i][j] * p[j];
	}
  }
  return res;
}

template<class T>
inline TMatrix<T>& TMatrix<T>::operator=(const TMatrix<T>& p)
{
  if (this == &p) return *this;
  this->length = p.length;
  this->width = p.width;
  if (this->data != nullptr) delete[] data;
  if (p.data == nullptr) data = nullptr;
  else data = new TVector<T>[p.width];
  for (int i = 0; i < p.width; i++)
	this->data[i] = p.data[i];
  return *this;
}

template<class T>
inline bool TMatrix<T>::operator==(const TMatrix<T>& p)
{
  if (this->length != p.length || width != p.width) return false;
  for (int i = 0; i < width; i++)
	for (int j = 0; j < this->length; j++)
	  if (this->data[i][j] != this->p.data[i][j]) return false;
  return true;
}

template<class T>
inline bool TMatrix<T>::operator!=(const TMatrix<T>& p)
{
  if (this->length != p.length || width != p.width) return true;
  for (int i = 0; i < width; i++)
	for (int j = 0; j < this->length; j++)
	  if (this->data[i][j] != this->p.data[i][j]) return true;
  return false;
}

template<class T>
inline TVector<T>& TMatrix<T>::operator[](const int i)
{
  if (i < 0 || i >= this->width) throw "Error";
  return this->data[i];
}

template<class T>
inline int TMatrix<T>::GetWidth()
{
  return width;
}

template<class T>
inline void TMatrix<T>::SetWidth(int w)
{
  this->Resize(this->length, w);
}

template<class T>
inline void TMatrix<T>::Resize(int w, int l)
{
  TVector<T>* data1 = new TVector<T>[w];
  if (this->data != nullptr)
  {
	int minW, minL;
	if (width > w) minW = w;
	else minW = width;
	if (this->length > l) minL = l;
	else minL = this->length;
	for (int i = 0; i < minW; i++)
	{
	  data1[i].Resize(l);
	  for (int j = 0; j < minL; j++)
		data1[i][j] = this->data[i][j];
	}
	delete[] data;
  }
  this->data = data1;
  this->length = l;
  width = w;
}

template<class T>
inline int TMatrix<T>::FindValue(T p)
{
  int count = 0;
  for (int i = 0; i < width; i++)
  {
	for (int j = 0; j < this->length; j++)
	{
	  if (this->data[i][j] == p) count++;
	}
  }
  return count;
}

template<class T>
inline int** TMatrix<T>::FindValues(T p)
{
  int count = 0;
  for (int i = 0; i < width; i++)
  {
	for (int j = 0; j < length; j++)
	{
	  if (data[i][j] == p) count++;
	}
  }
  int** res;
  res = new int* [count];
  int ind = 0;
  for (int i = 0; i < width; i++)
  {
	for (int j = 0; j < length; j++)
	{
	  if (data[i][j] == p)
	  {
		res[ind] = new int[2];
		res[ind][0] = i;
		res[ind][1] = j;
		ind++;
	  }
	}
  }
  index = ind;
  return res;
}

template<class T>
inline int TMatrix<T>::GetIndex()
{
  return index;
}

template<class T>
inline void TMatrix<T>::PrintFindValues(int**& p)
{

  for (int i = 0; i < GetIndex(); i++)
  {
	for (int j = 0; j < 2; j++)
	{
	  std::cout << p[i][j] << "\t";
	}
	std::cout << std::endl;
  }
}

template<class T>
inline std::ostream& operator<<(std::ostream& B, TMatrix<T>& A)
{
  for (int i = 0; i < A.width; i++)
  {
	for (int j = 0; j < A.length; j++)
	  B << A[i][j] << "\t";
	B << "\n";
  }
  return B;
}

template<class T>
inline std::istream& operator>>(std::istream& B, TMatrix<T>& A)
{
  std::cout << "Enter " << A.width * A.length << " values of Matrix: \n";
  for (int i = 0; i < A.width; i++)
	for (int j = 0; j < A.length; j++)
	  B >> A.data[i][j];
  return B;
}

template <class T>
TMatrix<T> operator *(TVector<T>& vector, TMatrix<T>& matrix)
{
  if (matrix.GetWidth() != 1) throw "Error";
  TMatrix<T> res(vector.GetLength(), matrix.GetLength());
  for (int i = 0; i < vector.GetLength(); i++)
  {
	for (int j = 0; j < matrix.GetLength(); j++)
	{
	  res[i][j] = vector[i] * matrix[0][j];
	}
  }
  return res;
};