#pragma once

template<class V,class E>
class GraphMatrix
{
public:
	GraphMatrix(V* vArray,const size_t &size)
		:_vArray(new V[size])
		,_size(size)
	{
		for(int i = 0;i < size;++i)
		{
			_vArray[i] = vArray[i];
		}
		_edges = new E*[_size];
		for(int i = 0;i < _size;++i)
		{
			_edges[i] = new E[_size];
			memset(_edges[i],0,sizeof(E)*_size);
		}
	}
	void AddEdge(const V &src,const V &dst,const E &w)
	{
		size_t srcIndex = GetIndex(src);
		size_t dstIndex = GetIndex(dst);

		_edges[srcIndex][dstIndex] = w;
		_edges[dstIndex][srcIndex] = w;
	}
	void Display()
	{
		//¶¥µã
		for(int i = 0;i < _size;++i)
		{
			cout<<i<<":"<<_vArray[i]<<"  ";
		}
		cout<<endl;
		//±ß
		for(int i = 0;i < _size;++i)
		{
			for(int j = 0;j < _size;++j)
			{
				cout<<_edges[i][j]<<"  ";
			}
			cout<<endl;
		}
	}
protected:
	size_t GetIndex(const V &v)
	{
		for(int i = 0;i < _size;++i)
		{
			if(_vArray[i] == v)
				return i;
		}
	}
private:
	V *_vArray;
	size_t _size;
	E **_edges;
};