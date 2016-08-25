; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "MetCOM"
#define MyAppVersion "1.0"
#define MyAppPublisher "ZixLink"
#define MyAppURL "http://zixlink.com"
#define MyAppExeName "MetCOM.exe"

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{04E5BD0E-E8EF-4965-AFD9-DA2C7AB676EE}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={pf}\{#MyAppName}
SetupIconFile=icon.ico
DisableProgramGroupPage=yes
OutputBaseFilename=MetCOMSetup
Compression=lzma
SolidCompression=yes
ShowLanguageDialog=yes

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "hebrew"; MessagesFile: "compiler:Languages\Hebrew.isl"
Name: "russian"; MessagesFile: "compiler:Languages\Russian.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "package\MetCOM.exe";              DestDir: "{app}"; Flags: ignoreversion
Source: "package\*";                       DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "icon.ico";                        DestDir: "{app}"; Flags: ignoreversion

[Icons]
Name: "{commonprograms}\{#MyAppPublisher}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{commonprograms}\{#MyAppPublisher}\Uninstall"; Filename: "{uninstallexe}"
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

[Code]

