/******************************************
*Author:Away
*Date:2016-11-8
*Function:异常模块单元代码
*******************************************/
#include"viac.h"

DynString tkstr;

 
void HandleException(const int stage, const int level, char* fmt, const va_list ap)
{
	char buf[1024];
	vsprintf_s(buf, 1024,fmt, ap);
	if (stage == STAGE_COMPILE)
	{
		if (level == LEVEL_WARNING)
			printf("%s(第%d行):编译警告：%s\n:", filename, linenum, buf);
		else
		{
			printf("%s(第%d行:编译错误:%s\n", filename, linenum, buf);
			exit(-1);
		}
	}
	else
	{
		printf("链接错误:%s\n", buf);
		exit(-1);
	}
}

void Warning(const char* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	HandleException(STAGE_COMPILE, LEVEL_WARNING, fmt, ap);
	va_end(ap);
}

void Error(const char* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	HandleException(STAGE_COMPILE, LEVEL_ERROR, fmt, ap);
	va_end(ap);
}
 
void Skip( const int c)
{
	if (token != c)
	{
		Error("缺少'%s'", GetTkstr(c));
	}
	GetToken();
}
/*******************************************
*函数功能:提示缺少的成分
*msg:需要什么语法成分
*******************************************/
void Expect(const char* msg)
{
	Error("缺少%s", msg);
}

void LinkError(const char* fmt,...)
{
	va_list ap;
	va_start(ap, fmt);
	HandleException(STAGE_LINK, LEVEL_ERROR, fmt, ap);
	va_end(ap);
}
