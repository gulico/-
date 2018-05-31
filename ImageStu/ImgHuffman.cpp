// ImgHuffman.cpp: implementation of the ImgHuffman class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "imagestu.h"
#include "ImgHuffman.h"

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iostream>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CImgHuffman::CImgHuffman(int * grayData, int pixelCount, int grayLevel)
{
	//�Ҷ�����
	_grayData = grayData;
	//��������
	_pixelCount = pixelCount;
	//�Ҷȼ�
	_grayLevel = grayLevel;

	//��ʼ���Ҷ��ַ���
	InitGrayStr();

}

CImgHuffman::~CImgHuffman()
{
	//���鲢��Ԫ�أ��������Ӵ�С����
	delete [] _waitMergeVec;

	//�Ҷȵ�ͳ������
	delete [] _grayStat;
	//�Ҷ������С�����������ַ�����ʾ
	delete [] _codeTable;

}

void CImgHuffman::InitCodeTable(void)
{
	//�Ҷ������С�����������ַ�����ʾ
	_codeTable = new std::string[_grayLevel];
	for(int index = 0; index <= _grayLevel - 1; index++){
		_codeTable[index] = "";
	}
	TRACE("��ʼ��������");
}

void CImgHuffman::CalcGrayStat(void)
{
	//�Ҷȵ�ͳ������
	_grayStat = new int[_grayLevel];

	int index;
	//��ʼ��Ϊ0
	for(index = 0; index <= _grayLevel - 1; index++){
		_grayStat[index] = 0;
	}

	//ͳ��
	for(index = 0; index <= _pixelCount - 1; index++){
		int gray = _grayData[index];
		_grayStat[gray]++;
	}
}

void CImgHuffman::InitMergeVec(void)
{
	//���鲢��Ԫ�أ��������Ӵ�С����
	_waitMergeVec = new std::vector<CHuffmanMergeItem>[_grayLevel];
	for(int index = 0; index <= _grayLevel - 1; index++){
		if(_grayStat[index] != 0){
			CHuffmanMergeItem item;
			//�Ҷ�
			std::vector<int> gray;
			gray.push_back(index);
			item.set_grayVec(gray);
			//����
			item.set_num(_grayStat[index]);

			//���
			_waitMergeVec->push_back(item);
		}
	}

	//����
	std::stable_sort( _waitMergeVec->begin(), _waitMergeVec->end(), CElemCompare() );

}

void CImgHuffman::MakeCode(std::vector<int> * grayVec, bool flag)
{
	std::vector<int>::iterator begin = grayVec->begin();
	std::vector<int>::iterator end = grayVec->end();
	std::vector<int>::iterator iter;
	for(iter = begin; iter != end; iter++){
		int gray = (int)(*iter);
		std::string str = ( flag == true ? "1" : "0" );
		_codeTable[gray] = str + _codeTable[gray];
	}
}

void CImgHuffman::MergeItem(CHuffmanMergeItem & first, CHuffmanMergeItem & second, CHuffmanMergeItem & result)
{
	std::vector<int> newGrayVec(second.get_grayVec());

	std::vector<int> firstGray = first.get_grayVec();
	newGrayVec.insert( newGrayVec.begin(), firstGray.begin(), firstGray.end() );

	result.set_grayVec(newGrayVec);

	int num = first.get_num() + second.get_num();

	result.set_num(num);
}

void CImgHuffman::InsertItem(CHuffmanMergeItem & item)
{
	std::vector<CHuffmanMergeItem>::iterator begin = _waitMergeVec->begin();
	std::vector<CHuffmanMergeItem>::iterator end = _waitMergeVec->end();
	std::vector<CHuffmanMergeItem>::iterator iter;
	for(iter = begin; iter != end; iter++){

		CHuffmanMergeItem curItem = (CHuffmanMergeItem)(*iter);
		if(iter + 1 != end){
			CHuffmanMergeItem nextItem = (CHuffmanMergeItem)(*(iter+1));
			if(item.get_num() >= curItem.get_num() && item.get_num() <= nextItem.get_num()){
				TRACE("ǰһ��: %d����ǰ: %d����һ��: %d\n", item.get_num(),item.get_num(),nextItem.get_num());
				//�ҵ�λ�ã���ǰһ���󣨻���ȣ�������һ��С������ȣ�
				_waitMergeVec->insert(iter+1,item);
				return;
			}
		}
	}
	if(iter == end){
		//û���ҵ����ʵ�λ�ã���Ԫ�������ģ�����ĩβ
		_waitMergeVec->push_back(item);
	}
}

int CImgHuffman::CalcSumBitCount(void)
{
	int sum =0;
	for(int index = 0; index <= _grayLevel - 1; index++){
		sum += _codeTable[index].size() * _grayStat[index];
	}
	return sum;
}

float CImgHuffman::CalcAvgBitLen(void)
{
	return (float)_sumBitCount / _pixelCount;
}

float CImgHuffman::CalcEntropy(void)
{
	float sum = 0.0;
	for(int index = 0; index <= _grayLevel - 1; index++){
		float p = (float)_grayStat[ index ] / _pixelCount;
		if( p > 0 ){
			sum -= p * ( log10( p ) / log10( 2 ) );
		}
	}
	return sum;
}

