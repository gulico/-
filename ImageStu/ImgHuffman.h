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
	/*���캯��*/
	CImgHuffman(int * grayData, int pixelCount, int grayLevel);
	/*��������*/
	~CImgHuffman();

	/*�Ҷ�ͳ��*/
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

	//����ӿ�
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
	//��ʼ�������
	void InitCodeTable(void);
	//����Ҷ�����
	void PrintGrayVec(CHuffmanMergeItem item);
	//���úϲ�����
	void MakeMergeStr(CHuffmanMergeItem item1, CHuffmanMergeItem item2, CHuffmanMergeItem newItem, int num);

private:

	//�Ҷ�����
	int * _grayData;
	//��������
	int _pixelCount;
	//ͼ��Ҷȼ�����
	int _grayLevel;

	//���鲢��Ԫ�أ���Ԫ�ش�С��������
	std::vector<CHuffmanMergeItem> * _waitMergeVec;

	//�Ҷȵ�ͳ������
	int * _grayStat;
	//�Ҷ������С�����������ַ�����ʾ
	std::string * _codeTable;
	//����λ�����ַ�����ʽ
	std::string _codeString;
	//����λ����������λ����
	std::vector< std::bitset<8> > * _codeBitSet;
	//ƽ���볤����BitΪ��λ��
	float _avgCodeLen;
	//������λ��
	int _sumBitCount;
	//��
	float _entropy;
	//�������
	std::string _mergeStr;
	//�Ҷ��ַ������Զ��Ÿ�����
	std::string _grayStr;

	//�����Ԫ�ش�С�ıȽϣ���������
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
