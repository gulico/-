// ImgHuffman.h: interface for the ImgHuffman class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMGHUFFMAN_H__B939DACA_3FAE_41B8_823A_0816FA939E85__INCLUDED_)
#define AFX_IMGHUFFMAN_H__B939DACA_3FAE_41B8_823A_0816FA939E85__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "HuffmanMergeItem.h"
#include <vector>
#include <BITSET>
#include <string>

class CImgHuffman  
{
public:
	/*构造函数*/
	CImgHuffman(int * grayData, int pixelCount, int grayLevel);
	/*析构函数*/
	~CImgHuffman();

	/*灰度统计*/
	void CalcGrayStat(void);

	void InitMergeVec(void);
	void MakeCode(std::vector<int> * grayVec, bool flag);

	void MergeItem(CHuffmanMergeItem & first, CHuffmanMergeItem & second, CHuffmanMergeItem & result);

	void InsertItem(CHuffmanMergeItem & item);

	int CalcSumBitCount(void);

	float CalcAvgBitLen(void);

	float CalcEntropy(void);

	void HuffmanCode(void);

	void GeneCodeString();

	void InitGrayStr();

	//对外接口
	//
	std::string * get_codeTable(void);
	//
	std::string get_codeString(void);
	//
	std::vector< std::bitset<8> > * get_codeBitSet(void);
	//
	float get_avgCodeLen(void);
	//
	int get_sumBitCount(void);
	//
	int * get_GrayStat(void);
	//
	float get_entropy(void);
	//
	std::string get_mergeStr();

	//
	std::string GetGrayStr() const{
		return _grayStr;
	}

protected:
private:
	//初始化代码表
	void InitCodeTable(void);
	//输出灰度向量
	void PrintGrayVec(CHuffmanMergeItem item);
	//设置合并过程
	void MakeMergeStr(CHuffmanMergeItem item1, CHuffmanMergeItem item2, CHuffmanMergeItem newItem, int num);

private:

	//灰度数据
	int * _grayData;
	//像素数量
	int _pixelCount;
	//图像灰度级数量
	int _grayLevel;

	//待归并的元素（按元素从小到大排序）
	std::vector<CHuffmanMergeItem> * _waitMergeVec;

	//灰度的统计数量
	int * _grayStat;
	//灰度码表，从小到大排序，用字符串表示
	std::string * _codeTable;
	//编码位流，字符串格式
	std::string _codeString;
	//编码位流（二进制位流）
	std::vector< std::bitset<8> > * _codeBitSet;
	//平均码长（以Bit为单位）
	float _avgCodeLen;
	//编码总位数
	int _sumBitCount;
	//熵
	float _entropy;
	//分组过程
	std::string _mergeStr;
	//灰度字符串（以逗号隔开）
	std::string _grayStr;

	//编码表元素大小的比较（用于排序）
	class CElemCompare{
	public:
		bool operator()( CHuffmanMergeItem elem1, CHuffmanMergeItem elem2){
			return elem1.get_num() < elem2.get_num();
		};
	};
	


//	ImgHuffman();
//	virtual ~ImgHuffman();

};

#endif // !defined(AFX_IMGHUFFMAN_H__B939DACA_3FAE_41B8_823A_0816FA939E85__INCLUDED_)
