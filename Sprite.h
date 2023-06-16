#pragma once

#include <Windows.h>
#include <atlImage.h>

#include "Util.h"
#include "Point.h"


class Sprite {
public:
	CImage source;
	Point position;
	//double rotate;	// ȸ��
	//Point offset;		// �̹��� ��ġ ����
	bool flip_x;		// ������
	bool flip_y;
	double size_per;		// 0�̸� �Ⱥ���, 100�϶� �⺻������
	bool fix_ratio;

public:
	Sprite(const tstring& file_name);

public:
	void draw(const HDC& hdc, const RECT& draw_area) const;
};