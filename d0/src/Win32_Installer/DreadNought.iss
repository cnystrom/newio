; -- Dreadnought.iss --

[Setup]
AppName=Dreadnought Browser
AppVerName=Dreadnought Browser version 0.12 066 RC10 080105
DefaultDirName={pf}\NewIO\DreadNought
DefaultGroupName=NewIO
UninstallDisplayIcon={app}\d0.ico
SetupIconFile=d0.ico
LicenseFile=lgpl.txt

[Files]
Source: d0.exe; DestDir: {app}; Flags: ignoreversion
Source: d0.ico; DestDir: {app}; Flags: ignoreversion

Source: dlls\jpeg.dll; DestDir: {sys}; Flags: restartreplace uninsneveruninstall sharedfile
Source: dlls\libpng12-0.dll; DestDir: {sys}; Flags: restartreplace uninsneveruninstall sharedfile
Source: dlls\libtiff-3.dll; DestDir: {sys}; Flags: restartreplace uninsneveruninstall sharedfile
Source: dlls\SDL.dll; DestDir: {sys}; Flags: restartreplace uninsneveruninstall sharedfile
Source: dlls\SDL_image.dll; DestDir: {sys}; Flags: restartreplace uninsneveruninstall sharedfile
Source: dlls\SDL_mixer.dll; DestDir: {sys}; Flags: restartreplace uninsneveruninstall sharedfile
Source: dlls\SDL_ttf.dll; DestDir: {sys}; Flags: restartreplace uninsneveruninstall sharedfile
Source: dlls\zlib1.dll; DestDir: {sys}; Flags: restartreplace uninsneveruninstall sharedfile
Source: dlls\avformat-51.dll; DestDir: {sys}; Flags: restartreplace uninsneveruninstall sharedfile
Source: dlls\avcodec-51.dll; DestDir: {sys}; Flags: restartreplace uninsneveruninstall sharedfile
Source: dlls\avutil-49.dll; DestDir: {sys}; Flags: restartreplace uninsneveruninstall sharedfile
Source: dlls\libogg-0.dll; DestDir: {sys}; Flags: restartreplace uninsneveruninstall sharedfile
Source: dlls\libvorbis-0.dll; DestDir: {sys}; Flags: restartreplace uninsneveruninstall sharedfile
Source: dlls\libvorbisfile-3.dll; DestDir: {sys}; Flags: restartreplace uninsneveruninstall sharedfile
Source: dlls\smpeg.dll; DestDir: {sys}; Flags: restartreplace uninsneveruninstall sharedfile
Source: dlls\libfreetype-6.dll; DestDir: {sys}; Flags: restartreplace uninsneveruninstall sharedfile 

Source: fonts\FreeMono.ttf; DestDir: {%HOME}\.d0\fonts
Source: fonts\FreeMonoBold.ttf; DestDir: {%HOME}\.d0\fonts
Source: fonts\FreeMonoBoldOblique.ttf; DestDir: {%HOME}\.d0\fonts
Source: fonts\FreeMonoOblique.ttf; DestDir: {%HOME}\.d0\fonts
Source: fonts\FreeSans.ttf; DestDir: {%HOME}\.d0\fonts
Source: fonts\FreeSansBold.ttf; DestDir: {%HOME}\.d0\fonts
Source: fonts\FreeSansBoldOblique.ttf; DestDir: {%HOME}\.d0\fonts
Source: fonts\FreeSansOblique.ttf; DestDir: {%HOME}\.d0\fonts; Flags: ignoreversion
Source: fonts\FreeSerif.ttf; DestDir: {%HOME}\.d0\fonts
Source: fonts\FreeSerifBold.ttf; DestDir: {%HOME}\.d0\fonts
Source: fonts\FreeSerifBoldItalic.ttf; DestDir: {%HOME}\.d0\fonts
Source: fonts\FreeSerifItalic.ttf; DestDir: {%HOME}\.d0\fonts

Source: newio.wav; DestDir: {%HOME}\.d0

Source: homenv.dll; Flags: dontcopy

[Code]
// add HOME to the path
procedure DllFunc();
external '_PutHomeInEnv@0@files:homenv.dll stdcall';
function InitializeSetup(): Boolean;
begin
  DllFunc();
  Result := True;
end;
procedure InitializeWizard();
begin
  // allow installation without requiring user to accept licence
  WizardForm.LicenseAcceptedRadio.Checked := True;
  WizardForm.LicenseAcceptedRadio.Visible := False;
  WizardForm.LicenseLabel1.Visible := False;
  WizardForm.LicenseNotAcceptedRadio.Visible := False;
  WizardForm.LicenseMemo.Top := WizardForm.LicenseLabel1.Top;
  WizardForm.LicenseMemo.Height :=
  WizardForm.LicenseNotAcceptedRadio.Top +
  WizardForm.LicenseNotAcceptedRadio.Height -
  WizardForm.LicenseMemo.Top - 5;
end;


[Icons]
Name: {group}\DreadNought Browser; Filename: {app}\d0.exe; IconFilename: {app}\d0.ico

; NOTE: Most apps do not need registry entries to be pre-created. If you
; don't know what the registry is or if you need to use it, then chances are
; you don't need a [Registry] section.
