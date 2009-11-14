#pragma once
#include "afxtempl.h"

typedef const vector< int> const_intvect;
typedef vector<int> intvect;
typedef vector< CString> CStringvect;
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
class CKeepMap :
	public CMap<KEY,ARG_KEY,VALUE, ARG_VALUE>
{
public:
	CKeepMap();
	~CKeepMap(void);
VALUE& operator[](ARG_KEY key);

 VALUE& operator[](UINT keynum);
VALUE& operator[](ARG_KEY key) const;

VALUE& operator[](UINT keynum) const;
void SetAt(ARG_KEY key, ARG_VALUE newValue);
	void GetNextAssoc(POSITION& rNextPosition,KEY& rKey, VALUE& rValue) const;
void Dumpout() ;

BOOL Lookup(ARG_KEY key) const;
using CMap<KEY,ARG_KEY,VALUE,ARG_VALUE>::Lookup;
void RemoveAll();
BOOL RemoveKey(ARG_KEY key);
void sort();
void sortvalue();
//template<class _Pr>	void sort(_Pr _Pred)
//{
//	std::sort(m_mapstr.begin(),m_mapstr.end(),_Pred);
//}
	vector<KEY> m_mapstr;
#ifdef _DEBUG
vector<VALUE> m_mapvalue;
#endif
};
template<class KEY,class ARG_KEY, class VALUE, class ARG_VALUE>
struct NatStrLessvalue: public binary_function<const KEY &, const KEY &, bool>
{
NatStrLessvalue(CKeepMap<KEY,ARG_KEY,VALUE,ARG_VALUE> *rumap)
{
tempmap=rumap;
}
  bool operator()(const KEY &ps1,const KEY &ps2) const
  {
    return (*tempmap)[ps1] < (*tempmap)[ps2];
  }
private:
CKeepMap<KEY,ARG_KEY,VALUE,ARG_VALUE> *tempmap;
};
struct findexit
{
	findexit(const CStringvect &upp,const_intvect &intt,int posfirst=0):updated(upp),comint(intt),firstpos(posfirst)
	{

	}
	bool operator() (const CStringvect &zz) const
	{
		for(vector<int>::const_iterator it=comint.begin(); it!=comint.end();it++)
		{
			//if(!=)
			if(lstrcmpi(zz.at(*it),updated.at(*it-firstpos))!=0)
				return false;
		}

		return true;
	}
private:
	const CStringvect updated;
	vector<int> comint;
	int firstpos;
};
inline int isshuzi(const TCHAR *buf,int shuzitype=0) 

	{	int dotnum=0;
	if(lstrlen(buf)==0)
		return 1;

	for(UINT i=0;i<lstrlen(buf);i++)
	{
		if(*(buf+i)=='.')
			dotnum++;
		else
		{
			if(*(buf+i)<'0'||*(buf+i)>'9')
			{
				if(*(buf+i)!='-'||i>0||lstrlen(buf)==1)
					return 0;
			}
		}
	}

	if(shuzitype==0&&dotnum!=0)
		return 0;
	if(shuzitype==1&&dotnum>1)
		return 0;

	return 1;


	}

struct NatureStrLess :public binary_function<const CString &, const CString &, bool>
{
	bool operator()(const CString &ps1,const CString &ps2) const
	{
		return ps1.GetLength()<ps2.GetLength();
	//	if(isshuzi(ps1)&&isshuzi(ps2))
	//	//if(_ttoi(ps1)>0&&_ttoi(ps1)>0)
	//return _ttoi(ps1)<_ttoi(ps2);

	//	int minnum=min(ps1.GetLength(),ps2.GetLength());
	//	int simlen=-1;
	//	for(int i=0;i<minnum;i++)
	//	{
	//		if(ps1[i]!=ps2[i])
	//		{
	//			simlen=i;
	//			break;
	//		}

	//	}


	//	if(simlen!=-1&&(ps1[simlen]>='0'&&ps1[simlen]<='9')&&(ps2[simlen]>='0'&&ps2[simlen]<='9'))//如果第simlen个开始两者都是数字，用数字大小相比，而不仅仅是字符串比较
	//	{

	//		return _ttoi((LPCTSTR)ps1+simlen)<_ttoi((LPCTSTR)ps2+simlen);

	//	}
	//	else
	//		return ps1 < ps2;
	//
}
};
template<class KEY>
struct NatStrLess: public binary_function<const KEY &, const KEY &, bool>
{
  bool operator()(const KEY &ps1,const KEY &ps2) const
  {
    return ps1 < ps2;
  }
};
template<>
struct NatStrLess<CString>: NatureStrLess
{
  
};
template<typename T>
struct Table_dataSort :public binary_function<const vector<T> &, const vector<T> &, bool>
{
Table_dataSort(int xuhao,BOOL IsLess)
{m_IsLess=IsLess;
	m_xuhao=xuhao;

}
	bool operator()(const vector<T> &ps1,const vector<T> &ps2) const
	{
		if(m_IsLess)
return NatStrLess<T>()(ps1.at(m_xuhao),ps2.at(m_xuhao));
		else
return NatStrLess<T>()(ps2.at(m_xuhao),ps1.at(m_xuhao));
	}

private:
	BOOL m_IsLess;
	int m_xuhao;
};
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
void CKeepMap<KEY,ARG_KEY,VALUE,ARG_VALUE>::sort()
{
	std::sort(m_mapstr.begin(),m_mapstr.end(),NatStrLess<KEY>());
 }
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
void CKeepMap<KEY,ARG_KEY,VALUE,ARG_VALUE>::sortvalue()
{
	std::sort(m_mapstr.begin(),m_mapstr.end(),NatStrLessvalue<KEY,ARG_KEY,VALUE,ARG_VALUE>(this));
}