void CImgHuffman::HuffmanCode(void)
{
	//�Ҷ�ͳ��
	CalcGrayStat();
	int index = 0;

	//��ʼ�����
	InitCodeTable();

	//��ʼ�����������
	InitMergeVec();
	//��������ַ���
	_mergeStr = "";

	//��ʼ����
	while( _waitMergeVec->size() >= 2){

		index++;
		//
		std::vector<CHuffmanMergeItem>::iterator firstIter = _waitMergeVec->begin();
		std::vector<CHuffmanMergeItem>::iterator secondIter = firstIter + 1;

		CHuffmanMergeItem firstItem = (CHuffmanMergeItem)(*firstIter);
		CHuffmanMergeItem secondItem = (CHuffmanMergeItem)(*secondIter);
		
		//
		//
		MakeCode(&firstItem.get_grayVec(), false);
		MakeCode(&secondItem.get_grayVec(), true);
		//
		TRACE("��һ����");
		PrintGrayVec(firstItem);
		TRACE("�ڶ�����");
		PrintGrayVec(secondItem);
		if(_waitMergeVec->size() == 2){
			TRACE("ʣ����������������ϲ�");
			return;
		}
		//
		CHuffmanMergeItem newItem;
		MergeItem(firstItem, secondItem, newItem);
		//
		MakeMergeStr(firstItem, secondItem, newItem, index);
		TRACE("��Ԫ�أ�");
		PrintGrayVec(newItem);


		//ɾ��������С��
		_waitMergeVec->erase(firstIter);
		firstIter = _waitMergeVec->begin();
		firstItem = (CHuffmanMergeItem)(*firstIter);
		_waitMergeVec->erase(firstIter);
		//

		//
		//
		//
		//����ĩβ������
		_waitMergeVec->push_back(newItem);
		std::stable_sort( _waitMergeVec->begin(), _waitMergeVec->end(),CElemCompare());

	}

	//
	_sumBitCount = CalcSumBitCount();
	TRACE("��λ��: %d\n", _sumBitCount);
	//
	_avgCodeLen = CalcAvgBitLen();
	TRACE("ƽ���볤: %f\n", _avgCodeLen);
	//
	_entropy = CalcEntropy();
	TRACE("��: %f\n", _entropy);
	//
	GeneCodeString();
}

void CImgHuffman::GeneCodeString()
{
	char * codeString = new char[ _sumBitCount + 1 ];
	TRACE("len = %d\n", _sumBitCount);
	int pos = 0;
	_codeString = "";

	CString str;
	str.Format("���뿪ʼ: %d", _sumBitCount);
	//
	//

	std::ostringstream buf;
	//
	//
	for(int index = 0; index <= 1000 - 1; index++){
		int gray = _grayData[index];
		/////
		_codeString += _codeTable[gray];
	}
	/////
	delete [] codeString;
}

void CImgHuffman::InitGrayStr()
{
	_grayStr = "";
	int num = 1000;
	for( int i = 0; i < num; ++i ){
		int gray = _grayData[ i ];
		CString curGray;
		curGray.Format("%d, ", gray);
		_grayStr += curGray;
	}
}

std::string * CImgHuffman::get_codeTable(void)
{
	return _codeTable;
}

std::string CImgHuffman::get_codeString(void)
{
	return _codeString;
}

std::vector< std::bitset<8> > * CImgHuffman::get_codeBitSet(void)
{
	return _codeBitSet;
}

float CImgHuffman::get_avgCodeLen(void)
{
	return _avgCodeLen;
}

int CImgHuffman::get_sumBitCount(void)
{
	return _sumBitCount;
}

float CImgHuffman::get_entropy(void)
{
	return _entropy;
}

//
int * CImgHuffman::get_GrayStat(void)
{
	return _grayStat;
}

//
std::string CImgHuffman::get_mergeStr()
{
	return _mergeStr;
}

//
void CImgHuffman::PrintGrayVec(CHuffmanMergeItem item)
{
	std::vector<int> grayVec = item.get_grayVec();
	std::vector<int>::iterator begin = grayVec.begin();
	std::vector<int>::iterator end = grayVec.end();
	std::vector<int>::iterator iter;
	for(iter = begin; iter != end; iter++)
	{
		int gray = (int)(*iter);
		TRACE("����: %d\n", item.get_num());
	}
}

//���úϲ�����
void CImgHuffman::MakeMergeStr(CHuffmanMergeItem item1, CHuffmanMergeItem item2, CHuffmanMergeItem newItem, int num)
{
	std::vector<int> grayVec = item1.get_grayVec();
	std::vector<int>::iterator begin = grayVec.begin();
	std::vector<int>::iterator end = grayVec.end();
	std::vector<int>::iterator iter;

	char str[1024];
	sprintf(str, "��%d��: \r\n", num);
	_mergeStr += str;
	for(iter = begin; iter != end; iter++)
	{
		int gray = (int)(*iter);
		TRACE("%d, ", gray);

		sprintf(str, "%d,", gray);
		_mergeStr += str;
	}
	sprintf(str,"����: %d;  ", item1.get_num());
	_mergeStr += str;
	//

	grayVec = item2.get_grayVec();
	begin = grayVec.begin();
	end = grayVec.end();
	iter;


	for(iter = begin; iter != end; iter++){
		int gray = (int)(*iter);
		TRACE("%d, ", gray);

		sprintf(str, "%d,", gray);
		_mergeStr += str;
	}
	sprintf(str,"����: %d;  ", item2.get_num());
	_mergeStr += str;

	_mergeStr += "�ϲ���: ";
	grayVec = newItem.get_grayVec();
	begin = grayVec.begin();
	end = grayVec.end();
	iter;


	sprintf(str,"����: %d\r\n  ", newItem.get_num());
	_mergeStr += str;
}
