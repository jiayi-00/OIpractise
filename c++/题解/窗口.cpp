#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
    const char* CLASS_NAME = "MyWindowClass";
    WNDCLASSA wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);  // 背景改为黑色
    wc.style = CS_HREDRAW | CS_VREDRAW;
    
    if (!RegisterClassA(&wc)){
        MessageBoxA(NULL, "Window Registration Failed!", "Error", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    
    HWND hwnd = CreateWindowExA(
        0,
        CLASS_NAME,
        "励志窗口",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,  
        500, 200,  // 窗口调大一点方便显示大字体
        NULL,
        NULL,
        hInstance,
        NULL
    );
    
    if (hwnd == NULL){
        MessageBoxA(NULL, "Window Creation Failed!", "Error", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
    switch (uMsg){
    case WM_PAINT:{
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        
        // 创建大字体
        HFONT hFont = CreateFontA(
            48,    // 字体高度（像素），数字越大字越大
            0,     // 字体宽度（0表示自动）
            0,     // 倾斜角度
            0,     // 倾斜角度
            FW_BOLD, // 粗体（FW_BOLD表示加粗）
            FALSE, // 斜体
            FALSE, // 下划线
            FALSE, // 删除线
            DEFAULT_CHARSET,
            OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS,
            DEFAULT_QUALITY,
            DEFAULT_PITCH | FF_DONTCARE,
            "Microsoft YaHei"  // 字体名称（雅黑支持中文好）
        );
        
        // 选择字体到设备上下文
        HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);
        
        // 设置文字颜色为白色
        SetTextColor(hdc, RGB(255, 255, 255));
        // 设置背景模式为透明（这样背景就显示黑色了）
        SetBkMode(hdc, TRANSPARENT);
        
        RECT rect;
        GetClientRect(hwnd, &rect);
        DrawTextA(hdc, "处在低谷，怎么走都是向上", -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        
        // 恢复旧字体并删除创建的字体
        SelectObject(hdc, hOldFont);
        DeleteObject(hFont);
        
        EndPaint(hwnd, &ps);
        }
        return 0;
    case WM_CLOSE:
        DestroyWindow(hwnd);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProcA(hwnd, uMsg, wParam, lParam);
    }
}
