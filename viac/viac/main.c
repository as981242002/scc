/******************************************
*Author:Away
*Date:2016-11-8
*Function:测试模块单元代码
*******************************************/
#include"viac.h"

int main(const int argc, char** argv)
{
	Init();
	outtype = OUTPUT_EXE;
	
	subsystem = IMAGE_SUBSYSTEM_WINDOWS_CUI;
	int opind = ProcessCommand(argc, argv);
	if (opind == 0)
	{
		return 0;
	}
	int i;
	char* ext = NULL;
	for (i = 0; i < srcfiles.count; ++i)
	{
		
		filename = srcfiles.data[i]; 
		
		ext = GetFileText(filename);
		
		if (!strcmp(ext, "viac") || !strcmp(ext,"VIAC"))
			Compile(filename);
		else if (!strcmp(ext, "c") || !strcmp(ext, "C"))
			Compile(filename);
		else if (!strcmp(ext, "obj"))
		{
			LoadObjFile(filename);
		}
		else
			printf("编译失败，不支持的类型");
	}
	if (outtype == OUTPUT_OBJ)
	{
		if(outfile)
			WriteObj(outfile);
	}
	else
	{
		if (outfile);
			PeOutputFile(outfile);
	}
	Cleanup();
	
	printf("编译成功");
	return 1;
}
