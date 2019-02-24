

#include <tchar.h>
#include <windows.h>
#include <string>
#include <iostream>
#include <math.h>
using namespace std;

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

HWND textstatic,texteditz1,buttoncalculate;

/*  Make the class name into a global variable  */

TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain (HINSTANCE hThisInstance,
                 HINSTANCE hPrevInstance,
                 LPSTR lpszArgument,
                 int nCmdShow)
{
HWND hwnd;               /* This is the handle for our window */
MSG messages;            /* Here messages to the application are saved */
WNDCLASSEX wincl;        /* Data structure for the windowclass */

/* The Window structure */
wincl.hInstance = hThisInstance;
wincl.lpszClassName = szClassName;
wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
wincl.cbSize = sizeof (WNDCLASSEX);

/* Use default icon and mouse-pointer */
wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
wincl.lpszMenuName = NULL;                 /* No menu */
wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
wincl.cbWndExtra = 0;                      /* structure or the window instance */
/* Use Windows's default colour as the background of the window */
wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

/* Register the window class, and if it fails quit the program */
if (!RegisterClassEx (&wincl))
    return 0;

/* The class is registered, let's create the program*/
hwnd = CreateWindowEx (
       0,                   /* Extended possibilites for variation */
       szClassName,         /* Classname */
       _T("Code::Blocks Template Windows App"),       /* Title Text */
       WS_OVERLAPPEDWINDOW, /* default window */
       CW_USEDEFAULT,       /* Windows decides the position */
       CW_USEDEFAULT,       /* where the window ends up on the screen */
       300,                 /* The programs width */
       200,                 /* and height in pixels */
       HWND_DESKTOP,        /* The window is a child-window to desktop */
       NULL,                /* No menu */
       hThisInstance,       /* Program Instance handler */
       NULL                 /* No Window Creation data */
       );

/* Make the window visible on the screen */
ShowWindow (hwnd, nCmdShow);

/* Run the message loop. It will run until GetMessage() returns 0 */
while (GetMessage (&messages, NULL, 0, 0))
{
    /* Translate virtual-key messages into character messages */
    TranslateMessage(&messages);
    /* Send message to WindowProcedure */
    DispatchMessage(&messages);
}

/* The program return-value is 0 - The value that PostQuitMessage() gave */
return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

switch (message)                  /* handle the messages */
{
    case WM_CREATE:
    texteditz1 = CreateWindow ("EDIT","",
                               WS_VISIBLE | WS_CHILD | WS_BORDER,
                               30,50,45,20,
                               hwnd, (HMENU) 4,NULL,NULL);


    textstatic = CreateWindow ("STATIC",
                                "Enter a value: ",
                                WS_VISIBLE | WS_CHILD | WS_BORDER,
                                30,30,150,20,
                                hwnd, NULL, NULL, NULL);


    buttoncalculate = CreateWindow ("BUTTON",
                                    "Check",
                                    WS_VISIBLE | WS_CHILD,
                                    100, 100, 70, 15,
                                    hwnd, (HMENU) 1, NULL, NULL);


    break;

    case WM_COMMAND:

        switch (LOWORD(wParam))
        {
            case 1:
                {
                int len = GetWindowTextLengthW(texteditz1) + 1;
                wchar_t text[len];

                GetWindowTextW(texteditz1, text, len);
                int value=0;

                if(len==1)
                {
                    ::MessageBox(hwnd,"You didn't enter anything!","Error",MB_ICONWARNING);
                    return 0;
                }

                for(int i=0;i<len-1;i++)
                {
                    //std::cout<<text[i]-48;
                    if(text[i]-'0'<0 ||text[i]-'0'>9)
                    {
                        ::MessageBox(hwnd,"Not a number entered!","Error",MB_ICONWARNING);
                        return 0;
                    }
                    value=value*10+(text[i]-'0');
                }
                //if((len-1)%2==1)value++;
                //std::cout<<" "<<value;

                if(value>100)
                {
                    ::MessageBox(hwnd, "Value is too big", "Message",MB_OK);
                }
                else if(value==100)
                {
                    ::MessageBox(hwnd, "Value is just right", "Message",MB_OK);
                }
                else
                {
                    ::MessageBox(hwnd, "Value is too small", "Message",MB_OK);
                }

                }
                break;


        }
    break;
    case WM_DESTROY:
        PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
        break;
    default:                      /* for messages that we don't deal with */
        return DefWindowProc (hwnd, message, wParam, lParam);

}


return 0;
}
