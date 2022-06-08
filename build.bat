@echo off

set DeleteAll=1

set Common=-nologo -Gm- -GR- -EHa- -Zo -Oi -FC -Z7 -WX -W4 -wd4668 -wd4100 -wd4820 -wd4365 -wd4774 -wd4710 -wd5045 -wd4191 -wd4189 -wd4061 -wd4996 -wd4464 -wd4201 -wd5220 -wd5219 -wd4310 -wd4065

COPY ak_math.h ak_math.cpp
cl %Common% -DAK_MATH_IMPLEMENTATION -DAK_MATH_TESTS ak_math.cpp -link -opt:ref -incremental:no -out:ak_math.exe

ak_math.exe

IF %DeleteAll% == 1 (
	DEL ak_math.cpp
	DEL ak_math.exe
	DEL ak_math.obj
	DEL ak_math.pdb
)