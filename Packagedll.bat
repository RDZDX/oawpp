"C:\Program Files\MRE SDK V3.0.00\tools\DllPackage.exe" "D:\MyGitHub\oawpp\oawpp.vcproj"
if %errorlevel% == 0 (
 echo postbuild OK.
  copy oawpp.vpp ..\..\..\MoDIS_VC9\WIN32FS\DRIVE_E\oawpp.vpp /y
exit 0
)else (
echo postbuild error
  echo error code: %errorlevel%
  exit 1
)

