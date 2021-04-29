#include <windows.h>
#include <functional>
#include <iostream>

#define RED RGB(255,0,0)
#define BLUE RGB(0,0,255)
#define YELLOW RGB(255,255,0)
#define WHITE RGB(255,255,255)
using namespace std;

HDC crntDC;
int GAP = 70;

RECT Rect(int left, int top, int right, int bottom) {
    RECT i;
    i.left = left;
    i.top = top;
    i.right = right;
    i.bottom = bottom;
    return i;
}

RECT nextRect(RECT i) {
    i.left += i.left + GAP;
    i.right += GAP;
    return i;
}

void SetCurrentDC(HDC j) {
    crntDC = j;
}

void setCurrentBrush(HDC p,COLORREF i) {
    HBRUSH pen = CreateSolidBrush(i);
    SelectObject(p, pen);
}

void setCurrentPen(HDC p, COLORREF i) {
    HPEN pen = CreatePen(PS_SOLID, 5,i);
    SelectObject(p, pen);
}

void DrawRectangle(HDC h,RECT j,COLORREF k) {
    setCurrentBrush(h, k);
    setCurrentPen(h, k);
    Rectangle(h, j.left, j.top, j.right, j.bottom);
}

void DrawLine(int left,int top,COLORREF x,HDC a) {
    setCurrentPen(a, x);
    LineTo(a, left , top);
}

void DrawCircle(HDC a,int radius,int x,int y) {
    Ellipse(a, x, y, y + radius, x + radius);
}

void DrawAxes(int x, int y, HDC cont) {
    DrawLine(0, y, WHITE, cont);
    DrawLine(y, x, WHITE, cont);
}

struct LINE {
    int x1;
    int x2;
    int y1;
    int y2;
    LINE() : x1(0), y1(0) {}
    LINE(int a, int b, int c, int d) {
        x1 = a;
        y1 = b;
        x2 = c;
        y2 = d;
    }
};

POINT* SetPoint(POINT* j,int x,int y) {
    j->x = x;
    j->y = y;
    return j;
}

void SetPointCol(POINT* j,COLORREF k) {
    SetPixel(crntDC, j->x, j->y, k);
}

POINT* Point(int a,int b) {
    POINT* k = new POINT;
    k->x = a;
    k->y = b;
    return k;
}

LINE* Lines(int size) {
    LINE* i = new LINE[size];
    return i;
}

LINE* Lines(int size, LINE p[]) {
    LINE* i = new LINE[size];
    for (int a = 0; a < size; a++) {
        i[a] = p[a];
    }
    return i;
}

bool DrawPath(HDC h,LINE* lines,int nrlines) {
    try {
        for (int a = 0; a < nrlines; a++) {
            MoveToEx(h, lines[nrlines].x1, lines[nrlines].y1, NULL);
            LineTo(h, lines[nrlines].x2, lines[nrlines].y2);
        }
        return true;
    }catch (...) {
        return false;
    }
}

void DrawFunction(function<int(int)> a){
    
}

int main(void)
{
    HWND console_handle = GetConsoleWindow();
    HDC device_context = GetDC(console_handle);

    DrawAxes(205, 205, device_context);
    DrawRectangle(device_context, Rect(40, 20, 90, 100) , WHITE);

    crntDC = device_context;
    SetPointCol(Point(200, 100), RED);

    ReleaseDC(console_handle, device_context);
    std::cin.ignore();
    return 0;
}
