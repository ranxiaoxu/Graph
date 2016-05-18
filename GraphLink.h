#pragma once

#include<queue>
using namespace std;

template<class V,class E>
struct EdgeNode{
	EdgeNode<V,E>* _next;
	E _w;                     //Ȩֵ
	size_t _srcIndex;         //Դ������±�
	size_t _dstIndex;         //Ŀ�궥����±�

	EdgeNode(const E &w,size_t srcIndex,size_t dstIndex)
		:_w(w)
		,_next(NULL)
		,_srcIndex(srcIndex)
		,_dstIndex(dstIndex)
	{}
};
template<class V,class E>
class GraphLink{
	typedef EdgeNode<V,E> Edge;
public:
	GraphLink(V* vArray,const size_t size,bool isDict = false)
		:_size(size)
		,_vArray(new V[size])
		,_isDict(isDict)
	{
		for(int i = 0;i < _size;++i)
		{
			_vArray[i] = vArray[i];
		}
		_edges = new Edge*[size]();
	}
	void AddEdge(const size_t &src,const size_t &dst,const E &w)
	{
		size_t srcIndex = GetIndex(src);
		size_t dstIndex = GetIndex(dst);
		if(_isDict == true)
		{
			_AddEdge(srcIndex,dstIndex,w);
		}
		else
		{
			_AddEdge(srcIndex,dstIndex,w);
			_AddEdge(dstIndex,srcIndex,w);
		}
	}
	void DFS(size_t srcIndex)    //��ȱ�������
	{
		bool *Visited = new bool[_size];
		memset(Visited,0,sizeof(bool)*_size);
		_DFS(srcIndex,Visited);
		delete[] Visited;
	}
	void BFS(size_t srcIndex)    //��ȱ�������
	{
		bool *Visited = new bool[_size];
		memset(Visited,0,sizeof(bool)*_size);

		queue<size_t> q;
		q.push(srcIndex);

		while(!q.empty())
		{
			size_t cur = q.front();
			cout<<cur<<" ";
			q.pop();
			Visited[cur] = true;

			Edge *begin = _edges[cur];
			while(begin)
			{
				if(Visited[begin->_dstIndex] == false)
				{
					q.push(begin->_dstIndex);
					Visited[begin->_dstIndex] = true;
				}
				begin = begin->_next;
			}
		}

		delete[] Visited;
	}
	void Display()
	{
		//��ӡ����
		for(int i = 0;i < _size;++i)
		{
			cout<<i<<":"<<_vArray[i]<<" ";
		}
		cout<<endl;
		//��ӡ�ٽӱ�
		for(int i = 0;i < _size;++i)
		{
			Edge *cur = _edges[i];
			cout<<_vArray[i]<<"["<<i<<"]"<<"->";
			while(cur)
			{
				cout<<cur->_w<<"["<<cur->_dstIndex<<"]"<<"->";
				cur = cur->_next;
			}
			cout<<"NULL"<<endl;
		}
	}
protected:
	void _DFS(size_t srcIndex,bool *visited)
	{
		cout<<srcIndex<<" ";
		visited[srcIndex] = true;

		Edge *cur = _edges[srcIndex];

		while(cur)
		{
			if(visited[cur->_dstIndex] == false)
				_DFS(cur->_dstIndex,visited);
			
			cur = cur->_next;
		}
		cout<<endl;
	}
	void _AddEdge(const size_t &src,const size_t &dst,const E &w)
	{
		Edge *tmp = new Edge(w,src,dst);
		//����ͷ��
		tmp->_next = _edges[src];
		_edges[src] = tmp;
	}
	size_t GetIndex(const V &v)
	{
		for(int i = 0;i < _size;++i)
		{
			if(_vArray[i] == v)
				return i;
		}
	}
private:
	V *_vArray;     //���㼯��
	size_t _size;   //����ĸ���
    Edge **_edges;  //�߼���
	bool _isDict;   //��־������ͼ��������ͼ
};