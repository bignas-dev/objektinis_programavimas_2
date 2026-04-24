; Inno Setup Script for Objektinis Programavimas v3.0
; Sukuria setup.exe diegimui į Windows sistemą

[Setup]
AppId={{A1B2C3D4-E5F6-G7H8-I9J0-K1L2M3N4O5P6}
AppName=Objektinis Programavimas
AppVersion=3.0
AppPublisher=VU
AppContact=student@vu.lt
DefaultDirName={pf}\VU\Vardenis-Pavardenis
DefaultGroupName=VU\Vardenis-Pavardenis
PrivilegesRequired=admin
LicenseFile=
InfoBeforeFile=
OutputDir=installer
OutputBaseFilename=setup
SetupIconFile=
Compression=lzma
SolidCompression=yes
WizardStyle=modern

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "lithuanian"; MessagesFile: "compiler:Languages\Lithuanian.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked
Name: "quicklaunchicon"; Description: "{cm:CreateQuickLaunchIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked; OnlyBelowVersion: 6.1; Check: not IsAdminInstallMode

[Files]
Source: "main_vector.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "tests\*"; DestDir: "{app}\tests"; Flags: ignoreversion recursesubdirs
Source: "test_10000.txt"; DestDir: "{app}"; Flags: ignoreversion
Source: "test_100000.txt"; DestDir: "{app}"; Flags: ignoreversion
Source: "README.md"; DestDir: "{app}"; Flags: ignoreversion
Source: "VECTOR_DOCS.md"; DestDir: "{app}"; Flags: ignoreversion
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{group}\Objektinis Programavimas"; Filename: "{app}\main_vector.exe"
Name: "{group}\{cm:UninstallProgram,Objektinis Programavimas}"; Filename: "{uninstallexe}"
Name: "{autodesktop}\Objektinis Programavimas"; Filename: "{app}\main_vector.exe"; Tasks: desktopicon
Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\Objektinis Programavimas"; Filename: "{app}\main_vector.exe"; Tasks: quicklaunchicon

[Run]
Filename: "{app}\main_vector.exe"; Description: "{cm:LaunchProgram,Objektinis Programavimas}"; Flags: nowait postinstall skipifsilent

[Code]
function InitializeSetup(): Boolean;
begin
  Result := True;
end;

procedure CurStepChanged(CurStep: TSetupStep);
begin
  if CurStep = ssPostInstall then
  begin
    // Post-installation tasks
  end;
end;
