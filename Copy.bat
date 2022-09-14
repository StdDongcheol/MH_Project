cd..
cd..
xcopy .\GameEngine\Bin\*.* .\Client3D\Bin\ /s /d /y /exclude:exclude.txt
xcopy .\GameEngine\Bin\*.* .\Engine\Bin\ /s /d /y /exclude:exclude.txt
xcopy .\GameEngine\Bin\*.* .\Editor\Bin\ /s /d /y /exclude:exclude.txt

xcopy .\GameEngine\Include\*.h .\Engine\Include\ /s /d /y
xcopy .\GameEngine\Include\*.inl .\Engine\Include\ /s /d /y
xcopy .\GameEngine\Include\*.hpp .\Engine\Include\ /s /d /y

xcopy .\Editor\Bin\Data\*.* .\Client3D\Bin\Data\ /s /d /y /exclude:exclude.txt