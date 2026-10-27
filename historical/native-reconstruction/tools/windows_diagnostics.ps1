# SPDX-License-Identifier: GPL-3.0-or-later
# Read-only source inventory. Does not launch, patch or configure the game.
# Run with Windows PowerShell 5.1 or later. See docs/WINDOWS_TESTING.md.
[CmdletBinding()]
param(
    [string]$Install = 'D:\Games\RA2',
    [Parameter(Mandatory = $true)][string]$OutputFile
)
Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'

function Assert-NoReparseAncestor([string]$Path) {
    $cursor = [IO.Path]::GetFullPath($Path)
    while ($cursor) {
        if (Test-Path -LiteralPath $cursor) {
            $entry = Get-Item -LiteralPath $cursor -Force
            if ($entry.Attributes -band [IO.FileAttributes]::ReparsePoint) {
                throw "Reparse point refused: $cursor"
            }
        }
        $parent = [IO.Path]::GetDirectoryName($cursor)
        if ($parent -eq $cursor) { break }
        $cursor = $parent
    }
}

function Get-PEHeader([string]$Path) {
    $stream = [IO.File]::Open($Path, 'Open', 'Read', 'ReadWrite')
    $reader = [IO.BinaryReader]::new($stream)
    try {
        if ($stream.Length -lt 64 -or $reader.ReadUInt16() -ne 0x5A4D) { return $null }
        $stream.Position = 0x3C
        $offset = $reader.ReadUInt32()
        if ($offset -gt $stream.Length - 24) { return $null }
        $stream.Position = $offset
        if ($reader.ReadUInt32() -ne 0x4550) { return $null }
        $machine = $reader.ReadUInt16()
        $sections = $reader.ReadUInt16()
        $timestamp = $reader.ReadUInt32()
        return [ordered]@{ machine = ('0x{0:X4}' -f $machine); sections = $sections; timestamp = $timestamp }
    } finally { $reader.Dispose() }
}

