# 2023—面向对象编程—大作业

## 基于Visual Studio和OpenGL的几何建模及功能实现



### 在Visual Studio 2022上的配置方法（附常见问题解决方法）

#### 配置方法

##### 1.Visual Studio 2022新建项目，选择MFC Application

![1684473699638](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\1684473699638.png)

##### 2.创建MFC项目

自行修改项目名称和项目地址，之后创建项目修改MFC应用程序类型。

修改以下几处选项，修改后完成即成功创建MFC项目。

![1684474079386](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\1684474079386.png)

创建好项目后我们可以运行项目，看到有窗口出现即创建成功。这里建议运行时切换到Win32平台（即x86），这是因为这样建立的程序能够保证在32位和64位系统上都能正常运行。

![1684474224962](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\1684474224962.png)

##### 3.链接OpenGL静态库

选择项目-属性-链接器，确保修改实在Debug模式Win32平台下进行的，在输入处附加如下依赖项：

```
opengl32.lib;glu32.lib;glaux.lib
```

![1684474440788](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\1684474440788.png)

在CXXXView.h处添加头文件

```c++
#include <gl/GL.h>
#include <gl/GLU.h>
```

![1684474744148](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\1684474744148.png)

然后我们运行文件，出现以下报错：

![1684475460890](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\1684475460890.png)

暂时不清楚解决方法，我们先把glaux.lib从依赖库中去除。再次运行，运行成功。

##### 4.修改部分文件以适配OpenGL

首先在CXXXView.h头文件的类内添加部分变量和函数的定义：

```c++
protected:
	CDC* m_pDC;
	HGLRC m_hRC;
	void DrawScene();
	BOOL SetupPixelFormat(PIXELFORMATDESCRIPTOR* pPFD = 0);
```

![1684478308843](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\1684478308843.png)

视图选择类视图，右键CXXXView，选择属性-消息，选择到相应的消息处，增加OnCreate、OnDestroy、OnSize、OnEraseBkgnd、PreCreateWindow、OnDraw重载函数，根据PPT上的内容修改对应函数（在对应的cpp文件中）。

![1684477867993](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\1684477867993.png)

![1684477912123](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\1684477912123.png)

##### ·在OnCreate()中添加：

```c++
	m_pDC = new CClientDC(this);	// get device context
	if (m_pDC == NULL)
	{
		::AfxMessageBox(_T("fail to get device context"));
		return FALSE;
	}

	if (!SetupPixelFormat())	// setup pixel format
	{
		::AfxMessageBox(_T("SetupPixelFormat failed"));
		return FALSE;
	}

	// get rendering context
	if ((m_hRC = wglCreateContext(m_pDC->GetSafeHdc())) == 0)
	{
		::AfxMessageBox(_T("wglCreateContext failed"));
		return FALSE;
	}

	// make current rendering context
	if (wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC) == FALSE)
	{
		::AfxMessageBox(_T("wglMakeCurrent failed"));
		return FALSE;
    }
```

##### ·在OnDestroy()中添加：

```c++
	if (wglMakeCurrent(0, 0) == FALSE)
		::AfxMessageBox(_T("wglMakeCurrent failed"));
	if (m_hRC && (wglDeleteContext(m_hRC) == FALSE))
		::AfxMessageBox(_T("sglDeleteContext failed"));
	if (m_pDC)
		delete m_pDC;
```

##### ·在OnEraseBkgnd()中修改return：

```c++
	//return CView::OnEraseBkgnd(pDC);
	return TRUE;
```

##### ·在OnSize()中添加：

```c++
	glViewport(0, 0, cx, cy);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluOrtho2D(0, 500, 0, 500);
```

##### ·重写PreCreateWindow()函数：

```c++
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
```

##### ·重写OnDraw()函数：

```c++
	DrawScene();
```

##### ·定义SetupPixelFormat()：

```c++
BOOL CMFCApplicationView::SetupPixelFormat(PIXELFORMATDESCRIPTOR* pPFD)
{
	PIXELFORMATDESCRIPTOR pfd = {
		sizeof( PIXELFORMATDESCRIPTOR ),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL,
		PFD_TYPE_RGBA,
		24,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 
		0, 0, 0, 0, 
		16,
		0, 0, 
		PFD_MAIN_PLANE,
		0, 0, 0, 0 };

	int pixelformat;
	
	PIXELFORMATDESCRIPTOR* pPFDtoUse;

	pPFDtoUse = (0 == pPFD)? &pfd : pPFD;
	
	if ( 0 == ( pixelformat = ::ChoosePixelFormat( m_pDC->GetSafeHdc(), pPFDtoUse ) ) ) 
	{
		::AfxMessageBox( _T("ChoosePixelFormat failed") );
		return FALSE;
	}

	if ( FALSE == ::SetPixelFormat( m_pDC->GetSafeHdc(), pixelformat, pPFDtoUse ) ) 
	{
		::AfxMessageBox( _T("SetPixelFormat failed") );
		return FALSE;
	}

	return TRUE;
}

```

##### ·在DrawScene()中编写你想要实现的代码（以下代码为例）：

```c++
void CMFCApplicationView::DrawScene()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);
		glVertex2f(100, 100);
		glVertex2f(100, 200);
		glVertex2f(200, 200);
		glVertex2f(200, 100);
	glEnd();

	glFlush();
}
```



运行程序，成功！

![1684480399286](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\1684480399286.png)





#### 常见问题及解决措施

##### 1.新建项目时找不到MFC Application

打开Visual Studio Installer，选择修改，在“使用C++的桌面开发”部分勾选相应的MFC选项。

![1684473899619](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\1684473899619.png)



##### 2.修改程序时会在有AfxMessageBox处出现如下报错，这可能是因为使用的VS版本过高，修改对应内容为（详见上述程序段）

```
AfxMessageBox(_T("请输入名称！"));
```

![1684473487879](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\1684473487879.png)