template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
CKeepMap<KEY,ARG_KEY,VALUE,ARG_VALUE>::CKeepMap(void):CMap<KEY,ARG_KEY,VALUE,ARG_VALUE>()
{
InitHashTable(10000);
}
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
CKeepMap<KEY,ARG_KEY,VALUE,ARG_VALUE>::~CKeepMap(void)
{

}

template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
void CKeepMap<KEY,ARG_KEY,VALUE,ARG_VALUE>::SetAt(ARG_KEY key, ARG_VALUE newValue)
{
(*this)[key]=newValue;
}
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
BOOL CKeepMap<KEY,ARG_KEY,VALUE,ARG_VALUE>::Lookup(ARG_KEY key) const
{
VALUE tempvalue;
return CMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::Lookup(key,tempvalue);

}
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
 VALUE& CKeepMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::operator[](ARG_KEY key)
{
	
	VALUE tempvalue;
if(!Lookup(key,tempvalue))
m_mapstr.push_back(key);


return CMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::operator[](key);
}
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
VALUE& CKeepMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::operator[](ARG_KEY key) const
{

UINT nHashBucket, nHashValue;
CAssoc* pAssoc;
	pAssoc = GetAssocAt(key, nHashBucket, nHashValue);

	if (pAssoc == NULL)
	{
		static VALUE tempnull;
		return tempnull;  // not in map
	}

	return pAssoc->value;


}
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
 VALUE& CKeepMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::operator[](UINT keynum)
{
	


return CMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::operator[](m_mapstr[keynum]);
}
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
VALUE& CKeepMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::operator[](UINT keynum) const
{
	
UINT nHashBucket, nHashValue;
CAssoc* pAssoc;
	pAssoc = GetAssocAt(m_mapstr[keynum], nHashBucket, nHashValue);
	
	return pAssoc->value;

//return CMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::operator[] (m_mapstr[keynum]);
}
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
void CKeepMap<KEY,ARG_KEY,VALUE,ARG_VALUE>::RemoveAll()
{
m_mapstr.clear();
CMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::RemoveAll();
}
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
BOOL CKeepMap<KEY,ARG_KEY,VALUE,ARG_VALUE>::RemoveKey(ARG_KEY key)
{
	m_mapstr.erase(std::remove(m_mapstr.begin(),m_mapstr.end(),key),m_mapstr.end()); 
return CMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::RemoveKey(key);

}
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
void CKeepMap<KEY,ARG_KEY,VALUE,ARG_VALUE>::Dumpout()
{
#ifdef _DEBUG
m_mapvalue.clear();
for(int i=0;i<m_mapstr.size();i++)
{
m_mapvalue.push_back((*this)[(UINT)i]);
}
#endif
}
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
void CKeepMap<KEY,ARG_KEY,VALUE,ARG_VALUE>::GetNextAssoc(POSITION& rNextPosition,KEY& rKey, VALUE& rValue) const
{

	ENSURE(rNextPosition != NULL); 
	if(rNextPosition==BEFORE_START_POSITION)
rNextPosition=0;

	
vector<KEY>::const_iterator it=m_mapstr.begin()+(int)rNextPosition;//&*rNextPosition;
	rKey=*it;
Lookup(rKey,rValue);

if(it!=(m_mapstr.end()-1))
	{

rNextPosition++;
	}
	else
	{
	rNextPosition=NULL;
	}


}
typedef CKeepMap<CString,LPCTSTR,CString,LPCTSTR> CStr2KeepMap;