// XingTaiXue.h: interface for the XingTaiXue class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XINGTAIXUE_H__9FC95467_28F0_496A_81C0_725D58FA50D1__INCLUDED_)
#define AFX_XINGTAIXUE_H__9FC95467_28F0_496A_81C0_725D58FA50D1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class XingTaiXue  
{
public:
	XingTaiXue(int * source, int width, int height );
	virtual ~XingTaiXue();

public:
	// model: 模板
	void jisuan_fushi(int level);
	void FuShi( int * model, int size, bool white );
	// 判断两个图像相等
	bool XiangDeng( int * first, int * second );
	// 交集
	void JiaoJi( int * first, int * second, int * result);
	//填充
	void TianChong(int x, int y, int * model, int level, bool white);
	// 连通
	void LianTong();
	void dfs_liantong(int x, int y, int index, int top);
	//细化
	void XiHua();

	
public:
	int * GetResult() const{
		return _img;
	}
	int *getliantong(){
		return flag_liantong;
	}
private:
int *_oldimg;
	int *_img;
	int *_fanxiangimg;
	int *flag_liantong;
	int _width;
	int _height;
	
	
};

#endif // !defined(AFX_XINGTAIXUE_H__9FC95467_28F0_496A_81C0_725D58FA50D1__INCLUDED_)