$installRoot = [IO.Path]::GetFullPath($Install).TrimEnd('\', '/')
$reportPath = [IO.Path]::GetFullPath($OutputFile)
if ($installRoot -eq [IO.Path]::GetPathRoot([IO.Path]::GetFullPath($Install)).TrimEnd('\', '/')) {
    throw 'Installation must be a directory below the volume root'
}
Assert-NoReparseAncestor $installRoot
Assert-NoReparseAncestor $reportPath
if (-not (Test-Path -LiteralPath $installRoot -PathType Container)) { throw 'Installation directory missing' }
if ($reportPath.Equals($installRoot, [StringComparison]::OrdinalIgnoreCase) -or
    $reportPath.StartsWith($installRoot + '\', [StringComparison]::OrdinalIgnoreCase)) {
    throw 'Report must be outside the source installation'
}
if ($reportPath -notmatch '(?i)[\\/](private|build)[\\/]') { throw 'Use a private/ or build/ report directory' }
if (Test-Path -LiteralPath $reportPath) { throw 'Refusing to overwrite an existing report' }

$files = @()
foreach ($file in Get-ChildItem -LiteralPath $installRoot -File -Force | Sort-Object Name) {
    if ($file.Attributes -band [IO.FileAttributes]::ReparsePoint) { throw "Source reparse point refused: $($file.Name)" }
    $beforeLength = $file.Length
    $beforeTime = $file.LastWriteTimeUtc
    $hash = (Get-FileHash -LiteralPath $file.FullName -Algorithm SHA256).Hash.ToLowerInvariant()
    $version = $null
    $pe = $null
    if ($file.Extension -in @('.exe', '.dll')) {
        $info = [Diagnostics.FileVersionInfo]::GetVersionInfo($file.FullName)
        $version = [ordered]@{ file = $info.FileVersion; product = $info.ProductVersion; description = $info.FileDescription }
        $pe = Get-PEHeader $file.FullName
    }
    $file.Refresh()
    $files += [ordered]@{
        name = $file.Name; bytes = $beforeLength; sha256 = $hash
        modified_utc = $beforeTime.ToString('o'); version = $version; pe = $pe
        changed_during_read = ($file.Length -ne $beforeLength -or $file.LastWriteTimeUtc -ne $beforeTime)
    }
}

# Only read relevant values: never export Serial/CD keys or complete INI files.
$settings = @()
foreach ($name in @('ra2.ini', 'ra2md.ini', 'ddraw.ini', 'aqrit.cfg')) {
    $path = Join-Path $installRoot $name
    if (-not (Test-Path -LiteralPath $path -PathType Leaf)) { continue }
    $section = ''
    foreach ($line in [IO.File]::ReadLines($path)) {
        if ($line -match '^\s*\[([^\]]+)\]') { $section = $Matches[1]; continue }
        if ($line -match '^\s*(ScreenWidth|ScreenHeight|AllowHiResModes|VideoBackBuffer|GameSpeed|DetailLevel|windowed|fullscreen|renderer|maxfps|vsync|maintas|boxing|ForceDirectDrawEmulation)\s*=\s*([^;]*)') {
            $settings += [ordered]@{ file = $name; section = $section; key = $Matches[1]; value = $Matches[2].Trim() }
        }
    }
}

$registry = @()
foreach ($hive in @('HKLM:', 'HKCU:')) {
    foreach ($prefix in @('SOFTWARE\Westwood', 'SOFTWARE\WOW6432Node\Westwood')) {
        foreach ($game in @('Red Alert 2', "Yuri's Revenge")) {
            $key = "$hive\$prefix\$game"
            if (Test-Path -LiteralPath $key) {
                $entry = Get-ItemProperty -LiteralPath $key
                $installProperty = $entry.PSObject.Properties['InstallPath']
                $registry += [ordered]@{ key = $key; install_path = $(if ($installProperty) { $installProperty.Value } else { $null }) }
            }
        }
    }
}

$events = @()
$eventQueryError = $null
try {
    $recent = Get-WinEvent -FilterHashtable @{ LogName = 'Application'; StartTime = (Get-Date).AddDays(-7); Id = @(1000, 1001, 1002) } -MaxEvents 200
    foreach ($event in $recent) {
        if ($event.Message -match '(?i)\b(game(md)?\.exe|ra2(md)?\.exe)\b') {
            $events += [ordered]@{ time_utc = $event.TimeCreated.ToUniversalTime().ToString('o'); id = $event.Id; provider = $event.ProviderName; message = $event.Message }
        }
    }
} catch { $eventQueryError = $_.Exception.Message }

$os = Get-CimInstance Win32_OperatingSystem
$gpu = @(Get-CimInstance Win32_VideoController | ForEach-Object {
    [ordered]@{ name = $_.Name; driver_version = $_.DriverVersion; video_mode = $_.VideoModeDescription }
})
$secdrv = Get-Service -Name secdrv -ErrorAction SilentlyContinue
$report = [ordered]@{
    schema = 1; collected_utc = [DateTime]::UtcNow.ToString('o'); host = $env:COMPUTERNAME
    install = $installRoot; scope = 'top-level files; selected settings/registry; recent game application errors'
    os = [ordered]@{ name = $os.Caption; version = $os.Version; build = $os.BuildNumber; architecture = $os.OSArchitecture }
    powershell = $PSVersionTable.PSVersion.ToString(); rdp_session = ($env:SESSIONNAME -like 'RDP*')
    video = $gpu; secdrv_service_present = ($null -ne $secdrv)
    secdrv_status = $(if ($secdrv) { $secdrv.Status.ToString() } else { $null })
    active_game_processes = @(Get-Process -Name game, gamemd, ra2, ra2md -ErrorAction SilentlyContinue | Select-Object ProcessName, Id)
    files = $files; selected_settings = $settings; install_registry = $registry
    application_errors = $events; event_query_error = $eventQueryError
    original_game_launched = $false; source_modified = $false; diagnosis = 'pending evidence review'
}
[IO.Directory]::CreateDirectory([IO.Path]::GetDirectoryName($reportPath)) | Out-Null
$bytes = [Text.UTF8Encoding]::new($false).GetBytes(($report | ConvertTo-Json -Depth 12) + "`n")
$output = [IO.File]::Open($reportPath, 'CreateNew', 'Write', 'None')
try { $output.Write($bytes, 0, $bytes.Length) } finally { $output.Dispose() }
Write-Output "Read-only inventory saved: $reportPath"
