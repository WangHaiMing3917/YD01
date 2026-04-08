cd ..

set FROMELF_PATH=D:\Keil_v5\ARM\ARMCC\bin\fromelf.exe




for /f "tokens=1 delims=." %%i in ('findstr /b "#include" .\product\product_name.h') do (set info=%%i)
set FILE_NAME=%info:*"=%


rd /s/q bin


%FROMELF_PATH% --bin -o  .\bin\%FILE_NAME%\%FILE_NAME%-1.bin  .\app\Objects\application.axf

.\app\MergeHex.exe .\boot\Objects\bootloader.hex .\app\Objects\application.hex .\bin\%FILE_NAME%\%FILE_NAME%.hex


setlocal enabledelayedexpansion



cd .\bin\%FILE_NAME%

for /f "delims=" %%i in ('dir  /a-d /b *.bin') do (
   echo %%~zi
   set /a Size= %%~zi
)


set /a  num2 = 128
set /a remainder = %Size% %% %num2%
echo The remainder is %remainder%

 set /a num = 0

if  %remainder% == 0 (

  set /a num  =%num2%-%remainder%

 ) else (

  set /a num  =%num2%-%remainder%


 )
echo The num is  %num%

set /a StartAddress=0
set /a num3=1
set /a FillStartAddress=!StartAddress!+!Size!

echo The FillStartAddress is  %FillStartAddress%

if  %remainder% == 0 (

  set /a FillendAddress =%FillStartAddress%

) else (

   set /a FillendAddress =!FillStartAddress!+!num!


)
  echo The FillendAddress is %FillendAddress%

set /a with=4

set /a LengthAddress=!FillendAddress!+!with!

set /a num1=1


set /a FillAddress=!Size!+!num1!

set /a num9=!FillAddress!+!num1!

echo The remainder is  %FillAddress%
echo The remainder is  %LengthAddress%
cd ..
cd ..
if  %remainder% == 0 (

  .\app\srec_cat.exe  .\bin\%FILE_NAME%\%FILE_NAME%-1.bin -Binary -crop 0 %Size%    -crc32-l-e %LengthAddress% -o .\bin\%FILE_NAME%\%FILE_NAME%-2.bin -Binary

  .\app\srec_cat.exe -generate %FillendAddress%  %LengthAddress% -constant-l-e %Size%  4  .\bin\%FILE_NAME%\%FILE_NAME%-2.bin -Binary -exclude %FillendAddress%  %LengthAddress%  -o .\app\tool\fw.bin -Binary


) else (
 .\app\srec_cat.exe  .\bin\%FILE_NAME%\%FILE_NAME%-1.bin -Binary -crop 0 %Size%    -crc32-l-e %LengthAddress% -o .\bin\%FILE_NAME%\%FILE_NAME%-2.bin -Binary

  .\app\srec_cat.exe -generate  %FillendAddress%  %LengthAddress% -constant-l-e %Size%  4  .\bin\%FILE_NAME%\%FILE_NAME%-2.bin -Binary -exclude %FillendAddress%  %LengthAddress% -o .\bin\%FILE_NAME%\%FILE_NAME%-3.bin -Binary


  .\app\srec_cat.exe -generate  %Size%  %FillAddress% -constant-l-e 0x1A  1  .\bin\%FILE_NAME%\%FILE_NAME%-3.bin -Binary -exclude %Size%  %FillAddress% -o .\bin\%FILE_NAME%\%FILE_NAME%-4.bin -Binary

  .\app\srec_cat.exe -generate %FillAddress%  %FillendAddress% -constant-l-e 0xFF  1  .\bin\%FILE_NAME%\%FILE_NAME%-4.bin -Binary -exclude %FillAddress%  %FillendAddress% -o .\app\tool\fw.bin -Binary

)
cd .\bin\%FILE_NAME%

 del %FILE_NAME%-1.bin
 del  %FILE_NAME%-2.bin
 del  %FILE_NAME%-3.bin
 del  %FILE_NAME%-4.bin
cd ..
cd ..
cd .\app\tool
crc.exe

